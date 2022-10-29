/**
 * @file image.cpp
 * @author Naveen Mangla (nmangla@umd.edu); Mahima Arora (marora1@umd.edu)
 * @brief
 * @version 0.1
 * @date 2022-10-14
 * @copyright Copyright (c) 2022
 *
 */

#include <cmath>
#include <image.hpp>
#include <yolo.hpp>
/**
 * @brief Construct a new Yolo:: Yolo object
 * 
 * @param modelPath 
 * @param is_cuda 
 */
Yolo::Yolo(string modelPath) {
  this->model = cv::dnn::readNetFromONNX(modelPath);

  std::cout << "Running on CPU\n";
  this->model.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
  this->model.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

}

cv::Mat Yolo::getOutput() {
  cv::Mat outImage = cv::Mat::ones(2, 2, CV_8UC1);

  // Get output image from model
  return outImage;
}
/**
 * @brief To load all the class names of coco dataset
 * 
 * @param fileName 
 * @return std::vector<std::string> 
 */
std::vector<std::string> Yolo::load_class_list(string fileName) {
  std::vector<string> class_list;
  std::ifstream ifs(fileName);
  std::string line;
  while (getline(ifs, line)) {
    class_list.push_back(line);
  }
  return class_list;
}
/**
 * @brief storing all the rectangle dimension which would be further used to draw on the object
 * 
 * @param boxes 
 * @param data 
 * @param box_height 
 * @param x_factor 
 * @param y_factor 
 */
void Yolo::getting_Rect_dim(std::vector<cv::Rect> &boxes, float *data,
                            float &box_height, float x_factor, float y_factor) {
  float x = data[0];
  float y = data[1];
  float w = data[2];
  float h = data[3];
  int left = static_cast<int>((x - 0.5 * w) * x_factor);
  int top = static_cast<int>((y - 0.5 * h) * y_factor);
  int width = static_cast<int>(w * x_factor);
  int height = static_cast<int>(h * y_factor);
  box_height = height;
  boxes.push_back(cv::Rect(left, top, width, height));

}
/**
 * @brief The function passes the image through yolo neural network and stores the result in vector
 * 
 * @param image:cv::Mat - Input frame 
 * @param output:cv::Mat -  Output frame with detection
 * @param className:vector<string> string list with class name  
 */
void Yolo::detect(cv::Mat &image, std::vector<Detection> &output,
                  const std::vector<std::string> &className) {
  cv::Mat blob;

  Image img(image);
  auto input_image = img.square_img();

  cv::dnn::blobFromImage(input_image, blob, 1. / 255.,
                         cv::Size(img.INPUT_WIDTH, img.INPUT_HEIGHT),
                         cv::Scalar(), true, false);
  this->model.setInput(blob);
  std::vector<cv::Mat> outputs;
  this->model.forward(outputs, this->model.getUnconnectedOutLayersNames());

  float x_factor = input_image.cols / img.INPUT_WIDTH;
  float y_factor = input_image.rows / img.INPUT_HEIGHT;

  float *data = reinterpret_cast<float*>(outputs[0].data);

  const int rows = 25200;

  std::vector<int> class_ids;
  std::vector<float> confidences;
  std::vector<cv::Rect> boxes;
  float box_height = 0;

  for (int i = 0; i < rows; ++i) {
    float confidence = data[4];
    if (confidence >= this->CONFIDENCE_THRESHOLD) {
      float *classes_scores = data + 5;
      cv::Mat scores(1, className.size(), CV_32FC1, classes_scores);
      cv::Point class_id;
      double max_class_score;
      minMaxLoc(scores, 0, &max_class_score, 0, &class_id);

      if (class_id.x == 0 && max_class_score > SCORE_THRESHOLD) {
        confidences.push_back(confidence);

        class_ids.push_back(class_id.x);

        getting_Rect_dim(boxes, data, box_height, x_factor, y_factor);
      }
    }

    data += 85;
  }
  // remove_Redundant_box(boxes,confidences);
  std::vector<int> nms_result;

  /**
   * @brief Removing excessive boxes detected by yolo model
   *
   */
  cv::dnn::NMSBoxes(boxes, confidences, this->SCORE_THRESHOLD,
                    this->NMS_THRESHOLD, nms_result);
  for (int i = 0; i < static_cast<int>(nms_result.size()); i++) {
    int idx = nms_result[i];
    Detection result;
    // result.class_id = class_ids[idx];
    result.confidence = confidences[idx];
    result.box = boxes[idx];
    // cout<<"boxes"<<boxes[idx]<<"\n";
    result.depth =
        (2 / tan((box_height * 55 * 3.14159 / 180) / input_image.rows));
    output.push_back(result);
  }
}

// std::vector<Detection> remove_Redundant_box(std::vector<cv::Rect>boxes,
// std::vector<float>confidences){

//   cv::dnn::NMSBoxes(boxes, confidences, this->SCORE_THRESHOLD,
//                     this->NMS_THRESHOLD, nms_result);
//   for (int i = 0; i < static_cast<int>(nms_result.size()); i++) {
//     int idx = nms_result[i];
//     Detection result;
//     // result.class_id = class_ids[idx];
//     result.confidence = confidences[idx];
//     result.box = boxes[idx];
//     // cout<<"boxes"<<boxes[idx]<<"\n";
//     result.depth = (2/tan((box_height*55*3.14159/180)/input_image.rows));
//     output.push_back(result);
//   }
// }
