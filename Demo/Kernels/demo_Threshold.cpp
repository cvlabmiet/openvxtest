//@file demo_Threshold.h
//@brief Contains demonstration of Threshold function in comparing with OpenCV
//@author Roman Golovanov
//@date 23 March 2016

#include "../stdafx.h"

#include <opencv2/opencv.hpp>

extern "C"
{
#include <Kernels/ref.h>
#include <types.h>
}

#include "../DemoEngine.h"

///////////////////////////////////////////////////////////////////////////////
//@brief Demonstration of Threshold function
class demo_Threshold : public IDemoCase
{
public:
   ///@brief default ctor
   demo_Threshold()
      : m_threshold(127)
   {
      // nothing to do
   }

   ///@see IDemoCase::ReplyName
   virtual std::string ReplyName() const override
   {
      return "Threshold";
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
   const std::string m_openVXWindow    = "openVX";
   const std::string m_openCVWindow    = "openCV";
   const std::string m_originalWindow  = "original";
   const std::string m_diffWindow      = "Diff of " + m_openVXWindow + " and " + m_openCVWindow;
}

///////////////////////////////////////////////////////////////////////////////
void demo_Threshold::execute()
{
   cv::namedWindow(m_originalWindow, CV_WINDOW_NORMAL);
   cv::namedWindow(m_openVXWindow, CV_WINDOW_NORMAL);
   cv::namedWindow(m_openCVWindow, CV_WINDOW_NORMAL);
   cv::namedWindow(m_diffWindow, CV_WINDOW_NORMAL);

   const std::string imgPath = "../Image/Solvay_conference_1927.png";
   m_srcImage = cv::imread(imgPath, CV_LOAD_IMAGE_GRAYSCALE);
   cv::imshow(m_originalWindow, m_srcImage);

   cv::createTrackbar("Threshold:", m_originalWindow, &m_threshold, 255, applyParameters, static_cast<void*>(this));
   applyParameters(m_threshold, this);

   cv::waitKey(0);
}

///////////////////////////////////////////////////////////////////////////////
void demo_Threshold::applyParameters(int, void* data)
{
   auto demo = static_cast<demo_Threshold*>(data);

   const cv::Size imgSize(demo->m_srcImage.cols, demo->m_srcImage.rows);

   ///@{ OPENCV
   cv::Mat cvImage;
   cv::threshold(demo->m_srcImage, cvImage, demo->m_threshold, 255, CV_THRESH_BINARY);
   cv::imshow(m_openCVWindow, cvImage);
   ///@}

   ///@{ OPENVX
   _vx_threshold vxThresh = { VX_THRESHOLD_TYPE_BINARY, uint8_t(demo->m_threshold), 0/* dummy value */, 255 /* dummy value */};
   _vx_image srcVXImage = {
      demo->m_srcImage.data,
      uint32_t(imgSize.width),
      uint32_t(imgSize.height),
      VX_DF_IMAGE_U8,
      VX_COLOR_SPACE_DEFAULT
   };

   uint8_t* outVXImage = static_cast<uint8_t*>(calloc(imgSize.width* imgSize.height, sizeof(uint8_t)));
   _vx_image dstVXImage = {
      outVXImage,
      uint32_t(imgSize.width),
      uint32_t(imgSize.height),
      VX_DF_IMAGE_U8,
      VX_COLOR_SPACE_DEFAULT
   };

   ref_Threshold(&srcVXImage, &dstVXImage, &vxThresh);

   const cv::Mat vxImage = cv::Mat(imgSize, CV_8UC1, outVXImage);
   cv::imshow(m_openVXWindow, vxImage);
   ///@}

   // Show difference of OpenVX and OpenCV
   const cv::Mat diffImage(imgSize, CV_8UC1);
   cv::absdiff(vxImage, cvImage, diffImage);
   cv::imshow(m_diffWindow, diffImage);
}

///////////////////////////////////////////////////////////////////////////////
IDemoCasePtr CreateThresholdingDemo()
{
   return std::make_unique<demo_Threshold>();
}
