/* 
 * @File:     chess_shape.h
 * @Author:   Sajjad Rahnama , Hossein Hojat Ansari
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created  2016
 */

#ifndef CHESS_SHAPE_H
#define CHESS_SHAPE_H


#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "../filter.h"

using namespace std;
using namespace cv;

class Chess_shape {
private:
    int row, col;
    std::vector<Rect> chess_shape;
    Mat gray;
    CascadeClassifier chess_shape_cascade;
    String cascade = "/home/sajjadtest/catkin_aurora_vision/src/aurora_vision/src/chess_shape.xml";
    void drawing(Mat &org_img);
    void detect();

public:
    Chess_shape();
    void recognize(Mat &org_img);

};


#endif // CHESS_SHAPE_H
