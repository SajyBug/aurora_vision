/* 
 * @File:     h_shape.cpp
 * @Author:   Sajjad Rahnama , Hossein Hojat Ansari
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created  2016
 */

#include "h_shape.h"

H_shape::H_shape()
{
  row = col = 0;
  h_shape.clear();
}

void H_shape::recognize(Mat &org_img)
{
  if (!h_shape_cascade.load(cascade))
  {
    printf("--(!)Error loading face cascade\n");
    exit(0);
  };

  cvtColor(org_img, gray, COLOR_BGR2GRAY);
  equalizeHist(gray, gray);
  detect();
  drawing(org_img);
}

void H_shape::detect()
{
  //-- Detect H shape
  h_shape_cascade.detectMultiScale(gray, h_shape, 2, 4, 1.1, Size(20, 20));
}

void H_shape::drawing(Mat &org_img)
{
  for (size_t i = 0; i < h_shape.size(); i++)
  {
    cout << h_shape.size() << endl;
    Point center(h_shape[i].x + h_shape[i].width / 2, h_shape[i].y + h_shape[i].height / 2);
    ellipse(org_img, center, Size(h_shape[i].width / 2, h_shape[i].height / 2), 0, 0, 360, Scalar(0, 0, 200), 4, 8, 0);

  }
}
