/* 
 * @File:     square.cpp
 * @Author:   Sajjad Rahnama , Hossein Hojat Ansari
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created  2016
 */

#include "square.h"

Square::Square()
{
  row = col = 0;
  contours.clear();
  approx.clear();

}

bool Square::recognize(Mat &org_img, Mat thr_img)
{
  Mat output;
  //medianblure filter for attenuation
  medianBlur(thr_img, output, 3);

  //find contours
  findContours(output, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
  for (unsigned int i = 0; i < contours.size(); i++)
  {
    //Approximates a polygonal curve(s) with the specified precision.
    approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

    if (approx.size() == 4 && isContourConvex(Mat(approx)) && std::fabs(contourArea(Mat(approx))) > 200)
    {
      double maxCosine = 0;
      for (int j = 2; j < 5; j++)
      {
        double cosine = fabs(angle(approx[j % 4], approx[j - 2], approx[j - 1]));
        maxCosine = MAX(maxCosine, cosine);
      }
      if (maxCosine < 0.5)
        square.push_back(approx);
    }
  }
  for (size_t i = 0; i < square.size(); i++)
  {
    const Point* p1 = &square[i][0];
    int n = (int) square[i].size();
    polylines(org_img, &p1, &n, 1, true, Scalar(0, 255, 0), 3, CV_AA);
    //    putText(org_img, "Blue Square", Point(10, 40), FONT_ITALIC, 1, cv::Scalar(212, 157, 34), 2);
    contours.clear();
    approx.clear();
    square.clear();
    return true;
  }
  contours.clear();
  approx.clear();
  square.clear();
  return false;
}

void Square::detect()
{
  // compute all moments (center contours)
  //  Moments mom = moments(Mat(contours[i]));
  //  row = (int) (mom.m10 / mom.m00);
  //  col = (int) (mom.m01 / mom.m00);
  //  cout << "Cols Square: " << row << "  ,  " << "Rows Square: " << col << endl;
}

void Square::drawing(Mat &org_img, vector <vector <Point> > &contours, int i)
{
  drawContours(org_img, contours, i, Scalar(0, 255, 0), 3, 8);
}

