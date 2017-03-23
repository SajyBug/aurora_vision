#include "filter.h"
#include "mainwindow.h"

Mat hsv_img;

void morphology(Mat& img)
{
  //morphological opening (remove small objects from the foreground)
  erode(img, img, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
  dilate(img, img, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

  //morphological closing (fill small holes in the foreground)
  dilate(img, img, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
  erode(img, img, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
}

void hsv_thresholding(Mat& org_img, Mat& thr_img, set_on *set)
{

  cvtColor(org_img, hsv_img, CV_BGR2HSV); //Convert the captured frame from BGR to HSV
  inRange(hsv_img, Scalar(set->h_low, set->s_low, set->v_low), Scalar(set->h_high, set->s_high, set->v_high), thr_img); //Threshold the image
}

double angle(Point pt1, Point pt2, Point pt0)
{
  double dx1 = pt1.x - pt0.x;
  double dy1 = pt1.y - pt0.y;
  double dx2 = pt2.x - pt0.x;
  double dy2 = pt2.y - pt0.y;

  return (dx1 * dx2 + dy1 * dy2) / sqrt((dx1 * dx1 + dy1 * dy1)*(dx2 * dx2 + dy2 * dy2) + 1e-10);
}

