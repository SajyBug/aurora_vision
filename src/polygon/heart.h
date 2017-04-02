/* 
 * @File:     heart.h
 * @Author:   Sajjad Rahnama , Hossein Hojat Ansari
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created  2016
 */

#ifndef HEART
#define HEART

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "ros/ros.h"
#include "../filter.h"
#include <aurora_vision/heart.h>

using namespace std;
using namespace cv;

class Heart {
public:
    Heart();
    aurora_vision::heart recognize(Mat &org_img);

private:
    int row, col;
    std::vector<Rect> heart;
    Mat gray;
    CascadeClassifier heart_cascade;
    String cascade = "/home/sajjadtest/catkin_aurora_vision/src/aurora_vision/src/heart.xml";
    void drawing(Mat &org_img);
    void detect(); 
};

#endif // HEART

