
/* 
 * @File:     main.cpp
 * @Author:   Sajjad Rahnama , Hossein Hojat Ansari
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created  2016
 */

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