/* 
 * @File:     polygon.h
 * @Author:   Sajjad Rahnama , Hossein Hojat Ansari
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created  2016
 */

#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "filter.h"
#include "polygon/triangle.h"
#include "polygon/circle.h"
#include "polygon/pentagon.h"
#include "polygon/square.h"
#include "polygon/star.h"
#include "polygon/heart.h"
#include "polygon/h_shape.h"
#include "polygon/chess_shape.h"

using namespace std;
using namespace cv;

class Polygon {
private:
    Triangle triangle;
    Square square;
    Star star;
    Circle circle;
    Pentagon pentagon;
    Heart heart;
    H_shape h_shape;
    Chess_shape chess_shape;

public:
    Polygon();
    Triangle getTriangle();
    Square getSquare();
    Star getStar();
    Circle getCircle();
    Pentagon getPentagon();
    Heart getHeart();
    H_shape getH_shape();
    Chess_shape getChess_shape();
};



#endif // POLYGON_H
