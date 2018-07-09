//@file demo_FindContours.cpp
//@brief Contains demonstration of FindContours function in comparing with OpenCV

#include "../stdafx.h"

#include <opencv2/opencv.hpp>

extern "C"
{
#include "Lib/Kernels/ref.h"
#include "Lib/Common/types.h"
}

#include "../DemoEngine.h"

///////////////////////////////////////////////////////////////////////////////
//@brief Demonstration of FindContours function
class demo_FindContours : public IDemoCase
{
public:
	///@brief default ctor
	demo_FindContours()
		: m_threshold(127)
	{
		// nothing to do
	}

	///@see IDemoCase::ReplyName
	virtual std::string ReplyName() const override
	{
		return "FindContours";
	}

private:
	///@see IDemoCase::execute
	virtual void execute() override;

	///@brief provide interactive demo
	static void applyParameters(int pos, void* data);

private:
	int m_threshold;
	cv::Mat m_srcImage;
};

///////////////////////////////////////////////////////////////////////////////
namespace
{
	const std::string m_openVXWindow = "openVX";
	const std::string m_openCVWindow = "openCV";
	const std::string m_originalWindow = "original1";
	const std::string m_diffWindow = m_openVXWindow + "-" + m_openCVWindow;
}

///////////////////////////////////////////////////////////////////////////////
void demo_FindContours::execute()
{
	cv::namedWindow(m_originalWindow, CV_WINDOW_NORMAL);
	cv::namedWindow(m_openVXWindow, CV_WINDOW_NORMAL);
	cv::namedWindow(m_openCVWindow, CV_WINDOW_NORMAL);
	cv::namedWindow(m_diffWindow, CV_WINDOW_NORMAL);

	const std::string imgPath = /*"apple.png";*/ "../../Image/testimg1_8UC1.png";
	m_srcImage = cv::imread(imgPath, CV_LOAD_IMAGE_GRAYSCALE);
	if (m_srcImage.empty())
	{
		std::cerr << "Cannot read image file: " << imgPath << std::endl;
		cv::destroyAllWindows();
	}
	else
	{
		cv::createTrackbar("Threshold:", m_originalWindow, &m_threshold, 255, applyParameters, static_cast<void*>(this));
		applyParameters(m_threshold, this);
	}
	cv::waitKey(0);
}

///////////////////////////////////////////////////////////////////////////////
void demo_FindContours::applyParameters(int, void* data)
{
	auto demo = static_cast<demo_FindContours*>(data);

	const cv::Size imgSize(demo->m_srcImage.cols, demo->m_srcImage.rows);

	// Thresholding before finding contours

	_vx_threshold vxThresh = { VX_THRESHOLD_TYPE_BINARY, uint8_t(demo->m_threshold), 0/* dummy value */, 255 /* dummy value */ };
	_vx_image srcThreshVXImage = {
		demo->m_srcImage.data,
		imgSize.width,
		imgSize.height,
		VX_DF_IMAGE_U8,
		VX_COLOR_SPACE_DEFAULT
	};

	uint8_t* threshVXImage = static_cast<uint8_t*>(calloc(imgSize.width* imgSize.height, sizeof(uint8_t)));
	_vx_image dstThreshVXImage = {
		threshVXImage,
		imgSize.width,
		imgSize.height,
		VX_DF_IMAGE_U8,
		VX_COLOR_SPACE_DEFAULT
	};

	ref_Threshold(&srcThreshVXImage, &dstThreshVXImage, &vxThresh);

	const cv::Mat origImage = cv::Mat(imgSize, CV_8UC1, threshVXImage);
	cv::imshow(m_originalWindow, origImage);
	

	////////////////
	///@{ OPENCV
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(origImage, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_NONE);
	cv::Mat cvImage(origImage.size(), CV_8UC1, cv::Scalar(0.0, 0.0, 0.0));
	cv::drawContours(cvImage, contours, -1, cv::Scalar(255.0, 255.0, 255.0), 1, 8, hierarchy, 1);
	cv::imshow(m_openCVWindow, cvImage);
	///@}

	///@{ OPENVX
	_vx_image srcVXImage = {
		origImage.data,
		imgSize.width,
		imgSize.height,
		VX_DF_IMAGE_U8,
		VX_COLOR_SPACE_DEFAULT
	};

	uint8_t* outVXImage = static_cast<uint8_t*>(calloc(imgSize.width* imgSize.height, sizeof(uint8_t)));
	_vx_image dstVXImage = {
		outVXImage,
		imgSize.width,
		imgSize.height,
		VX_DF_IMAGE_U8,
		VX_COLOR_SPACE_DEFAULT
	};

	ref_FindContours(&srcVXImage, &dstVXImage);

	const cv::Mat vxImage = cv::Mat(imgSize, CV_8UC1, outVXImage);
	cv::imshow(m_openVXWindow, vxImage);
	///@}

	// Show difference of OpenVX and OpenCV
	const cv::Mat diffImage(imgSize, CV_8UC1);
	cv::absdiff(vxImage, cvImage, diffImage);
	cv::imshow(m_diffWindow, diffImage);
}

///////////////////////////////////////////////////////////////////////////////
IDemoCasePtr CreateFindingContoursDemo()
{
	return std::make_unique<demo_FindContours>();
}
