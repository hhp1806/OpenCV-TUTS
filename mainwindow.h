#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "QFileDialog"

#include <string>
#include <cstring>
#include <QWidget>
#include <QColor>
#include <QTimer>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_open_clicked();

    void on_btn_close_clicked();

    void update_window();

    void on_sld_lowH_sliderMoved();

    void on_sld_lowS_sliderMoved();

    void on_sld_lowV_sliderMoved();

    void on_sld_highH_sliderMoved();

    void on_sld_highS_sliderMoved();

    void on_sld_highV_sliderMoved();

    void update_window_detect();

private:
    Ui::MainWindow *ui;

    QTimer *timer;
    VideoCapture cap;

    Mat frame;
    QImage qt_image;


};
#endif // MAINWINDOW_H
