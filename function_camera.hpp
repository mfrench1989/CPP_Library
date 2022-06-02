#ifndef FUNCTIONOPENCV_HPP
#define FUNCTIONOPENCV_HPP

#include <opencv2/objdetect.hpp>

void cameraDisplay(const std::string&, const cv::Mat&);
std::string cameraDecodeQR(cv::Mat&);
cv::Mat cameraDecodeFrame(const std::vector<char>&);
cv::Mat cameraGetFrame(const int);
std::vector<int> cameraDetect(const int, const int);
std::vector<char> cameraEncodeFrame(const cv::Mat&);

#endif // FUNCTIONOPENCV_HPP
