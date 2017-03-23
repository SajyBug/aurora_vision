#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include "filter.h"
#include "polygon.h"

using namespace std;
using namespace cv;

set_on data_indoor[10]; //baraye preview && save data
int currentRow = 0;
unsigned int close_ = 0;

QString logo_addres = ":/source/logo.png";
QString indoor_file = "/home/sajjadtest/Desktop/indoor_file.txt";
QString name_item_indoor;
string line_data;
Mat original;
bool thershold = false;
Polygon polygon;
image_transport::Publisher image_pub_;

bool triangle = false;
bool square = false;
bool circle1 = false;
bool pentagon = false;
bool star = false;
bool heart = false;
bool chess_shape1 = false;
bool outdoor = false;
bool rviz = false;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  it_(nh_)
{
  ui->setupUi(this);

  polygon = Polygon();

  QPixmap logo(logo_addres);
  ui->logo_lable->setPixmap(logo);
  ui->data_Adrs_lineEdit->setText(indoor_file);
  ui->lineEdit_indoor->setPlaceholderText("Item Name"); //line edit plac

  image_sub_ = it_.subscribe("/ardrone/bottom/image_raw", 1, &MainWindow::imageCb, this);
  image_pub_ = it_.advertise("/vision/image", 1);
  connect(ui->triangle_cb, SIGNAL(stateChanged(int)), this, SLOT(traingle_cb(int)));
  connect(ui->square_cb, SIGNAL(stateChanged(int)), this, SLOT(square_cb(int)));
  connect(ui->circle_cb, SIGNAL(stateChanged(int)), this, SLOT(circle_cb(int)));
  connect(ui->pentagon_cb, SIGNAL(stateChanged(int)), this, SLOT(pentagon_cb(int)));
  connect(ui->star_cb, SIGNAL(stateChanged(int)), this, SLOT(star_cb(int)));
  connect(ui->heart_cb, SIGNAL(stateChanged(int)), this, SLOT(heart_cb(int)));
  connect(ui->chess_shape_cb, SIGNAL(stateChanged(int)), this, SLOT(chess_shape(int)));
  connect(ui->outdoor_cb, SIGNAL(stateChanged(int)), this, SLOT(outdoor_cb(int)));
  connect(ui->rviz_cb, SIGNAL(stateChanged(int)), this, SLOT(rviz_cb(int)));
  ui->set_state_label_indoor->setText("default");
  ui->set_state_label_indoor->setStyleSheet("QLabel { color : blue; }");
  data_indoor[0].name_item = "default";
  data_indoor[0].h_low = 0;
  data_indoor[0].h_high = 179;
  data_indoor[0].s_low = 0;
  data_indoor[0].s_high = 255;
  data_indoor[0].v_low = 0;
  data_indoor[0].v_high = 255;
  data_indoor[0].item_row = 0;

}

void MainWindow::traingle_cb(int a)
{
  if (a)
    triangle = true;
  else
    triangle = false;
}

void MainWindow::square_cb(int a)
{
  if (a)
    square = true;
  else
    square = false;
}

void MainWindow::circle_cb(int a)
{
  if (a)
    circle1 = true;
  else
    circle1 = false;
}

void MainWindow::pentagon_cb(int a)
{
  if (a)
    pentagon = true;
  else
    pentagon = false;
}

void MainWindow::star_cb(int a)
{
  if (a)
    star = true;
  else
    star = false;
}

void MainWindow::heart_cb(int a)
{
  if (a)
    heart = true;
  else
    heart = false;
}

void MainWindow::chess_shape(int a)
{
  if (a)
    chess_shape1 = true;
  else
    chess_shape1 = false;
}

void MainWindow::outdoor_cb(int a)
{
  if (a)
    outdoor = true;
  else
    outdoor = false;
}

void MainWindow::rviz_cb(int a)
{
  if (a)
    rviz = true;
  else
    rviz = false;
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::imageCb(const sensor_msgs::ImageConstPtr& msg)
{
  cv_bridge::CvImagePtr cv_ptr;
  try
  {
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }
  original = cv_ptr->image;
  //  cv::imshow("original", original);
  cv::waitKey(3);
}

void MainWindow::on_submit_pb_clicked()
{
  indoor_file = ui->data_Adrs_lineEdit->text();
  on_load_pb_indoor_clicked();
  if (ui->listWidget_indoor->count() != 0)
    ui->item_lb_indoor->clear();
}

void MainWindow::on_data_Adrs_lineEdit_returnPressed()
{
  on_submit_pb_clicked();
}

void MainWindow::on_add_pb_indoor_clicked()
{
  if (ui->lineEdit_indoor->text().isEmpty()) //empty line edit warning
  {
    ui->item_lb_indoor->setText("Name is empty");
    ui->item_lb_indoor->setStyleSheet("QLabel { color : red; }");
  }
  else
  {
    //Add new item
    name_item_indoor = ui->lineEdit_indoor->text();
    ui->listWidget_indoor->addItem(name_item_indoor);

    currentRow = ui->listWidget_indoor->count() - 1;
    data_indoor[currentRow].item_row = currentRow;
    data_indoor[currentRow].name_item = name_item_indoor.toStdString();
    data_indoor[currentRow].h_low = ui->h_low_s_indoor->value();
    data_indoor[currentRow].h_high = ui->h_high_s_indoor->value();
    data_indoor[currentRow].s_low = ui->s_low_s_indoor->value();
    data_indoor[currentRow].s_high = ui->s_high_s_indoor->value();
    data_indoor[currentRow].v_low = ui->v_low_s_indoor->value();
    data_indoor[currentRow].v_high = ui->v_high_s_indoor->value();

    ui->listWidget_indoor->setCurrentRow(currentRow);

    //clear line edit & indoor_error lable
    ui->lineEdit_indoor->clear();
    ui->item_lb_indoor->clear();
  }
}

void MainWindow::on_lineEdit_indoor_returnPressed()
{
  on_add_pb_indoor_clicked(); //add item
}

void MainWindow::on_remove_pb_indoor_clicked()
{
  if (data_indoor[currentRow].name_item == ui->set_state_label_indoor->text().toStdString()) //clear "set on" labale when delet its item
    ui->set_state_label_indoor->clear();

  qDeleteAll(ui->listWidget_indoor->selectedItems()); //delete select item

  if (currentRow == ui->listWidget_indoor->count()) //[Bug maskhare]: agar khastim akharin item ro delete konim
    currentRow += 1;
  else // agar khastim az vasate hazf konim
  {
    for (; currentRow <= ui->listWidget_indoor->count() - 1; currentRow++)
    {
      data_indoor[currentRow].item_row = data_indoor[currentRow + 1].item_row;
      data_indoor[currentRow].name_item = data_indoor[currentRow + 1].name_item;
      data_indoor[currentRow].h_low = data_indoor[currentRow + 1].h_low;
      data_indoor[currentRow].h_high = data_indoor[currentRow + 1].h_high;
      data_indoor[currentRow].s_low = data_indoor[currentRow + 1].s_low;
      data_indoor[currentRow].s_high = data_indoor[currentRow + 1].s_high;
      data_indoor[currentRow].v_low = data_indoor[currentRow + 1].v_low;
      data_indoor[currentRow].v_high = data_indoor[currentRow + 1].v_high;
    }
  }
  ui->listWidget_indoor->setCurrentRow(ui->listWidget_indoor->count() - 1); //raf'e bug feshar dadan click remove dar itemhaye bala :S

}

void MainWindow::on_listWidget_indoor_pressed(const QModelIndex &index)
{
  currentRow = index.row(); //item row
  data_indoor[currentRow].item_row = currentRow;
  ui->h_low_s_indoor->setValue(data_indoor[currentRow].h_low);
  ui->h_high_s_indoor->setValue(data_indoor[currentRow].h_high);
  ui->s_low_s_indoor->setValue(data_indoor[currentRow].s_low);
  ui->s_high_s_indoor->setValue(data_indoor[currentRow].s_high);
  ui->v_low_s_indoor->setValue(data_indoor[currentRow].v_low);
  ui->v_high_s_indoor->setValue(data_indoor[currentRow].v_high);
  name_item_indoor = QString::fromStdString(data_indoor[currentRow].name_item);
  ui->set_state_label_indoor->setText(name_item_indoor);
}

void MainWindow::on_save_pb_indoor_clicked()
{
  fstream file;
  int v = ui->listWidget_indoor->currentRow();

  if (ui->listWidget_indoor->count() == 0)
  { //clear extera text when we have'nt item
    ofstream ofs(indoor_file.toStdString().c_str(), std::ios::out | std::ios::trunc); // clear content
    ofs.close();
  }
  else // else : save data
  {
    ui->listWidget_indoor->setCurrentRow(0);
    currentRow = ui->listWidget_indoor->currentIndex().row();

    std::ofstream ofs(indoor_file.toStdString().c_str(), std::ios::out | std::ios::trunc); // clear content
    file.open(indoor_file.toStdString().c_str());

    //save data
    for (; currentRow <= ui->listWidget_indoor->count() - 1; currentRow++)
    {
      file << data_indoor[currentRow].item_row << " " << data_indoor[currentRow].name_item << " " <<
        data_indoor[currentRow].h_low << " " << data_indoor[currentRow].h_high << " " <<
        data_indoor[currentRow].s_low << " " << data_indoor[currentRow].s_high << " " <<
        data_indoor[currentRow].v_low << " " << data_indoor[currentRow].v_high << endl;
    }
    file.close();
    ofs.close();
  }
  ui->listWidget_indoor->setCurrentRow(v); //select new item (raf'e bug  :O :|)
  QModelIndex index_item;
  index_item = ui->listWidget_indoor->currentIndex();
  on_listWidget_indoor_pressed(index_item);
}

void MainWindow::on_load_pb_indoor_clicked()
{
  fstream file;
  //counting all of files line
  ifstream ifile(indoor_file.toStdString().c_str());
  string line;
  int c_line = 0;
  while (std::getline(ifile, line))
    c_line++;

  if (c_line != 0) // agar data dashtim
  {
    file.open(indoor_file.toStdString().c_str()); //load database
    ui->listWidget_indoor->clear();
    for (currentRow = 0; currentRow < c_line; currentRow++)
    {
      file >> data_indoor[currentRow].item_row >> data_indoor[currentRow].name_item
        >> data_indoor[currentRow].h_low >> data_indoor[currentRow].h_high
        >> data_indoor[currentRow].s_low >> data_indoor[currentRow].s_high
        >> data_indoor[currentRow].v_low >> data_indoor[currentRow].v_high;

      name_item_indoor = QString::fromStdString(data_indoor[currentRow].name_item);

      ui->listWidget_indoor->addItem(name_item_indoor);
      ui->h_low_s_indoor->setValue(data_indoor[currentRow].h_low);
      ui->h_high_s_indoor->setValue(data_indoor[currentRow].h_high);
      ui->s_low_s_indoor->setValue(data_indoor[currentRow].s_low);
      ui->s_high_s_indoor->setValue(data_indoor[currentRow].s_high);
      ui->v_low_s_indoor->setValue(data_indoor[currentRow].v_low);
      ui->v_high_s_indoor->setValue(data_indoor[currentRow].v_high);
    }
    file.close();
  }

  if (ui->listWidget_indoor->count() == 0) //when database is empty
  {
    ui->item_lb_indoor->setText(" Data not found ");
    ui->item_lb_indoor->setStyleSheet("QLabel { color : red; }");
  }
}

void MainWindow::on_h_low_s_indoor_valueChanged(int value)
{
  data_indoor[currentRow].h_low = value;
  ui->h_low_value->setText(QString::number(value));
}

void MainWindow::on_h_high_s_indoor_valueChanged(int value)
{
  data_indoor[currentRow].h_high = value;
  ui->h_high_value->setText(QString::number(value));
}

void MainWindow::on_s_low_s_indoor_valueChanged(int value)
{
  data_indoor[currentRow].s_low = value;
  ui->s_low_value->setText(QString::number(value));
}

void MainWindow::on_s_high_s_indoor_valueChanged(int value)
{
  data_indoor[currentRow].s_high = value;
  ui->s_high_value->setText(QString::number(value));
}

void MainWindow::on_v_low_s_indoor_valueChanged(int value)
{
  data_indoor[currentRow].v_low = value;
  ui->v_low_value->setText(QString::number(value));
}

void MainWindow::on_v_high_s_indoor_valueChanged(int value)
{
  data_indoor[currentRow].v_high = value;
  ui->v_high_value->setText(QString::number(value));
}

void MainWindow::on_pre_cb_indoor_clicked()
{
  if (ui->pre_cb_indoor->checkState())
    thershold = true;
  else
    thershold = false;
}

void MainWindow::on_open_cam_indoor_clicked()
{
  thread.start();
}

void MainWindow::on_close_cam_indoor_clicked()
{
  close_++;
  if (close_ > 1)
    close_ = 0;
}

void MainWindow::Thread::run()
{
  Mat org_img, thr_img, thr_img1, hsv_img;
  cv_bridge::CvImage Cvptr;
  Cvptr.encoding = sensor_msgs::image_encodings::BGR8;
  while (true)
  {
    org_img = original;
    if (thershold)
    {
      cvtColor(org_img, hsv_img, CV_BGR2HSV); //Convert the captured frame from BGR to HSV
      inRange(hsv_img, Scalar(data_indoor[currentRow].h_low, data_indoor[currentRow].s_low, data_indoor[currentRow].v_low),
        Scalar(data_indoor[currentRow].h_high, data_indoor[currentRow].s_high, data_indoor[currentRow].v_high), thr_img1); //Threshold the image

      if (!rviz)
        imshow("Outdoor Shape", thr_img1);
    }
    else
    {
      hsv_thresholding(org_img, thr_img, data_indoor[currentRow]);

      if (triangle)
        polygon.getTriangle().recognize(org_img, thr_img);

      if (square)
        polygon.getSquare().recognize(org_img, thr_img);

      if (circle1)
        polygon.getCircle().recognize(org_img, thr_img);

      if (pentagon)
        polygon.getPentagon().recognize(org_img, thr_img);

      if (star)
        polygon.getStar().recognize(org_img, thr_img);

      if (heart)
        polygon.getHeart().recognize(org_img);

      if (chess_shape1)
        polygon.getChess_shape().recognize(org_img);

      if (outdoor)
        polygon.getH_shape().recognize(org_img);

      if (!rviz)
        imshow("Outdoor Shape", org_img);
    }

    Cvptr.image = org_img;
    if (rviz)
    {
      image_pub_.publish(Cvptr.toImageMsg());
      destroyAllWindows();
    }

    if (close_ > 0)
    {
      close_ = 0;
      destroyAllWindows();
      break;
    }
  }
}


