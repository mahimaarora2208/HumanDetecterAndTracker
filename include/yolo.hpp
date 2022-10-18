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

#ifndef YOLO_HPP_
#define YOLO_HPP_

#include<iostream>
#include<opencv2/opencv.hpp>
using std::string;
using std::cout;
using std::cin;

class Yolo{
    private:
        // This will change to original yolo model
        int model;

        void modelFilter(){
            //TODO, Model Filter.
        };
    
    public:
        /**
         * @brief Get the Output image
         * 
         * @return cv::Mat 
         */
        cv::Mat getOutput();
};

#endif  //YOLO_HPP_