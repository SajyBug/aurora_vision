#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "../filter.h"

using namespace std;
using namespace cv;

class Square {
    int row, col;
    unsigned int i;
    vector <vector <Point> > contours;
    vector <Point> approx;
    vector<vector<Point> > square;
    void detect();
    void drawing(Mat &org_img, vector <vector <Point> > &contours, int i);

public:
    Square();
    void recognize(Mat &org_img, Mat thr_img);
};


#endif // SQUARE_H
