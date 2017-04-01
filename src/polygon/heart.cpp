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

void Heart::recognize(Mat &org_img)
{
  if (!heart_cascade.load(cascade))
  {
    printf("--(!)Error loading face cascade\n");
    exit(0);
  };

  cvtColor(org_img, gray, COLOR_BGR2GRAY);
  equalizeHist(gray, gray);
  detect();
  drawing(org_img);
}

void Heart::detect()
{
  //-- Detect heart
  heart_cascade.detectMultiScale(gray, heart, 2, 4, 1.1, Size(20, 20));
}

float calculateDistance(const vector<Point2f>& p1, const Point& p2)
{
  float diffY = p1[0].y - p2.y;
  float diffX = p1[0].x - p2.x;
  return sqrt((diffY * diffY) + (diffX * diffX));
}

void Heart::drawing(Mat &org_img)
{
  vector<Point2f> mc(1);
  Point inside(160, 120);
  for (size_t i = 0; i < heart.size(); i++)
  {
    cout << heart.size() << endl;
    Point center(heart[i].x + heart[i].width / 2, heart[i].y + heart[i].height / 2);
    putText(org_img, "heart", Point(10, 40), FONT_ITALIC, 1, cv::Scalar(212, 157, 34), 2);
    ellipse(org_img, center, Size(heart[i].width / 2, heart[i].height / 2), 0, 0, 360, Scalar(0, 0, 200), 4, 8, 0);
    std::cout << " X= " << (heart[i].x + heart[i].width / 2)<< std::endl;
    std::cout << " Y= " << (heart[i].y + heart[i].height / 2) << std::endl;
    mc[0] = Point2f(static_cast<float> (heart[i].x + heart[i].width / 2), static_cast<float> (heart[i].y + heart[i].height / 2));
    line(org_img, mc[0], inside, cv::Scalar(0, 255, 0), 2);
    std::cout << calculateDistance(mc, inside) << std::endl;
//    connector->send("ABC;");

  }
}
