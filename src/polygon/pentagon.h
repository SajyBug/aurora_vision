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
    unsigned int i;
    vector <vector <Point> > contours;
    vector <Point> approx;
    vector<vector<Point> > pentagon;
    void detect();
    void drawing(Mat &org_img, vector <vector <Point> > &contours, int i);

public:
    Pentagon();
    void recognize(Mat &org_img, Mat thr_img);
};

#endif // PENTAGON_H
