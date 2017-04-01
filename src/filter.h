/* 
 * @File:     filter.h
 * @Author:   Sajjad Rahnama , Hossein Hojat Ansari
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created  2016
 */

#ifndef FILTER_H
#define FILTER_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "mainwindow.h"


using namespace std;
using namespace cv;
void morphology(Mat& img);
void hsv_thresholding(Mat& org_img, Mat& thr_img, set_on set);
double angle(Point pt1, Point pt2, Point pt0);


#endif // FILTER_H
