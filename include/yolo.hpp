/**
 * @file yolo.hpp
 * @author Naveen Mangla (nvnmangla@umd.edu)
 * @author Mahima Arora
 * @author Abhinav Garg
 * @brief Model related functions
 * @version 0.1
 * @copyright Copyright (c) 2022
 *
 */

#ifndef HUMANDETECTERANDTRACKER_INCLUDE_YOLO_HPP_
#define HUMANDETECTERANDTRACKER_INCLUDE_YOLO_HPP_
#include <fstream>
#include <image.hpp>

using cv::Scalar;
/**
 * @brief The constants INPUT_WIDTH and INPUT_HEIGHT are for the blob size.
 *  The BLOB stands for Binary Large Object. It contains the data in readable
 * raw format. The image has to be converted to a blob so that the network can
 * process it. In our case, it is a 4D array object with the shape (1, 3, 640,
 * 640). Source:
 * https://learnopencv.com/object-detection-using-yolov5-and-opencv-dnn-in-c-and-python/
 */
// Constants.

using std::cin;
using std::cout;
using std::string;

struct Detection {
  // int class_id;
  float confidence;
  cv::Rect box;
};

class Yolo {
 public:
  const float INPUT_WIDTH = 640.0;
  const float INPUT_HEIGHT = 640.0;
  const float SCORE_THRESHOLD = 0.25;
  const float NMS_THRESHOLD = 0.55;
  const float CONFIDENCE_THRESHOLD = 0.25;

  // Text parameters.
  const float FONT_SCALE = 0.7;
  const int FONT_FACE = cv::FONT_HERSHEY_SIMPLEX;
  const int THICKNESS = 1;

  // Colors.
  Scalar BLACK = Scalar(0, 0, 0);
  Scalar BLUE = Scalar(255, 178, 50);
  Scalar YELLOW = Scalar(0, 255, 255);
  Scalar RED = Scalar(0, 0, 255);

  // contructure
  Yolo(string,bool);
  cv::dnn::Net model;
  // Yolo model YOLO V5
  cv::Mat format_yolov5(const cv::Mat &source);

  std::vector<std::string> load_class_list(string);

  void modelFilter() {
    // TODO(nvnmangla) , Model Filter.
  }

  //  public:
  /**
   * @brief Get the Output image
   *
   * @return cv::Mat
   */
  cv::Mat getOutput();

  void detect(cv::Mat &image, std::vector<Detection> &output,
              const std::vector<std::string> &className);
};

#endif  // HUMANDETECTERANDTRACKER_INCLUDE_YOLO_HPP_