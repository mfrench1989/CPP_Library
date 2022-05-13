#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "function_opencv.hpp"

void opencvDisplay(const std::string& label_in, const cv::Mat& image_in) {
  if (image_in.data != nullptr) {
      cv::imshow(label_in, image_in);
    }
}

std::string opencvQRDecode(cv::Mat& image_in) {
  /*Check image has data*/
  if (image_in.data == nullptr) {
      return std::string();
    }

  /*Convert to gray-scale*/
  cv::cvtColor(image_in, image_in, cv::COLOR_BGR2GRAY);

  /*Detect and decode image*/
  cv::QRCodeDetector qr_detector = cv::QRCodeDetector();
  cv::Mat points, image_rect;

  return qr_detector.detectAndDecode(image_in, points, image_rect);
}

cv::Mat opencvCaptureFrame(const int index_in) {
  cv::Mat image_out;
  /*Open camera*/
  cv::VideoCapture video_cap = cv::VideoCapture(index_in);
  if (video_cap.isOpened()) {
      /*Read next frame into image_out*/
      video_cap.read(image_out);
      /*Close camera*/
      video_cap.release();
    }
  return image_out;
}

std::vector<int> opencvDetectCameras() {
  std::vector<int> vector_out;
  int index = 0;
  int no_cam = 0;

  /*Search through indexes until 16 consecutive indexes with no camera*/
  while (no_cam < 16) {
      cv::Mat image = opencvCaptureFrame(index);
      if (image.data == nullptr) {
          ++no_cam;
        }
      else {
          vector_out.push_back(index);
          no_cam = 0;
        }
      ++index;
    }

  return vector_out;
}
