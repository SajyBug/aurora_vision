/* 
 * @File:     circle.cpp
 * @Author:   Sajjad Rahnama , Hossein Hojat Ansari
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created  2016
 */

#include "circle.h"

Circle::Circle()
{
  circles.clear();
  center = Point(0, 0);
}

bool Circle::recognize(Mat &org_img, Mat thr_img)
{
  Mat output;
  // Reduce the noise so we avoid false circle detection
  GaussianBlur(thr_img, output, Size(3, 3), 2, 2);

  morphology(output);

  // Apply the Hough Transform to find the circles
  HoughCircles(output, circles, CV_HOUGH_GRADIENT, 1, output.rows / 4, 20, 20, 10, 50);

  // Draw the circles detected
  for (unsigned int i = 0; i < circles.size(); i++)
  {
    center = Point(cvRound(circles[0][0]), cvRound(circles[0][1]));
    radius = cvRound(circles[0][2]);
    // circle center
    circle(org_img, center, 3, Scalar(0, 255, 0), -1, 8, 0);
    // circle outline
    circle(org_img, center, radius, Scalar(185, 192, 33), 3, 8, 0);
    return true;
  }
  return false;
}

void Circle::detect()
{
  //  cout << center << endl;
}
