/* 
 * @File:     circle.h
 * @Author:   Sajjad Rahnama , Hossein Hojat Ansari
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created  2016
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "../filter.h"

using namespace std;
using namespace cv;

class Circle {
    vector <Vec3f> circles;
    Point center;
    unsigned int radius;

public:
    Circle();
    void recognize(Mat &org_img, Mat thr_img);
    void detect();
};
#endif // CIRCLE_H
