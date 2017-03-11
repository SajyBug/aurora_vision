#include "chess_shape.h"

Chess_shape::Chess_shape()
{
  row = col = 0;
  chess_shape.clear();
}

void Chess_shape::recognize(Mat &org_img)
{
  if (!chess_shape_cascade.load(cascade))
  {
    printf("--(!)Error loading face cascade\n");
    exit(0);
  };

  cvtColor(org_img, gray, COLOR_BGR2GRAY);
  equalizeHist(gray, gray);
  detect();
  drawing(org_img);
}

void Chess_shape::detect()
{
  //-- Detect Chess shape
  chess_shape_cascade.detectMultiScale(gray, chess_shape, 2, 4, 1.1, Size(20, 20));
}

void Chess_shape::drawing(Mat &org_img)
{
  for (size_t i = 0; i < chess_shape.size(); i++)
  {
    Point center(chess_shape[i].x + chess_shape[i].width / 2, chess_shape[i].y + chess_shape[i].height / 2);
    ellipse(org_img, center, Size(chess_shape[i].width / 2, chess_shape[i].height / 2), 0, 0, 360, Scalar(0, 0, 200), 4, 8, 0);

  }
}
