/*! @file
 *  @brief Contains demonstration of cclabeling function in comparing with OpenCV.
 *  @author Iaroslav Murenkov
 *  @date 2022-03-30
 */

#include <cstdint>
#include <filesystem>
#include <stdexcept>
#include <iostream>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <kernels.h>
#include <detail/types.h>
#include <sys/types.h>

#include "idemo.hpp"

//! Demonstration of cclabeling function.
class demo_cclabeling : public idemo
{
    public:
        demo_cclabeling() : idemo("cclabeling")
    {
    }

        //! @see idemo::prepeare
        void prepare(const std::filesystem::path& resource_dir) override
        {
            cv::namedWindow("params", cv::WINDOW_GUI_EXPANDED);
            cv::namedWindow("original", cv::WINDOW_NORMAL);
            cv::namedWindow("opencv", cv::WINDOW_NORMAL);
            cv::namedWindow("openvx", cv::WINDOW_NORMAL);
            cv::namedWindow("diff", cv::WINDOW_NORMAL);

            auto path = resource_dir / std::filesystem::path("Solvay_conference_1927.png");
            if (!std::filesystem::exists(path))
                throw std::invalid_argument("Cannot find file " + path.string());

            src_ = cv::imread(path, cv::IMREAD_GRAYSCALE);
            cv::imshow("original", src_);

            cv::createTrackbar("threshold:", "params", nullptr, 255, threshold_callback, this);
            cv::createTrackbar("connectivity:", "params", nullptr, 8, connectivity_callback, this);
        }

        //! @see idemo::execute_opencv
        void execute_opencv() override
        {
            cv::Mat thresh(src_.size(), CV_8UC1);
            cv::threshold(src_, thresh, threshold_, 255, cv::THRESH_BINARY);

            cv::Mat labels(src_.size(), CV_32SC1);
            int nlabels = cv::connectedComponents(thresh, labels, connectivity_);

            opencv_out_.create(src_.rows, src_.cols, CV_8UC1);
            for (auto row = 0; row < opencv_out_.rows; ++row)
                for (auto col = 0; col < opencv_out_.cols; ++col)
                    opencv_out_.at<uint8_t>(row, col) = static_cast<uint8_t>(((float) labels.at<int>(row, col)) / nlabels * 255);

            labels.convertTo(opencv_out_, CV_8UC1);
            cv::imshow("opencv", opencv_out_);
        }

        //! @see idemo::execute_openvx
        void execute_openvx() override
        {
            _vx_threshold thresh{VX_THRESHOLD_TYPE_BINARY, uint8_t(threshold_), 0, 255};

            _vx_image input = {
                src_.data,
                uint32_t(src_.cols),
                uint32_t(src_.rows),
                VX_DF_IMAGE_U8,
                VX_COLOR_SPACE_DEFAULT
            };

            cv::Mat thresholded_;
            thresholded_.create(src_.rows, src_.cols, CV_8UC1);
            _vx_image thresholded = {
                thresholded_.data,
                uint32_t(thresholded_.cols),
                uint32_t(thresholded_.rows),
                VX_DF_IMAGE_U8,
                VX_COLOR_SPACE_DEFAULT
            };

            if (auto status = ref_threshold(&input, &thresholded, &thresh); status != VX_SUCCESS)
                throw std::runtime_error("OpenVX: Threshold failed: " + std::to_string(status));

            cv::Mat labels_;
            labels_.create(src_.rows, src_.cols, CV_32SC1);
            _vx_image labels = {
                labels_.data,
                uint32_t(labels_.cols),
                uint32_t(labels_.rows),
                VX_DF_IMAGE_S32,
                VX_COLOR_SPACE_DEFAULT
            };

            int32_t nlabels = ref_cclabeling(&thresholded, &labels, connectivity_);

            openvx_out_.create(src_.rows, src_.cols, CV_8UC1);
            _vx_image output = {
                openvx_out_.data,
                uint32_t(openvx_out_.cols),
                uint32_t(openvx_out_.rows),
                VX_DF_IMAGE_U8,
                VX_COLOR_SPACE_DEFAULT
            };

            for (auto ind = 0; ind < openvx_out_.rows * openvx_out_.cols; ++ind)
                openvx_out_.data[ind] = static_cast<uint8_t>((static_cast<float>(labels_.data[ind])) / nlabels * 255);

            std::cout << output.data << "\n"; // To avoid "error: unused variable ‘output’ [-Werror=unused-variable]"

            labels_.convertTo(openvx_out_, CV_8UC1);
            cv::imshow("openvx", openvx_out_);
        }

        //! @see idemo::make_diff
        void make_diff() override
        {
            cv::Mat diff;
            cv::absdiff(openvx_out_, opencv_out_, diff);
            cv::imshow("diff", diff);
        }

    private:
        static void threshold_callback(int value, void* data)
        {
            auto self = static_cast<demo_cclabeling*>(data);
            self->threshold_ = value;
        }
        static void connectivity_callback(int value, void* data)
        {
            auto self = static_cast<demo_cclabeling*>(data);
            self->connectivity_ = value;
        }

        int connectivity_ = 8;
        int threshold_ = 127;
        cv::Mat src_;
        cv::Mat opencv_out_;
        cv::Mat openvx_out_;
};

// Register the demo.
static demo_cclabeling demo_cclabeling_instance;
