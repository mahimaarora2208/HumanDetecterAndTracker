/**
 * @file test.cpp
 * @author Naveen Mangla (nmangla@umd.edu)
 * @brief Test cases for functions
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <gtest/gtest.h>

#include <image.hpp>
#include <opencv2/opencv.hpp>
#include <yolo.hpp>

TEST(Yolo_detect_Test,detect){
  cv::Mat im = cv::imread("../videos/shiva.jpg",1);
  Image img(im);
  Yolo yol("../models/yolov5n.onnx");
  auto classes = yol.load_class_list("../segmentations/coco_names.txt");

  yol.detect(img,classes);
}

TEST(Yolo_constuctor_test,yolo){
  
  Yolo yol("../models/yolov5n.onnx");
 
}


TEST(Image_constuctor_test,image){
  cv::Mat im = cv::imread("../videos/shiva.jpg",1);
  Image img(im);
 
}


TEST(Image_sq_image_Test,sqare_image){
  cv::Mat im = cv::imread("../videos/shiva.jpg",1);
  Image img(im);
  EXPECT_FLOAT_EQ(img.square_img().cols,img.square_img().rows);

}


TEST(Image_get_image_Test,get_image){
  cv::Mat im = cv::imread("../videos/shiva.jpg",1);
  Image img(im);
  EXPECT_FLOAT_EQ(img.getImage().cols,im.cols);

}


TEST(Image_draw_rectangles_Test,draw_rectangles){
  Yolo yol("../models/yolov5n.onnx");
  cv::Mat im = cv::imread("../videos/shiva.jpg",1);
  Image img(im);
  auto size = static_cast<int>(yol.output.size());
  
  EXPECT_EQ(img.getImage().cols,img.draw_rectangles(size,yol.output).cols);
  

}

TEST(Yolo_Getting_rectangle_dimensions,getting_Rect_dim){
  Yolo yol("../models/yolov5n.onnx");
  cv::Mat im = cv::imread("../videos/shiva.jpg",1);
  Image img(im);
  std::vector<cv::Rect> boxes;
  float data[4] = {1,2,3,4};
  float box_height{};
  yol.getting_Rect_dim(boxes,data, box_height,1.0, 1.0);

}


TEST(Yolo_load_class_list_test,load_class_list){
  Yolo yol("../models/yolov5n.onnx");
  auto list = yol.load_class_list("../segmentations/coco_names.txt");
  EXPECT_EQ(80,list.size());
}