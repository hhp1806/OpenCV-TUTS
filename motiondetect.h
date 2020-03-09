#ifndef MOTIONDETECT_H
#define MOTIONDETECT_H

#include <QMainWindow>
#include "QFileDialog"
#include <QMessageBox>
#include <QWidget>
#include <QColor>
#include <QTimer>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MotionDetect; }
QT_END_NAMESPACE

class MotionDetect : public QMainWindow
{
    Q_OBJECT

public:
    MotionDetect(QWidget *parent = nullptr);

    ~MotionDetect();

private slots:
    void on_btn_vid_clicked();



    void on_btn_detect_clicked();

private:
    Ui::MotionDetect *ui;

    QTimer *timer;
    VideoCapture cap;

    Mat frame;
    QImage qt_image;
};
#endif // MOTIONDETECT_H
