#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "asmOpenCV.h"

#include <QPalette>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace ASM;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->btn_img->setVisible(false);
    ui->btn_defimg->setVisible(false);

    QObject::connect(ui->spb_value, SIGNAL(valueChanged(int)), ui->sld_value, SLOT(setValue(int)));
    QObject::connect(ui->sld_value, SIGNAL(valueChanged(int)), ui->spb_value, SLOT(setValue(int)));

    QObject::connect(ui->spb_type, SIGNAL(valueChanged(int)), ui->sld_type, SLOT(setValue(int)));
    QObject::connect(ui->sld_type, SIGNAL(valueChanged(int)), ui->spb_type, SLOT(setValue(int)));

    ui->sld_type->setRange(0,4);
    ui->sld_value->setRange(0,255);
    ui->spb_type->setRange(0,4);
    ui->spb_value->setRange(0,255);

    ui->spb_type->setValue(0);
    ui->spb_value->setValue(0);


    QObject::connect(ui->sld_upred, SIGNAL(valueChanged(int)), ui->spb_upred, SLOT(setValue(int)));
    QObject::connect(ui->spb_upred, SIGNAL(valueChanged(int)), ui->sld_upred, SLOT(setValue(int)));

    QObject::connect(ui->sld_upgr, SIGNAL(valueChanged(int)), ui->spb_upgr, SLOT(setValue(int)));
    QObject::connect(ui->spb_upgr, SIGNAL(valueChanged(int)), ui->sld_upgr, SLOT(setValue(int)));

    QObject::connect(ui->sld_upbl, SIGNAL(valueChanged(int)), ui->spb_upbl, SLOT(setValue(int)));
    QObject::connect(ui->spb_upbl, SIGNAL(valueChanged(int)), ui->sld_upbl, SLOT(setValue(int)));

    ui->sld_upred->setRange(0,179);
    ui->sld_upgr->setRange(0,255);
    ui->sld_upbl->setRange(0,255);

    ui->spb_upred->setRange(0,179);
    ui->spb_upgr->setRange(0,255);
    ui->spb_upbl->setRange(0,255);

    ui->spb_upred->setValue(0);
    ui->spb_upgr->setValue(0);
    ui->spb_upbl->setValue(0);


    QObject::connect(ui->sld_lowred, SIGNAL(valueChanged(int)), ui->spb_lowred, SLOT(setValue(int)));
    QObject::connect(ui->spb_lowred, SIGNAL(valueChanged(int)), ui->sld_lowred, SLOT(setValue(int)));

    QObject::connect(ui->sld_lowgr, SIGNAL(valueChanged(int)), ui->spb_lowgr, SLOT(setValue(int)));
    QObject::connect(ui->spb_lowgr, SIGNAL(valueChanged(int)), ui->sld_lowgr, SLOT(setValue(int)));

    QObject::connect(ui->sld_lowbl, SIGNAL(valueChanged(int)), ui->spb_lowbl, SLOT(setValue(int)));
    QObject::connect(ui->spb_lowbl, SIGNAL(valueChanged(int)), ui->sld_lowbl, SLOT(setValue(int)));

    ui->sld_lowred->setRange(0,179);
    ui->sld_lowgr->setRange(0,255);
    ui->sld_lowbl->setRange(0,255);

    ui->spb_lowred->setRange(0,179);
    ui->spb_lowgr->setRange(0,255);
    ui->spb_lowbl->setRange(0,255);

    ui->spb_lowred->setValue(0);
    ui->spb_lowgr->setValue(0);
    ui->spb_lowbl->setValue(0);


//    QObject::connect(ui->sld_upred, SIGNAL(valueChanged(int)), SLOT(onColorChanged()));
//    QObject::connect(ui->sld_upgr, SIGNAL(valueChanged(int)), SLOT(onColorChanged()));
//    QObject::connect(ui->sld_upbl, SIGNAL(valueChanged(int)), SLOT(onColorChanged()));

//    onColorChanged();

    QObject::connect(ui->spb_blur,SIGNAL(valueChanged(int)),ui->sld_blur,SLOT(setValue(int)) );
    QObject::connect(ui->sld_blur,SIGNAL(valueChanged(int)),ui->spb_blur,SLOT(setValue(int))) ;

    ui->spb_blur->setRange(0,3);
    ui->sld_blur->setRange(0,3);

    ui->spb_blur->setValue(0);
    ui->sld_blur->setValue(0);

    timer = new QTimer(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::onColorChanged()
//{
//    m_color.setRgb(ui->sld_upgr->value(), ui->sld_upgr->value(), ui->sld_upbl->value());
//    QPalette pal = ui->dis_up->palette();
//    pal.setColor(QPalette::Window, m_color);
//    ui->dis_up->setPalette(pal);
//    emit colorChanged(m_color);
//}

//QImage Mat2QImage(const cv::Mat &src)
//{
//    cv::Mat temp; // make the same cv::Mat
//         cvtColor(src, temp, cv::COLOR_BGR2RGB); // cvtColor Makes a copt, that what i need
//         QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
//         dest.bits(); // enforce deep copy, see documentation
//         // of QImage::QImage ( const uchar * data, int width, int height, Format format )
//         return dest;
//}

//cv::Mat QImage2Mat(const QImage &src)
//{
//    cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
//         cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
//         cvtColor(tmp, result,cv::COLOR_BGR2RGB);
//         return result;
//}

//void MainWindow::MatImg (const String& filename) {

//    cv::Mat image = cv::imread(const String& filename);

//    cv::namedWindow("My Image", WINDOW_FULLSCREEN);

//    cv::imshow("My Image", image);
//}

void MainWindow::on_btn_img_clicked()
{
    QImage img;
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "");
        if(QString::compare(filename, QString())!= 0)
        {

            bool valid = img.load(filename);
            if(valid)
            {
                const char* string = filename.toStdString().c_str();
                Mat image = cv::imread(string);
                namedWindow("My Image", WINDOW_FULLSCREEN);
                imshow("My Image", image);
                ui->lbl_img->setText("Open successfully");
                img = img.scaledToWidth(ui->lbl_img->width(), Qt::SmoothTransformation);
                ui->lbl_img->setPixmap(QPixmap::fromImage(img));
            }
            else
            {
                ui->lbl_img->setText("No image data");
            }

        }
}

void MainWindow::on_btn_defimg_clicked()
{

//    Mat image = imread("D:\\Pics\\Screens\\MVs\\charles.png");
//    namedWindow("My Image", WINDOW_FULLSCREEN);
//    imshow("My Image", image);
//    ui->lbl_img->setText("Open successfully");
    QImage img;
    img.load("D:\\Pics\\mata.jpg");
    img = img.scaledToWidth(ui->lbl_img->width(), Qt::SmoothTransformation);
    ui->lbl_img->setPixmap(QPixmap::fromImage(img));
    ui->btn_gray->setVisible(true);

}

void MainWindow::on_btn_gray_clicked()
{
//    const QPixmap* pixmap = ui->lbl_img->pixmap();
//    QImage image(pixmap->toImage());
//    Mat img = ASM::QImageToCvMat(image);
//    Mat dst;
//    cvtColor(img, dst, COLOR_BGR2GRAY);
//    cvtColor(dst,img,COLOR_BGR2RGB);
//    ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
    cap.open(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_window_gray()));
    timer->start(200);

}

void MainWindow::update_window_gray()
{
    cap >> frame;
    QImage qt_image;
    cvtColor(frame, frame, COLOR_BGR2GRAY);
    cvtColor(frame, frame, COLOR_BGR2RGB);
    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
    ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(qt_image));
    ui->lbl_img_Edit->resize(ui->lbl_img_Edit->pixmap()->size());

}



void MainWindow::on_sld_value_sliderMoved()
{
//    Mat src, src_gray, dst;
//    const QPixmap* pixmap = ui->lbl_img->pixmap();
//    QImage image(pixmap->toImage());
//    src = ASM::QImageToCvMat(image);
//    cvtColor(src, src_gray, COLOR_BGR2GRAY);
//    threshold(src_gray, dst, value, 255, ui->sld_type->value());
//    Mat img;
//    cvtColor(dst,img,COLOR_BGR2RGB);
//    ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));

    cap.open(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_window_threshold()));
    timer->start(200);
}



void MainWindow::on_sld_type_sliderMoved()
{
//    Mat src, src_gray, dst;
//    const QPixmap* pixmap = ui->lbl_img->pixmap();
//    QImage image(pixmap->toImage());
//    src = ASM::QImageToCvMat(image);
//    cvtColor(src, src_gray, COLOR_BGR2GRAY);
//    threshold(src_gray, dst, ui->sld_value->value(), 255, type);
//    Mat img;
//    cvtColor(dst,img,COLOR_BGR2RGB);
//    ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));

    cap.open(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_window_threshold()));
    timer->start(200);

}

void MainWindow::update_window_threshold()
{
    cap >> frame;
    QImage qt_image;
    cvtColor(frame, frame, COLOR_BGR2GRAY);
    threshold(frame, frame, ui->sld_value->value(), 255, ui->sld_type->value());
    cvtColor(frame, frame, COLOR_BGR2RGB);
    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
    ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(qt_image));
    ui->lbl_img_Edit->resize(ui->lbl_img_Edit->pixmap()->size());
}





void MainWindow::on_sld_upred_sliderMoved()
{
//    Mat src, src_hsv, dst;
//    const QPixmap* pixmap = ui->lbl_img->pixmap();
//    QImage image(pixmap->toImage());
//    src = ASM::QImageToCvMat(image);
//    cvtColor(src, src_hsv, COLOR_BGR2HSV);
//    inRange(src_hsv, Scalar(ui->sld_lowred->value(), ui->sld_lowbl->value(), ui->sld_lowgr->value()), Scalar(position, ui->sld_upbl->value(), ui->sld_upgr->value()), dst);
//    Mat img;
//    cvtColor(dst,img,COLOR_BGR2RGB);
//    ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
    cap.open(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_window_hsv()));
    timer->start(200);
}



void MainWindow::on_sld_upbl_sliderMoved()
{
//    Mat src, src_hsv, dst;
//    const QPixmap* pixmap = ui->lbl_img->pixmap();
//    QImage image(pixmap->toImage());
//    src = ASM::QImageToCvMat(image);
//    cvtColor(src, src_hsv, COLOR_BGR2HSV);
//    inRange(src_hsv, Scalar(ui->sld_lowred->value(), ui->sld_lowbl->value(), ui->sld_lowgr->value()), Scalar(ui->sld_upred->value(), position, ui->sld_upgr->value()), dst);
//    Mat img;
//    cvtColor(dst,img,COLOR_BGR2RGB);
//    ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
    cap.open(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_window_hsv()));
    timer->start(200);
}



void MainWindow::on_sld_upgr_sliderMoved()
{
//    Mat src, src_hsv, dst;
//    const QPixmap* pixmap = ui->lbl_img->pixmap();
//    QImage image(pixmap->toImage());
//    src = ASM::QImageToCvMat(image);
//    cvtColor(src, src_hsv, COLOR_BGR2HSV);
//    inRange(src_hsv, Scalar(ui->sld_lowred->value(), ui->sld_lowbl->value(), ui->sld_lowgr->value()), Scalar(ui->sld_upred->value(), ui->sld_upbl->value(), position), dst);
//    Mat img;
//    cvtColor(dst,img,COLOR_BGR2RGB);
//    ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
    cap.open(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_window_hsv()));
    timer->start(200);
}



void MainWindow::on_sld_lowred_sliderMoved()
{
//    Mat src, src_hsv, dst;
//    const QPixmap* pixmap = ui->lbl_img->pixmap();
//    QImage image(pixmap->toImage());
//    src = ASM::QImageToCvMat(image);
//    cvtColor(src, src_hsv, COLOR_BGR2HSV);
//    inRange(src_hsv, Scalar(position, ui->sld_lowbl->value(), ui->sld_lowgr->value()), Scalar(ui->sld_upred->value(), ui->sld_upbl->value(), ui->sld_upgr->value()), dst);
//    Mat img;
//    cvtColor(dst,img,COLOR_BGR2RGB);
//    ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
    cap.open(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_window_hsv()));
    timer->start(200);
}



void MainWindow::on_sld_lowbl_sliderMoved()
{
//    Mat src, src_hsv, dst;
//    const QPixmap* pixmap = ui->lbl_img->pixmap();
//    QImage image(pixmap->toImage());
//    src = ASM::QImageToCvMat(image);
//    cvtColor(src, src_hsv, COLOR_BGR2HSV);
//    inRange(src_hsv, Scalar(ui->sld_lowred->value(), position, ui->sld_lowgr->value()), Scalar(ui->sld_upred->value(), ui->sld_upbl->value(), ui->sld_upgr->value()), dst);
//    Mat img;
//    cvtColor(dst,img,COLOR_BGR2RGB);
//    ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));

    cap.open(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_window_hsv()));
    timer->start(200);
}



void MainWindow::on_sld_lowgr_sliderMoved()
{
//    Mat src, src_hsv, dst;
//    const QPixmap* pixmap = ui->lbl_img->pixmap();
//    QImage image(pixmap->toImage());
//    src = ASM::QImageToCvMat(image);
//    cvtColor(src, src_hsv, COLOR_BGR2HSV);
//    inRange(src_hsv, Scalar(ui->sld_lowred->value(), ui->sld_lowbl->value(), position), Scalar(ui->sld_upred->value(), ui->sld_upbl->value(), ui->sld_upgr->value()), dst);
//    Mat img;
//    cvtColor(dst,img,COLOR_BGR2RGB);
//    ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
    cap.open(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_window_hsv()));
    timer->start(200);

}

void MainWindow::update_window_hsv()
{
    cap >> frame;
    QImage qt_image;
    cvtColor(frame, frame, COLOR_BGR2HSV);
    inRange(frame, Scalar(ui->sld_lowred->value(), ui->sld_lowbl->value(), ui->sld_lowgr->value()), Scalar(ui->sld_upred->value(), ui->sld_upbl->value(), ui->sld_upgr->value()), frame);
    cvtColor(frame,frame,COLOR_BGR2RGB);
    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
    ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(qt_image));
    ui->lbl_img_Edit->resize(ui->lbl_img_Edit->pixmap()->size());
}


void MainWindow::on_sld_blur_sliderMoved(int position)
{
//    int MAX_KERNEL_LENGTH = 31;
//        Mat src, dst;
//        const QPixmap* pixmap = ui->lbl_img->pixmap();
//        QImage image( pixmap->toImage() );
//        src = ASM::QImageToCvMat(image);

        switch (position)
        {
        case 0: {
            // Homogenerous Blur:
//            for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 ) {
//                blur( src, dst, Size( i, i ), Point(-1,-1) );
//                     }
            // Chuyển đổi MAT => PixMap

//            Mat img;
//            cvtColor(dst,img,COLOR_BGR2RGB);
//            ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
//            break;
            cap.open(0);
            connect(timer, SIGNAL(timeout()), this, SLOT(update_window_blur0()));
            timer->start(200);
            break;
        }
        case 1: {
            // Gaussian Blur
//            for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
//                    {
//                GaussianBlur( src, dst, Size( i, i ), 0, 0 );
//        }
            // Chuyển đổi MAT => PixMap

//            Mat img;
//            cvtColor(dst,img,COLOR_BGR2RGB);
//            ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
//            break;
            cap.open(0);
            connect(timer, SIGNAL(timeout()), this, SLOT(update_window_blur1()));
            timer->start(200);
            break;
        }
        case 2: {
            // Median Blur
//            for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
//                     { medianBlur ( src, dst, i ); }
            // Chuyển đổi MAT => PixMap

//            Mat img;
//            cvtColor(dst,img,COLOR_BGR2RGB);
//            ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
//            break;
            cap.open(0);
            connect(timer, SIGNAL(timeout()), this, SLOT(update_window_blur2()));
            timer->start(200);
            break;
        }
        case 3: {
            // Bilateral Filter
//            for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
//                     { bilateralFilter ( src, dst, i, i*2, i/2 ); }
            // Chuyển đổi MAT => PixMap

//            Mat img;
//            cvtColor(dst,img,COLOR_BGR2RGB);
//            ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
//            break;
            cap.open(0);
            connect(timer, SIGNAL(timeout()), this, SLOT(update_window_blur3()));
            timer->start(200);
            break;
        }
        default: break;
        }
}

void MainWindow::update_window_blur0()
{
    int MAX_KERNEL_LENGTH = 31;
    cap >> frame;
    QImage qt_image;
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 ) {
                    blur( frame, frame, Size( i, i ), Point(-1,-1) );
                         }
    cvtColor(frame,frame,COLOR_BGR2RGB);
    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
    ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(qt_image));
    ui->lbl_img_Edit->resize(ui->lbl_img_Edit->pixmap()->size());

}

void MainWindow::update_window_blur1()
{
    int MAX_KERNEL_LENGTH = 31;
    cap >> frame;
    QImage qt_image;
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 ) {
                    GaussianBlur(frame, frame, Size( i, i ), 0, 0 );
                         }
    cvtColor(frame,frame,COLOR_BGR2RGB);
    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
    ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(qt_image));
    ui->lbl_img_Edit->resize(ui->lbl_img_Edit->pixmap()->size());

}

void MainWindow::update_window_blur2()
{
    int MAX_KERNEL_LENGTH = 31;
    cap >> frame;
    QImage qt_image;
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 ) {
                    medianBlur (frame, frame, i );
                         }
    cvtColor(frame,frame,COLOR_BGR2RGB);
    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
    ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(qt_image));
    ui->lbl_img_Edit->resize(ui->lbl_img_Edit->pixmap()->size());

}

void MainWindow::update_window_blur3()
{
    int MAX_KERNEL_LENGTH = 31;
    cap >> frame;
    QImage qt_image;
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 ) {
                    bilateralFilter (frame, frame, i, i*2, i/2 );
                         }
    cvtColor(frame,frame,COLOR_BGR2RGB);
    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
    ui->lbl_img_Edit->setPixmap(QPixmap::fromImage(qt_image));
    ui->lbl_img_Edit->resize(ui->lbl_img_Edit->pixmap()->size());

}

void MainWindow::on_btn_open_clicked()
{
    cap.open(0);

    if(!cap.isOpened())  // Check if we succeeded
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
    ui->lbl_img->setPixmap(QPixmap::fromImage(qt_image));
    ui->lbl_img->resize(ui->lbl_img->pixmap()->size());
    cout << "camera is closed" << endl;
}

void MainWindow::update_window()
{
    cap >> frame;
    QImage qt_image;
    cvtColor(frame, frame, COLOR_BGR2RGB);
    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
    ui->lbl_img->setPixmap(QPixmap::fromImage(qt_image));
    ui->lbl_img->resize(ui->lbl_img->pixmap()->size());
}






