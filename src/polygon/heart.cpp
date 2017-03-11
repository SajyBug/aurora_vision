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

void Heart::drawing(Mat &org_img)
{
  for (size_t i = 0; i < heart.size(); i++)
  {
    cout << heart.size() << endl;
    Point center(heart[i].x + heart[i].width / 2, heart[i].y + heart[i].height / 2);
    ellipse(org_img, center, Size(heart[i].width / 2, heart[i].height / 2), 0, 0, 360, Scalar(0, 0, 200), 4, 8, 0);

  }
}
