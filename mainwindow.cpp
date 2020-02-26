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
    ui->btn_gray->setVisible(false);

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
//                const char* string = filename.toStdString().c_str();
//                Mat image = cv::imread(string);
//                namedWindow("My Image", WINDOW_FULLSCREEN);
//                imshow("My Image", image);
                ui->lbl_img->setText("Open successfully");
                img = img.scaledToWidth(ui->lbl_img->width(), Qt::SmoothTransformation);
                ui->lbl_img->setPixmap(QPixmap::fromImage(img));
            }
            else
            {
                ui->lbl_img->setText("No image data");
            }

        }
        ui->btn_gray->setVisible(true);



}

void MainWindow::on_btn_defimg_clicked()
{

//    Mat image = imread("D:\\Pics\\Screens\\MVs\\charles.png");
//    namedWindow("My Image", WINDOW_FULLSCREEN);
//    imshow("My Image", image);

    ui->lbl_img->setText("Open successfully");

    QImage img;
    img.load("D:\\Pics\\Screens\\MVs\\charles.png");
    img = img.scaledToWidth(ui->lbl_img->width(), Qt::SmoothTransformation);
    ui->lbl_img->setPixmap(QPixmap::fromImage(img));
    ui->btn_gray->setVisible(true);

}

void MainWindow::on_btn_gray_clicked()
{
    const QPixmap* pixmap = ui->lbl_img->pixmap();
    QImage image(pixmap->toImage());
    Mat img = ASM::QImageToCvMat(image);
    Mat img_gray;
    cvtColor(img, img_gray, COLOR_BGR2GRAY);
    imshow("Image", img_gray);
}



void MainWindow::on_sld_value_sliderMoved(int value)
{
    Mat src, src_gray, dst;
    const QPixmap* pixmap = ui->lbl_img->pixmap();
    QImage image(pixmap->toImage());
    src = ASM::QImageToCvMat(image);
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    threshold(src_gray, dst, value, 255, ui->sld_type->value());
    imshow("Image", dst);
}


void MainWindow::on_sld_type_sliderMoved(int type)
{
    Mat src, src_gray, dst;
    const QPixmap* pixmap = ui->lbl_img->pixmap();
    QImage image(pixmap->toImage());
    src = ASM::QImageToCvMat(image);
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    threshold(src_gray, dst, ui->sld_value->value(), 255, type);
    imshow("Image", dst);
}



void MainWindow::on_sld_upred_sliderMoved(int position)
{
    Mat src, src_hsv, dst;
    const QPixmap* pixmap = ui->lbl_img->pixmap();
    QImage image(pixmap->toImage());
    src = ASM::QImageToCvMat(image);
    cvtColor(src, src_hsv, COLOR_BGR2HSV);
    inRange(src_hsv, Scalar(ui->sld_lowred->value(), ui->sld_lowbl->value(), ui->sld_lowgr->value()), Scalar(position, ui->sld_upbl->value(), ui->sld_upgr->value()), dst);
    imshow("Image", dst);
}



void MainWindow::on_sld_upbl_sliderMoved(int position)
{
    Mat src, src_hsv, dst;
    const QPixmap* pixmap = ui->lbl_img->pixmap();
    QImage image(pixmap->toImage());
    src = ASM::QImageToCvMat(image);
    cvtColor(src, src_hsv, COLOR_BGR2HSV);
    inRange(src_hsv, Scalar(ui->sld_lowred->value(), ui->sld_lowbl->value(), ui->sld_lowgr->value()), Scalar(ui->sld_upred->value(), position, ui->sld_upgr->value()), dst);
    imshow("Image", dst);
}



void MainWindow::on_sld_upgr_sliderMoved(int position)
{
    Mat src, src_hsv, dst;
    const QPixmap* pixmap = ui->lbl_img->pixmap();
    QImage image(pixmap->toImage());
    src = ASM::QImageToCvMat(image);
    cvtColor(src, src_hsv, COLOR_BGR2HSV);
    inRange(src_hsv, Scalar(ui->sld_lowred->value(), ui->sld_lowbl->value(), ui->sld_lowgr->value()), Scalar(ui->sld_upred->value(), ui->sld_upbl->value(), position), dst);
    imshow("Image", dst);
}



void MainWindow::on_sld_lowred_sliderMoved(int position)
{
    Mat src, src_hsv, dst;
    const QPixmap* pixmap = ui->lbl_img->pixmap();
    QImage image(pixmap->toImage());
    src = ASM::QImageToCvMat(image);
    cvtColor(src, src_hsv, COLOR_BGR2HSV);
    inRange(src_hsv, Scalar(position, ui->sld_lowbl->value(), ui->sld_lowgr->value()), Scalar(ui->sld_upred->value(), ui->sld_upbl->value(), ui->sld_upgr->value()), dst);
    imshow("Image", dst);
}



void MainWindow::on_sld_lowbl_sliderMoved(int position)
{
    Mat src, src_hsv, dst;
    const QPixmap* pixmap = ui->lbl_img->pixmap();
    QImage image(pixmap->toImage());
    src = ASM::QImageToCvMat(image);
    cvtColor(src, src_hsv, COLOR_BGR2HSV);
    inRange(src_hsv, Scalar(ui->sld_lowred->value(), position, ui->sld_lowgr->value()), Scalar(ui->sld_upred->value(), ui->sld_upbl->value(), ui->sld_upgr->value()), dst);
    imshow("Image", dst);
}



void MainWindow::on_sld_lowgr_sliderMoved(int position)
{
    Mat src, src_hsv, dst;
    const QPixmap* pixmap = ui->lbl_img->pixmap();
    QImage image(pixmap->toImage());
    src = ASM::QImageToCvMat(image);
    cvtColor(src, src_hsv, COLOR_BGR2HSV);
    inRange(src_hsv, Scalar(ui->sld_lowred->value(), ui->sld_lowbl->value(), position), Scalar(ui->sld_upred->value(), ui->sld_upbl->value(), ui->sld_upgr->value()), dst);
    imshow("Image", dst);
}
