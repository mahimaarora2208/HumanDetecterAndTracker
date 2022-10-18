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

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include<iostream>
#include<opencv2/opencv.hpp>
using std::string;
using std::cout;
using std::cin;

class Image{
   private: 
    string imagePath;  // Path of the image 
    cv::Mat image = cv::imread(imagePath); // image itself :)
   public:
    /**
     * @brief Shorten the input image
     * 
     * @return cv::Mat 
     */
    cv::Mat shorten(); 
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
    void grayScale();

};

#endif  //IMAGE_HPP_