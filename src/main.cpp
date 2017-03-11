#include "mainwindow.h"
#include <QApplication>
#include <ros/ros.h>

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "aurora_vision");
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  ros::spin();

  return a.exec();
}