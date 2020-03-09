#include "motiondetect.h"
#include "ui_motiondetect.h"



MotionDetect::MotionDetect(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MotionDetect)
{
    ui->setupUi(this);
}

MotionDetect::~MotionDetect()
{
    delete ui;
}


void MotionDetect::on_btn_vid_clicked()
{
        QFileDialog dialog(this);
        dialog.setNameFilter(tr("Videos (*.avi)"));
        dialog.setViewMode(QFileDialog::Detail);
        QString videofileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C:/", tr("Videos (*.avi)"));

        if(!videofileName.isEmpty())
        {
            String videopath;
            videopath = videofileName.toLocal8Bit().constData();

            bool playVideo = true;
            VideoCapture cap(videopath);
            if(!cap.isOpened())
            {
                QMessageBox::warning(this, tr("Warning"),tr("Error loadeing video."));
                exit(0);
            }
            int frame_counter = 0;
            Mat frame, fgmask, mask;
            Rect bounding_rect;
            while(1)
            {

                frame_counter +=1;
                if(frame_counter == cap.get(CAP_PROP_FRAME_COUNT))
                {
                    frame_counter = 0;
                    cap.set(CAP_PROP_POS_FRAMES, 0);
                }
                if(playVideo)
                cap >> frame;
                QImage qt_image;

                if(frame.empty())
                {
                    QMessageBox::warning(this, tr("Warning"),tr("Video frame cannot be openned."));
                    break;
                }

                Ptr<BackgroundSubtractorMOG2> fgbg = createBackgroundSubtractorMOG2();
                fgbg->apply(frame, fgmask);
                mask = 255 - fgmask;
                vector<vector<Point>> contours;
                vector<Vec4i> hier;
                findContours(mask, contours, hier, 3, 1);
                cvtColor(fgmask, fgmask, COLOR_GRAY2BGR);
                for (size_t i = 0; i < contours.size(); i++) {
            //            cv::drawContours(contourImage, contours, idx, Scalar(0, 255, 0), 1, 8, hier);
                    double area = contourArea( contours[i] );
                    if (area > 200 && area < 20000)
                    {
                        int x, y, w, h;
                        bounding_rect = boundingRect( contours[i] );
//                        drawContours(frame, contours,i, Scalar( 0, 255, 0 ), 2 );
                        Rect rect(x, y, w, h);
                        rect = bounding_rect;
                        rectangle(frame, rect, Scalar(0,255,0));
                    }
//                    cvtColor(frame, frame, COLOR_BGR2RGB);
//                    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
//                    ui->lbl_vid->setPixmap(QPixmap::fromImage(qt_image));
//                    ui->lbl_vid->resize(ui->lbl_vid->pixmap()->size());
                    imshow("Frame", frame);
                    imshow("Mask", fgmask);
                    QApplication::processEvents();

            }
       }
}
}



void MotionDetect::on_btn_detect_clicked()
{

}
