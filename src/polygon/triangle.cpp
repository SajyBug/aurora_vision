#include "triangle.h"

Triangle::Triangle()
{
  row = col = 0;
  contours.clear();
  approx.clear();
}

void Triangle::recognize(Mat &org_img, Mat thr_img)
{
  Mat output, edge;

  //medianblure filter for attenuation
  medianBlur(thr_img, output, 3);

  //morphology operation for attenuation
  morphology(output);

  //Edge detection
  Canny(output, edge, 140, 255);

  findContours(edge, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
  for (i = 0; i < contours.size(); i++)
  {
    //Approximates a polygonal curve(s) with the specified precision.
    approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);

    // Skip small or non-convex objects
    //        if (std::fabs(cv::contourArea(contours[i])) < 1000 || !cv::isContourConvex(approx))
    //        continue;

    if (approx.size() == 3)
    {
      //            detect();
      //            drawing(org_img, contours, i);
      double maxCosine1 = 0;
      double maxCosine2 = 0;
      double maxCosine3 = 0;

      double cosine1 = fabs(angle(approx[2], approx[1], approx[0]));
      maxCosine1 = MAX(maxCosine1, cosine1);

      double cosine2 = fabs(angle(approx[(2)], approx[(0)], approx[(1)]));
      maxCosine2 = MAX(maxCosine2, cosine2);

      double cosine3 = fabs(angle(approx[(0)], approx[(1)], approx[(2)]));
      maxCosine3 = MAX(maxCosine3, cosine3);

      if ((maxCosine1 > 0.35 && maxCosine1 < 0.65) &&
          (maxCosine2 > 0.35 && maxCosine2 < 0.65) &&
          (maxCosine3 > 0.35 && maxCosine3 < 0.65))
        triangle.push_back(approx);
    }
  }
  for (size_t i = 0; i < triangle.size(); i++)
  {
    const Point* p1 = &triangle[i][0];
    int n = (int) triangle[i].size();
    polylines(org_img, &p1, &n, 1, true, Scalar(0, 255, 0), 3, CV_AA);
    putText(org_img, "Blue Triangle", Point(10, 40), FONT_ITALIC, 1, cv::Scalar(212, 157, 34), 2);
  }
  contours.clear();
  approx.clear();
  triangle.clear();
}

void Triangle::detect()
{
  // compute all moments (center contours)
  Moments mom = moments(Mat(contours[i]));
  row = (int) (mom.m10 / mom.m00);
  col = (int) (mom.m01 / mom.m00);
  cout << "Cols Triangle: " << row << "  ,  " << "Rows Triangle: " << col << endl;
}

void Triangle::drawing(Mat &org_img, vector <vector <Point> > &contours, int i)
{
  drawContours(org_img, contours, i, Scalar(0, 255, 0), 3, 8);
}
