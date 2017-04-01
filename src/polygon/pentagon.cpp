/* 
 * @File:     pentagon.cpp
 * @Author:   Sajjad Rahnama , Hossein Hojat Ansari
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created  2016
 */

#include "pentagon.h"

Pentagon::Pentagon()
{
  row = col = 0;
  contours.clear();
  approx.clear();

}

void Pentagon::recognize(Mat &org_img, Mat thr_img)
{

  //find contours
  findContours(thr_img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
  for (unsigned int i = 0; i < contours.size(); i++)
  {
    //Approximates a polygonal curve(s) with the specified precision.
    approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

    if (approx.size() == 5 && fabs(contourArea(Mat(approx))) > 100)
    {
      double maxCosine1 = 0;
      double maxCosine2 = 0;
      double maxCosine3 = 0;
      double maxCosine4 = 0;
      double maxCosine5 = 0;

      double cosine1 = fabs(angle(approx[2], approx[0], approx[1]));
      maxCosine1 = MAX(maxCosine1, cosine1);

      double cosine2 = fabs(angle(approx[(3)], approx[(1)], approx[(2)]));
      maxCosine2 = MAX(maxCosine2, cosine2);

      double cosine3 = fabs(angle(approx[(4)], approx[(2)], approx[(3)]));
      maxCosine3 = MAX(maxCosine3, cosine3);

      double cosine4 = fabs(angle(approx[(0)], approx[(3)], approx[(4)]));
      maxCosine4 = MAX(maxCosine4, cosine4);

      double cosine5 = fabs(angle(approx[(4)], approx[(1)], approx[(0)]));
      maxCosine5 = MAX(maxCosine5, cosine5);

      if ((maxCosine1 < 0.6)&&
          (maxCosine2 < 0.6) &&
          (maxCosine3 < 0.6) &&
          (maxCosine4 < 0.6) &&
          (maxCosine5 < 0.6))
        pentagon.push_back(approx);
    }
  }
  for (size_t i = 0; i < pentagon.size(); i++)
  {
    const Point* p1 = &pentagon[i][0];
    int n = (int) pentagon[i].size();
    polylines(org_img, &p1, &n, 1, true, Scalar(0, 255, 0), 3, CV_AA);
    putText(org_img, "Blue Pentagon", Point(10, 40), FONT_ITALIC, 1, cv::Scalar(212, 157, 34), 2);
  }
  contours.clear();
  approx.clear();
  pentagon.clear();
}

void Pentagon::detect()
{
  // compute all moments (center contours)
  //  Moments mom = moments(Mat(contours[i]));
  //  row = (int) (mom.m10 / mom.m00);
  //  col = (int) (mom.m01 / mom.m00);
  //  cout << "Cols Pentagon: " << row << "  ,  " << "Rows Pentagon: " << col << endl;
}

void Pentagon::drawing(Mat &org_img, vector <vector <Point> > &contours, int i)
{
  drawContours(org_img, contours, i, Scalar(0, 255, 0), 3, 8);
}

