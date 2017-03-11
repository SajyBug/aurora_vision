#ifndef HEART
#define HEART

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "../filter.h"

using namespace std;
using namespace cv;

class Heart {
private:
    int row, col;
    std::vector<Rect> heart;
    Mat gray;
    CascadeClassifier heart_cascade;
    String cascade = "/home/sajjadtest/catkin_aurora_vision/src/aurora_vision/src/heart.xml";
    void drawing(Mat &org_img);
    void detect();

public:
    Heart();
    void recognize(Mat &org_img);

};

#endif // HEART

