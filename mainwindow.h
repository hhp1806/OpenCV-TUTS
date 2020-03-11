#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <sstream>
#include <string>
#include <iostream>
#include <thread>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);


    int H_MIN, H_MAX, S_MIN, S_MAX, V_MIN, V_MAX;

    double area;
    double sideLength;

    const int WIDTH = 640;
    const int HEIGHT = 480;

    static const int MAX_OBJECTS = 20;

    const int MIN_OBJECT_AREA = 30 * 30;
    const int MAX_OBJECT_AREA = HEIGHT*WIDTH / 2;

    const string imageWindow = "Original Image";
    const string hsvWindow = "HSV Image";
    const string thresholdWindow = "Thresholded Image";
    bool breakLoop=false;

    Mat cameraFeed;

    Mat HSV;
    int x = 0, y = 0;

    VideoCapture capture;


    typedef struct {
        std::string name;
        int x;
        int y;
        int H_MIN= H_MIN;
        int H_MAX = H_MAX;
        int S_MIN= S_MIN;
        int S_MAX= S_MAX;
        int V_MIN= V_MIN;
        int V_MAX= V_MAX;
        Mat threshold;
    }item ;


    item testObject;

    vector<item> objects;

    void closeEvent (QCloseEvent *event);
    string numberToString(int number);
    void Start();
    void morphObject(Mat &thresh);
    void trackObject(int &x, int &y,  item tempItem, Mat &cameraFeed);
    item setUpObject(string name, int hmin, int hmax, int smin, int smax, int vmin, int vmax);

    //    void drawObject(int x, int y, cv::Mat &frame, item tempItem);

    ~MainWindow();

private slots:

    void on_addButton_clicked();

    void on_defaultButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
