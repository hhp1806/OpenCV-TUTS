#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->sld_highH, SIGNAL(valueChanged(int)), ui->spb_highH, SLOT(setValue(int)));
    QObject::connect(ui->spb_highH, SIGNAL(valueChanged(int)), ui->sld_highH, SLOT(setValue(int)));

    QObject::connect(ui->sld_highS, SIGNAL(valueChanged(int)), ui->spb_highS, SLOT(setValue(int)));
    QObject::connect(ui->spb_highS, SIGNAL(valueChanged(int)), ui->sld_highS, SLOT(setValue(int)));

    QObject::connect(ui->sld_highV, SIGNAL(valueChanged(int)), ui->spb_highV, SLOT(setValue(int)));
    QObject::connect(ui->spb_highV, SIGNAL(valueChanged(int)), ui->sld_highV, SLOT(setValue(int)));

    ui->sld_highH->setRange(0,179);
    ui->sld_highS->setRange(0,255);
    ui->sld_highV->setRange(0,255);

    ui->spb_highH->setRange(0,179);
    ui->spb_highS->setRange(0,255);
    ui->spb_highV->setRange(0,255);

    ui->spb_highH->setValue(0);
    ui->spb_highS->setValue(0);
    ui->spb_highV->setValue(0);


    QObject::connect(ui->sld_lowH, SIGNAL(valueChanged(int)), ui->spb_lowH, SLOT(setValue(int)));
    QObject::connect(ui->spb_lowH, SIGNAL(valueChanged(int)), ui->sld_lowH, SLOT(setValue(int)));

    QObject::connect(ui->sld_lowS, SIGNAL(valueChanged(int)), ui->spb_lowS, SLOT(setValue(int)));
    QObject::connect(ui->spb_lowS, SIGNAL(valueChanged(int)), ui->sld_lowS, SLOT(setValue(int)));

    QObject::connect(ui->sld_lowV, SIGNAL(valueChanged(int)), ui->spb_lowV, SLOT(setValue(int)));
    QObject::connect(ui->spb_lowV, SIGNAL(valueChanged(int)), ui->sld_lowV, SLOT(setValue(int)));

    ui->sld_lowH->setRange(0,179);
    ui->sld_lowS->setRange(0,255);
    ui->sld_lowV->setRange(0,255);

    ui->spb_lowH->setRange(0,179);
    ui->spb_lowS->setRange(0,255);
    ui->spb_lowV->setRange(0,255);

    ui->spb_lowH->setValue(0);
    ui->spb_lowS->setValue(0);
    ui->spb_lowV->setValue(0);

    timer = new QTimer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_open_clicked()
{
    cap.open(0);
    if(!cap.isOpened())
    {
        cout << "camera is not open" << endl;
    }
    else
    {
        cout << "camera is open" << endl;
        connect(timer, SIGNAL(timeout()), this, SLOT(update_window()));
        timer->start(20);
    }

}

void MainWindow::on_btn_close_clicked()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(update_window()));
    cap.release();
    Mat image = Mat::zeros(frame.size(),CV_8UC3);
    qt_image = QImage((const unsigned char*) (image.data), image.cols, image.rows, QImage::Format_RGB888);
    ui->lbl_cam->setPixmap(QPixmap::fromImage(qt_image));
    ui->lbl_cam->resize(ui->lbl_cam->pixmap()->size());
    cout << "camera is closed" << endl;
}

void MainWindow::update_window()
{
    cap >> frame;
//    QImage qt_image;
//    cvtColor(frame, frame, COLOR_BGR2RGB);
//    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
//    ui->lbl_cam->setPixmap(QPixmap::fromImage(qt_image));
//    ui->lbl_cam->resize(ui->lbl_cam->pixmap()->size());
    imshow("Webcam", frame);
}




void MainWindow::on_sld_lowH_sliderMoved()
{
    cap.open(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_window_detect()));
    timer->start(20);

}

void MainWindow::on_sld_lowS_sliderMoved()
{
    cap.open(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_window_detect()));
    timer->start(20);
}

void MainWindow::on_sld_lowV_sliderMoved()
{
    cap.open(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_window_detect()));
    timer->start(20);

}

void MainWindow::on_sld_highH_sliderMoved()
{
    cap.open(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_window_detect()));
    timer->start(20);

}

void MainWindow::on_sld_highS_sliderMoved()
{
    cap.open(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_window_detect()));
    timer->start(20);

}

void MainWindow::on_sld_highV_sliderMoved()
{
    cap.open(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_window_detect()));
    timer->start(20);
}

void MainWindow::update_window_detect()
{
    cap >> frame;
    QImage qt_image;
    Mat frame_hsv;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    cvtColor(frame, frame_hsv, COLOR_BGR2HSV);
    inRange(frame_hsv, Scalar(ui->sld_lowH->value(), ui->sld_lowS->value(), ui->sld_lowV->value()), Scalar(ui->sld_highH->value(), ui->sld_highS->value(), ui->sld_highV->value()), frame_hsv);
//    inRange(frame_hsv, Scalar(22, 50, 50), Scalar(38, 255, 255), frame_hsv);
    findContours(frame_hsv, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    vector<RotatedRect> minRect( contours.size() );
    for(size_t i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(0,255,0);
        minRect[i] = minAreaRect(Mat(contours[i]));
        double area = contourArea( contours[i] );
        if (area > 2000 && area < 30000)
        {
            Point2f rect_points[4];
            Point2f center;
            float angle;
            minRect[i].points( rect_points );
            for( int j = 0; j < 4; j++ )
            {
                line(frame, rect_points[j], rect_points[(j+1)%4], color, 1, 8 );
            }

            center = (rect_points[0] + rect_points[3])/2;
            angle = minRect[i].angle;
            if(minRect[i].size.width < minRect[i].size.height)
            {
                angle = angle + 180;
            }
            else
            {
                angle = angle + 90;
            }
            stringstream str_center;
            str_center << "( " << center.x << "," << center.y << ")";
            string string = to_string(angle) + "  " + str_center.str();
            putText(frame, string, center, FONT_HERSHEY_DUPLEX, 1, color, 1, LINE_AA, false);

//            cout << center << endl;
//            cout << angle << endl;

        }
    }

//    cvtColor(frame, frame, COLOR_BGR2RGB);
//    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
//    ui->lbl_cam->setPixmap(QPixmap::fromImage(qt_image));
//    ui->lbl_cam->resize(ui->lbl_cam->pixmap()->size());
    imshow("Webcam", frame);

}


