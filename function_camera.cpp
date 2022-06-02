#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "function_camera.hpp"

void cameraDisplay(const std::string& label_in, const cv::Mat& image_in) {
  if (image_in.data != nullptr) {
      cv::imshow(label_in, image_in);
    }
}

std::string cameraDecodeQR(cv::Mat& image_in) {
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

cv::Mat cameraDecodeFrame(const std::vector<char>& buffer_in) {
  if (buffer_in.empty()) {
      return cv::Mat();
    }
  return cv::imdecode(cv::Mat(buffer_in), 1);
}

cv::Mat cameraGetFrame(const int cam_index) {
  cv::Mat image_out;
  if (cam_index < 0) {
      return image_out;
    }
  /*Open camera*/
  cv::VideoCapture camera = cv::VideoCapture(cam_index);
  if (camera.isOpened()) {
      /*Read next frame into image_out*/
      camera.read(image_out);
      /*Close camera*/
      camera.release();
    }
  return image_out;
}

std::vector<int> cameraDetect(const int flag_max_cam, const int flag_no_cam) {
  std::vector<int> vector_out;
  int index = 0;
  int no_cam = 0;

  /*Search through indexes until either max_cam or no_cam flag reached*/
  while (no_cam < flag_no_cam && (flag_max_cam == 0 || (flag_max_cam > 0 && flag_max_cam > static_cast<int>(vector_out.size())))) {
      if (cameraGetFrame(index).data == nullptr) {
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

std::vector<char> cameraEncodeFrame(const cv::Mat& image_in) {
  if (image_in.data == nullptr) {
      return std::vector<char>();
    }
  std::vector<uchar> data_out(sizeof(image_in));
  cv::imencode(".png", image_in, data_out);
  return std::vector<char>(data_out.begin(), data_out.end());
}
