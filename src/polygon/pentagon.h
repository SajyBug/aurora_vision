/* 
 * @File:     pentagon.h
 * @Author:   Sajjad Rahnama , Hossein Hojat Ansari
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created  2016
 */

#ifndef PENTAGON_H
#define PENTAGON_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "../filter.h"

using namespace std;
using namespace cv;

class Pentagon {
    int row, col;
    vector <vector <Point> > contours;
    vector <Point> approx;
    vector<vector<Point> > pentagon;
    void detect();
    void drawing(Mat &org_img, vector <vector <Point> > &contours, int i);

public:
    Pentagon();
    bool recognize(Mat &org_img, Mat thr_img);
};

#endif // PENTAGON_H
