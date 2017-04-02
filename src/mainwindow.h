/* 
 * @File:     mainwindow.h
 * @Author:   Sajjad Rahnama , Hossein Hojat Ansari
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created  2016
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QMessageBox>
#include <QModelIndex>
#include <QString>
#include <fstream>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <QThread>
#include <aurora_vision/heart.h>


using namespace std;
using namespace cv;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void imageCb(const sensor_msgs::ImageConstPtr& msg);
    ~MainWindow();

    class Thread : public QThread {
    public:
        Thread();
        void run();
    private:
        ros::NodeHandle nh2_;
        ros::Publisher heart_pub;
    };

private slots:
    void on_submit_pb_clicked();
    void on_add_pb_indoor_clicked();
    void on_lineEdit_indoor_returnPressed();
    void on_remove_pb_indoor_clicked();
    void on_listWidget_indoor_pressed(const QModelIndex &index);
    void on_save_pb_indoor_clicked();
    void traingle_cb(int);
    void square_cb(int);
    void circle_cb(int);
    void pentagon_cb(int);
    void star_cb(int);
    void heart_cb(int);
    void chess_shape(int);
    void outdoor_cb(int);
    void rviz_cb(int);
    void on_load_pb_indoor_clicked();
    void on_h_low_s_indoor_valueChanged(int value);
    void on_h_high_s_indoor_valueChanged(int value);
    void on_s_low_s_indoor_valueChanged(int value);
    void on_s_high_s_indoor_valueChanged(int value);
    void on_v_low_s_indoor_valueChanged(int value);
    void on_v_high_s_indoor_valueChanged(int value);
    void on_pre_cb_indoor_clicked();
    void on_open_cam_indoor_clicked();
    void on_close_cam_indoor_clicked();
    void on_data_Adrs_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    Thread thread;
};

struct set_on {
    string name_item;
    int item_row, h_low, h_high, s_low, s_high, v_low, v_high;
};


#endif // MAINWINDOW_H
