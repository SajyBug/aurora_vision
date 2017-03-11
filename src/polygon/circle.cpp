#include "circle.h"

Circle::Circle()
{
  circles.clear();
  center = Point(0, 0);
}

void Circle::recognize(Mat &org_img, Mat thr_img)
{
  Mat output;
  // Reduce the noise so we avoid false circle detection
  GaussianBlur(thr_img, output, Size(3, 3), 2, 2);


  morphology(output);

  // Apply the Hough Transform to find the circles
  HoughCircles(output, circles, CV_HOUGH_GRADIENT, 1, output.rows / 4, 20, 20, 10, 50);

  // Draw the circles detected
  for (i = 0; i < circles.size(); i++)
  {
    detect();
    // circle center
    circle(org_img, center, 3, Scalar(0, 255, 0), -1, 8, 0);
    // circle outline
    circle(org_img, center, radius, Scalar(185, 192, 33), 3, 8, 0);

  }

}

void Circle::detect()
{
  center = Point(cvRound(circles[i][0]), cvRound(circles[i][1]));
  radius = cvRound(circles[i][2]);
  cout << center << endl;
}
