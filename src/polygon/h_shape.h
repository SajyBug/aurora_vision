#ifndef H_SHAPE_H
#define H_SHAPE_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "../filter.h"

using namespace std;
using namespace cv;

class H_shape {
private:
    int row, col;
    std::vector<Rect> h_shape;
    Mat gray;
    CascadeClassifier h_shape_cascade;
    String cascade = "/home/sajjadtest/catkin_aurora_vision/src/aurora_vision/src/h_shape.xml";
    void drawing(Mat &org_img);
    void detect();

public:
    H_shape();
    void recognize(Mat &org_img);

};



#endif // H_SHAPE_H
