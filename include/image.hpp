/**
 * @file image.hpp
 * @author Naveen Mangla (nvnmangla@umd.edu)
 * @author Mahima Arora
 * @author Abhinav Garg
 * @brief Image related functions
 * @version 0.1
 * @copyright Copyright (c) 2022
 *
 */

#ifndef HUMANDETECTERANDTRACKER_INCLUDE_IMAGE_HPP_
#define HUMANDETECTERANDTRACKER_INCLUDE_IMAGE_HPP_

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>



using std::cin;
using std::cout;
using std::string;

class Image {
 public:
  /**
   * @brief Construct a new Image object
   * 
   * @param pathToImage:string - Directory to the image
   */
  explicit Image(string pathToImage);
  bool testView = true;
  bool testGrayscale = true;

 private:
  string imagePath;  // Path of the image
  cv::Mat image;     // image itself :)
  cv::Mat shortImage;
  int ratio = 4;
  cv::Mat gray;

 public:
  /**
   * @brief Shorten the input image
   *
   * @return cv::Mat
   */
  cv::Mat shorten();

  /**
   * @brief Get the Image
   *
   * @return cv::Mat
   */
  cv::Mat getImage();

  /**
   * @brief Enlage the output image
   *
   * @return cv::Mat
   */
  cv::Mat enlarge();
  /**
   * @brief view the image
   *
   */
  void view();
  /**
   * @brief Gray Scaling the image
   *
   */
  cv::Mat grayScale();
};

#endif  // HUMANDETECTERANDTRACKER_INCLUDE_IMAGE_HPP_