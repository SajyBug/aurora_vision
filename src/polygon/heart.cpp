/* 
 * @File:     heart.cpp
 * @Author:   Sajjad Rahnama , Hossein Hojat Ansari
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created  2016
 */

#include "heart.h"

Heart::Heart()
{
  row = col = 0;
  heart.clear();
}

float calculateDistance(const vector<Point2f>& p1, const Point& p2)
{
  float diffY = p1[0].y - p2.y;
  float diffX = p1[0].x - p2.x;
  return sqrt((diffY * diffY) + (diffX * diffX));
}

aurora_vision::heart Heart::recognize(Mat &org_img)
{
  if (!heart_cascade.load(cascade))
  {
    printf("--(!)Error loading face cascade\n");
    exit(0);
  };

  cvtColor(org_img, gray, COLOR_BGR2GRAY);
  equalizeHist(gray, gray);
  detect();
  //  drawing(org_img);
  vector<Point2f> mc(1);
  Point inside(160, 120);
  if (heart.size())
  {
    cout << heart.size() << endl;
    Point center(heart[0].x + heart[0].width / 2, heart[0].y + heart[0].height / 2);
    putText(org_img, "heart", Point(10, 40), FONT_ITALIC, 1, cv::Scalar(212, 157, 34), 2);
    ellipse(org_img, center, Size(heart[0].width / 2, heart[0].height / 2), 0, 0, 360, Scalar(0, 0, 200), 4, 8, 0);
    std::cout << " X= " << (heart[0].x + heart[0].width / 2) << std::endl;
    std::cout << " Y= " << (heart[0].y + heart[0].height / 2) << std::endl;
    mc[0] = Point2f(static_cast<float> (heart[0].x + heart[0].width / 2), static_cast<float> (heart[0].y + heart[0].height / 2));
    line(org_img, mc[0], inside, cv::Scalar(0, 255, 0), 2);
    std::cout << calculateDistance(mc, inside) << std::endl;
    //    connector->send("ABC;");
    aurora_vision::heart hr;
    hr.X = (heart[0].x + heart[0].width / 2);
    hr.Y = (heart[0].y + heart[0].height / 2);
    hr.Distance = calculateDistance(mc, inside);
    heart.clear();
    return hr;
  }
  else
  {
    aurora_vision::heart hr1;
    hr1.X = 0;
    hr1.Y = 0;
    hr1.Distance = 0;
    heart.clear();
    return hr1;
  }
}

void Heart::detect()
{
  //-- Detect heart
  heart_cascade.detectMultiScale(gray, heart, 2, 4, 1.1, Size(20, 20));
}

void Heart::drawing(Mat &org_img)
{

}
