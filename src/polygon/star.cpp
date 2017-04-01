/* 
 * @File:     star.cpp
 * @Author:   Sajjad Rahnama , Hossein Hojat Ansari
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created  2016
 */

#include "star.h"

Star::Star()
{
  row = col = 0;
  contours.clear();
  approx.clear();

}

void Star::recognize(Mat &org_img, Mat thr_img)
{

  //find contours
  findContours(thr_img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
  for (unsigned int i = 0; i < contours.size(); i++)
  {
    //Approximates a polygonal curve(s) with the specified precision.
    approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);
    if (approx.size() == 10 && fabs(contourArea(Mat(approx))) > 100)
    {
      double maxCosine1 = 0;
      double maxCosine2 = 0;
      double maxCosine3 = 0;
      double maxCosine4 = 0;
      double maxCosine5 = 0;
      double maxCosine6 = 0;
      double maxCosine7 = 0;
      double maxCosine8 = 0;
      double maxCosine9 = 0;
      double maxCosine0 = 0;

      double cosine1 = fabs(angle(approx[2], approx[0], approx[1]));
      maxCosine1 = MAX(maxCosine1, cosine1);

      double cosine2 = fabs(angle(approx[(3)], approx[(1)], approx[(2)]));
      maxCosine2 = MAX(maxCosine2, cosine2);

      double cosine3 = fabs(angle(approx[(4)], approx[(2)], approx[(3)]));
      maxCosine3 = MAX(maxCosine3, cosine3);

      double cosine4 = fabs(angle(approx[(5)], approx[(3)], approx[(4)]));
      maxCosine4 = MAX(maxCosine4, cosine4);

      double cosine5 = fabs(angle(approx[(6)], approx[(4)], approx[(5)]));
      maxCosine5 = MAX(maxCosine5, cosine5);

      double cosine6 = fabs(angle(approx[(7)], approx[(5)], approx[(6)]));
      maxCosine6 = MAX(maxCosine6, cosine6);

      double cosine7 = fabs(angle(approx[(8)], approx[(6)], approx[(7)]));
      maxCosine7 = MAX(maxCosine7, cosine7);

      double cosine8 = fabs(angle(approx[(9)], approx[(7)], approx[(8)]));
      maxCosine8 = MAX(maxCosine8, cosine8);

      double cosine9 = fabs(angle(approx[(0)], approx[(8)], approx[(9)]));
      maxCosine9 = MAX(maxCosine9, cosine9);

      double cosine0 = fabs(angle(approx[(1)], approx[(9)], approx[(0)]));
      maxCosine0 = MAX(maxCosine0, cosine0);


      if ((maxCosine1 > 0.35 && maxCosine1 < 0.65) &&
          (maxCosine2 < 0.9) &&
          (maxCosine3 > 0.35 && maxCosine3 < 0.65) &&
          (maxCosine4 < 0.9) &&
          (maxCosine5 > 0.35 && maxCosine5 < 0.65) &&
          (maxCosine6 < 0.9) &&
          (maxCosine7 > 0.35 && maxCosine3 < 0.65) &&
          (maxCosine8 < 0.9) &&
          (maxCosine9 > 0.35 && maxCosine5 < 0.65) &&
          (maxCosine0 < 0.9))
        star.push_back(approx);
    }
  }
  for (size_t i = 0; i < star.size(); i++)
  {
    const Point* p1 = &star[i][0];
    int n = (int) star[i].size();
    polylines(org_img, &p1, &n, 1, true, Scalar(0, 255, 0), 3, CV_AA);
    //    putText(org_img, "Blue Star", Point(10, 40), FONT_ITALIC, 1, cv::Scalar(212, 157, 34), 2);
  }
  contours.clear();
  approx.clear();
  star.clear();
}

void Star::detect()
{
  // compute all moments (center contours)
  //  Moments mom = moments(Mat(contours[i]));
  //  row = (int) (mom.m10 / mom.m00);
  //  col = (int) (mom.m01 / mom.m00);
  //  cout << "Cols Star: " << row << "  ,  " << "Rows Star: " << col << endl;
}

void Star::drawing(Mat &org_img, vector <vector <Point> > &contours, int i)
{
  drawContours(org_img, contours, i, Scalar(0, 255, 0), 3, 8);
}
