#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "QFileDialog"

#include <string>
#include <cstring>
#include <QWidget>
#include <QColor>
#include <QTimer>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
//    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_img_clicked();
    void on_btn_defimg_clicked();
    void on_btn_gray_clicked();
    void on_sld_value_sliderMoved();
    void on_sld_type_sliderMoved();

//    void onColorChanged();

//    void on_btn_hsv_clicked();

    void on_sld_upred_sliderMoved();

    void on_sld_upbl_sliderMoved();

    void on_sld_upgr_sliderMoved();

    void on_sld_lowred_sliderMoved();

    void on_sld_lowbl_sliderMoved();

    void on_sld_lowgr_sliderMoved();

    void on_sld_blur_sliderMoved(int position);

    void on_btn_open_clicked();

    void on_btn_close_clicked();

    void update_window();

    void update_window_gray();

    void update_window_threshold();

    void update_window_hsv();

    void update_window_blur0();

    void update_window_blur1();

    void update_window_blur2();

    void update_window_blur3();





private:
    Ui::MainWindow *ui;

    QTimer *timer;
    VideoCapture cap;

    Mat frame;
    QImage qt_image;


};
#endif // MAINWINDOW_H
