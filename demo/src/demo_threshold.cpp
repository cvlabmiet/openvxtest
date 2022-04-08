/*! @file
 *  @brief Contains demonstration of Threshold function in comparing with OpenCV.
 *  @author Roman Golovanov
 *  @date 23 March 2016
 */

#include <filesystem>
#include <stdexcept>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <kernels.h>
#include <detail/types.h>

#include "idemo.hpp"

//! Demonstration of threshold function.
class demo_threshold : public idemo
{
public:
    demo_threshold() : idemo("threshold")
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

        openvx_out_.create(src_.rows, src_.cols, CV_8UC1);

        cv::createTrackbar("Threshold:", "params", nullptr, 255, on_change_callback, this);
    }

    //! @see idemo::execute_opencv
    void execute_opencv() override
    {
        cv::threshold(src_, opencv_out_, threshold_, 255, cv::THRESH_BINARY);
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

        _vx_image output = {
            openvx_out_.data,
            uint32_t(openvx_out_.cols),
            uint32_t(openvx_out_.rows),
            VX_DF_IMAGE_U8,
            VX_COLOR_SPACE_DEFAULT
        };

        if (auto status = ref_threshold(&input, &output, &thresh); status != VX_SUCCESS)
            throw std::runtime_error("OpenVX: Threshold failed: " + std::to_string(status));

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
    //! Callback to set threshold.
    static void on_change_callback(int value, void* data)
    {
        auto self = static_cast<demo_threshold*>(data);
        self->threshold_ = value;
    }

   int threshold_ = 127; //!< Threshold value.
   cv::Mat src_; //!< Input image.
   cv::Mat opencv_out_; //!< Output image for OpenCV.
   cv::Mat openvx_out_; //!< Output image for OpenVX.
};

// Register the demo.
static demo_threshold demo_threshold_instance;
