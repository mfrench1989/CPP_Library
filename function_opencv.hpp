#ifndef FUNCTIONOPENCV_HPP
#define FUNCTIONOPENCV_HPP

#include <opencv2/objdetect.hpp>

void opencvDisplay(const std::string&, const cv::Mat&);
cv::Mat opencvCaptureFrame(const int);
std::string opencvQRDecode(cv::Mat&);
std::vector<int> opencvDetectCameras();

#endif // FUNCTIONOPENCV_HPP
