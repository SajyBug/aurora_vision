/* 
 * @File:     triangle.h
 * @Author:   Sajjad Rahnama , Hossein Hojat Ansari
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created  2016
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "../filter.h"

using namespace std;
using namespace cv;

class Triangle {
private:
    int row, col;
    vector <vector <Point> > contours;
    vector <Point> approx;
    vector<vector<Point> > triangle;
    void drawing(Mat &org_img, vector <vector <Point> > &contours, int i);
    void detect();

public:
    Triangle();
    void recognize(Mat &org_img, Mat thr_img);
};

#endif // TRIANGLE_H
