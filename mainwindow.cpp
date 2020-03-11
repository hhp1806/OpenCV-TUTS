#include "mainwindow.h"
#include "ui_mainwindow.h"


using namespace cv;
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    capture.open(0);

    capture.set(CAP_PROP_FRAME_WIDTH, WIDTH);
    capture.set(CAP_PROP_FRAME_HEIGHT, HEIGHT);

    namedWindow(imageWindow);
    namedWindow(hsvWindow);
    namedWindow(thresholdWindow);

    moveWindow(imageWindow,100,0);
    moveWindow(hsvWindow, 1000,0);
    moveWindow(thresholdWindow, 1000,500);

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    breakLoop=true;
    destroyAllWindows();
    capture.~VideoCapture();
    this->destroy();
    event->accept();
}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::Start(){

    while (true){

        if(breakLoop==true){
            return;
        }
        H_MIN = ui->hminBox->text().toInt();
        H_MAX = ui->hmaxBox->text().toInt();
        S_MIN = ui->sminBox->text().toInt();
        S_MAX = ui->smaxBox->text().toInt();
        V_MIN = ui->vminBox->text().toInt();
        V_MAX = ui->vmaxBox->text().toInt();


        capture.read(cameraFeed);
        testObject.name="Default";
        cvtColor(cameraFeed,HSV, COLOR_BGR2HSV);
        inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), testObject.threshold);
        morphObject(testObject.threshold);
        trackObject(x, y, testObject, cameraFeed);

        for (unsigned int i = 0; i<objects.size(); i++) {
            inRange(HSV, Scalar(objects[i].H_MIN, objects[i].S_MIN, objects[i].V_MIN), Scalar(objects[i].H_MAX, objects[i].S_MAX, objects[i].V_MAX), objects[i].threshold);
            morphObject(objects[i].threshold);
            trackObject(x, y, objects[i], cameraFeed);
        }
        imshow(imageWindow, cameraFeed);
        imshow(hsvWindow, HSV);
        imshow(thresholdWindow,testObject.threshold);
        waitKey(30);
    }


}

string MainWindow::numberToString(int number){
   stringstream ss;
   ss << number;
   return ss.str();
}


//void MainWindow::drawObject(int x, int y, Mat &frame, item tempItem){

//    rectangle(frame,Point(x-(sideLength/2),y-(sideLength/2)), Point(x+(sideLength/2),y+(sideLength/2)),Scalar(0,255,0),2);

//    putText(frame, numberToString(x) + "," + numberToString(y), Point(x, y + 30), 1, 1, Scalar(0,72, 255), 1);
//    putText(frame, tempItem.name , Point(x, y + 50), 2, 1, Scalar(0,72, 255), 1);
//}

void MainWindow::morphObject(Mat &thresh){

    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));

    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

    erode(thresh, thresh, erodeElement);
    erode(thresh, thresh, erodeElement);
    dilate(thresh, thresh, dilateElement);
    dilate(thresh, thresh, dilateElement);



}
void MainWindow::trackObject(int &x, int &y, item tempItem, Mat &cameraFeed){

    Mat temp;
    tempItem.threshold.copyTo(temp);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(temp, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
    vector<RotatedRect> minRect(contours.size());


    double refArea = 0;

    bool objectFound = false;
    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();
        if (numObjects<MAX_OBJECTS){
            for (int i = 0; i >= 0; i = hierarchy[i][0]) {

                Moments moment = moments((Mat)contours[i]);
                area = moment.m00;
                sideLength= sqrt(area);
                minRect[i] = minAreaRect(Mat(contours[i]));

                if (area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
                    x = moment.m10 / area;
                    y = moment.m01 / area;
                    objectFound = true;
                    refArea = area;
                }
                else objectFound = false;
            }

            if (objectFound == true){
                for (int i = 0; i >= 0; i = hierarchy[i][0])
                {
                    double cnt_area = contourArea( contours[i] );
                    if (cnt_area > 5000 && cnt_area < 100000)
                    {

                        Point2f rect_points[4];
                        float angle;
                        minRect[i].points( rect_points );
                        for(int j = 0; j < 4; j++)
                        {
                               line(cameraFeed, rect_points[j], rect_points[(j+1)%4], Scalar(0,255,0), 2, 8 );
                        }

                        angle = minRect[i].angle;
                        if(minRect[i].size.width < minRect[i].size.height)
                        {
                            angle = angle + 180;
                        }

                        else
                        {
                            angle = angle + 90;
                        }

                        putText(cameraFeed, numberToString(x) + "," + numberToString(y) + ";" + numberToString(angle), Point(x, y + 30), 1, 1, Scalar(0,72, 255), 1);
                        putText(cameraFeed, tempItem.name , Point(x, y + 50), 2, 1, Scalar(0,72, 255), 1);
                    }

                }
            }
        }
    }
}


MainWindow::item MainWindow::setUpObject(string name, int hmin, int hmax, int smin, int smax, int vmin, int vmax){

    item temp;
    temp.name = name;
    //temp.x = x;
    //temp.y = y;
    temp.H_MIN = hmin;
    temp.H_MAX = hmax;
    temp.S_MIN = smin;
    temp.S_MAX = smax;
    temp.V_MIN = vmin;
    temp.V_MAX = vmax;

    return temp;

}

void MainWindow::on_addButton_clicked()
{
    objects.push_back(setUpObject(ui->nameLineEdit->text().toStdString(),H_MIN,H_MAX,S_MIN,S_MAX,V_MIN,V_MAX));
    ui->nameLineEdit->clear();
}

void MainWindow::on_defaultButton_clicked()
{
    ui->hminBox->setValue(0);
    ui->hmaxBox->setValue(255);
    ui->sminBox->setValue(0);
    ui->smaxBox->setValue(255);
    ui->vminBox->setValue(0);
    ui->vmaxBox->setValue(255);

}
