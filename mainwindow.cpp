#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "iostream"
#include "Blob.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    capVideo.open("C:\\Users\\hhp18\\OneDrive\\Documents\\QT demo\\object_couting\\objectCouting\\demo.mp4");


    capVideo.set(CAP_PROP_FRAME_WIDTH, WIDTH);
    capVideo.set(CAP_PROP_FRAME_HEIGHT, HEIGHT);

}

MainWindow::~MainWindow()
{
    delete ui;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//void addBlobToExistingBlobs(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex) {

//    existingBlobs[intIndex].currentContour = currentFrameBlob.currentContour;
//    existingBlobs[intIndex].currentBoundingRect = currentFrameBlob.currentBoundingRect;

//    existingBlobs[intIndex].centerPositions.push_back(currentFrameBlob.centerPositions.back());

//    existingBlobs[intIndex].dblCurrentDiagonalSize = currentFrameBlob.dblCurrentDiagonalSize;
//    existingBlobs[intIndex].dblCurrentAspectRatio = currentFrameBlob.dblCurrentAspectRatio;

//    existingBlobs[intIndex].blnStillBeingTracked = true;
//    existingBlobs[intIndex].blnCurrentMatchFoundOrNewBlob = true;
//}

///////////////////////////////////////////////////////////////////////////////////////////////////
//void addNewBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs) {

//    currentFrameBlob.blnCurrentMatchFoundOrNewBlob = true;

//    existingBlobs.push_back(currentFrameBlob);
//}

///////////////////////////////////////////////////////////////////////////////////////////////////
//double distanceBetweenPoints(cv::Point point1, cv::Point point2) {

//    int intX = abs(point1.x - point2.x);
//    int intY = abs(point1.y - point2.y);

//    return(sqrt(pow(intX, 2) + pow(intY, 2)));
//}

//void matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob> &existingBlobs, std::vector<Blob> &currentFrameBlobs) {

//    for (auto &existingBlob : existingBlobs) {

//        existingBlob.blnCurrentMatchFoundOrNewBlob = false;

//        existingBlob.predictNextPosition();
//    }

//    for (auto &currentFrameBlob : currentFrameBlobs) {

//        int intIndexOfLeastDistance = 0;
//        double dblLeastDistance = 100000.0;

//        for (unsigned int i = 0; i < existingBlobs.size(); i++) {

//            if (existingBlobs[i].blnStillBeingTracked == true) {

//                double dblDistance = distanceBetweenPoints(currentFrameBlob.centerPositions.back(), existingBlobs[i].predictedNextPosition);

//                if (dblDistance < dblLeastDistance) {
//                    dblLeastDistance = dblDistance;
//                    intIndexOfLeastDistance = i;
//                }
//            }
//        }

//        if (dblLeastDistance < currentFrameBlob.dblCurrentDiagonalSize * 0.5) {
//            addBlobToExistingBlobs(currentFrameBlob, existingBlobs, intIndexOfLeastDistance);
//        }
//        else {
//            addNewBlob(currentFrameBlob, existingBlobs);
//        }

//    }

//    for (auto &existingBlob : existingBlobs) {

//        if (existingBlob.blnCurrentMatchFoundOrNewBlob == false) {
//            existingBlob.intNumOfConsecutiveFramesWithoutAMatch++;
//        }

//        if (existingBlob.intNumOfConsecutiveFramesWithoutAMatch >= 5) {
//            existingBlob.blnStillBeingTracked = false;
//        }

//    }

//}



///////////////////////////////////////////////////////////////////////////////////////////////////
//void drawAndShowContours(Size imageSize, vector<std::vector<Point> > contours, string strImageName) {

//    Mat image(imageSize, CV_8UC3, Scalar(0.0, 0.0, 0.0));

//    drawContours(image, contours, -1, Scalar(255.0, 255.0, 255.0), -1);

//    imshow(strImageName, image);
//}

///////////////////////////////////////////////////////////////////////////////////////////////////
//void drawAndShowContours(cv::Size imageSize, std::vector<Blob> blobs, std::string strImageName) {

//    cv::Mat image(imageSize, CV_8UC3, Scalar(0.0, 0.0, 0.0));

//    std::vector<std::vector<cv::Point> > contours;

//    for (auto &blob : blobs) {
//        if (blob.blnStillBeingTracked == true) {
//            contours.push_back(blob.currentContour);
//        }
//    }

//    cv::drawContours(image, contours, -1, Scalar(255.0, 255.0, 255.0), -1);

//    cv::imshow(strImageName, image);
//}

///////////////////////////////////////////////////////////////////////////////////////////////////
//bool checkIfBlobsCrossedTheLine(std::vector<Blob> &blobs, int &intHorizontalLinePosition, int &carCount) {
//    bool blnAtLeastOneBlobCrossedTheLine = false;

//    for (auto blob : blobs) {

//        if (blob.blnStillBeingTracked == true && blob.centerPositions.size() >= 2) {
//            int prevFrameIndex = (int)blob.centerPositions.size() - 2;
//            int currFrameIndex = (int)blob.centerPositions.size() - 1;

//            if (blob.centerPositions[prevFrameIndex].y > intHorizontalLinePosition && blob.centerPositions[currFrameIndex].y <= intHorizontalLinePosition) {
//                carCount++;
//                blnAtLeastOneBlobCrossedTheLine = true;
//            }
//        }

//    }

//    return blnAtLeastOneBlobCrossedTheLine;
//}

///////////////////////////////////////////////////////////////////////////////////////////////////
//void drawBlobInfoOnImage(std::vector<Blob> &blobs, cv::Mat &imgFrame2Copy) {

//    for (unsigned int i = 0; i < blobs.size(); i++) {

//        if (blobs[i].blnStillBeingTracked == true) {
//            cv::rectangle(imgFrame2Copy, blobs[i].currentBoundingRect, Scalar(0.0, 0.0, 255.0), 2);

//            int intFontFace = FONT_HERSHEY_SIMPLEX;
//            double dblFontScale = blobs[i].dblCurrentDiagonalSize / 60.0;
//            int intFontThickness = (int)std::round(dblFontScale * 1.0);

//            cv::putText(imgFrame2Copy, std::to_string(i), blobs[i].centerPositions.back(), intFontFace, dblFontScale, Scalar(0.0, 200.0, 0.0), intFontThickness);
//        }
//    }
//}

///////////////////////////////////////////////////////////////////////////////////////////////////
//void drawCarCountOnImage(int &carCount, cv::Mat &imgFrame2Copy) {

//    int intFontFace = FONT_HERSHEY_SIMPLEX;
//    double dblFontScale = (imgFrame2Copy.rows * imgFrame2Copy.cols) / 300000.0;
//    int intFontThickness = (int)std::round(dblFontScale * 1.5);

//    cv::Size textSize = cv::getTextSize(std::to_string(carCount), intFontFace, dblFontScale, intFontThickness, 0);

//    cv::Point ptTextBottomLeftPosition;

//    ptTextBottomLeftPosition.x = imgFrame2Copy.cols - 1 - (int)((double)textSize.width * 1.25);
//    ptTextBottomLeftPosition.y = (int)((double)textSize.height * 1.25);

//    cv::putText(imgFrame2Copy, std::to_string(carCount), ptTextBottomLeftPosition, intFontFace, dblFontScale, Scalar(0.0, 200.0, 0.0), intFontThickness);

//}
void MainWindow::Start(){

    while (true){

        if(breakLoop==true){
            return;
        }

        if (!capVideo.isOpened()) {
                cout << "error reading video file" << std::endl << std::endl;

            }

            if (capVideo.get(CAP_PROP_FRAME_COUNT) < 2) {
                cout << "error: video file must have at least two frames";
            }

            capVideo.read(imgFrame1);
            capVideo.read(imgFrame2);

            int intHorizontalLinePosition = (int)round((double)imgFrame1.rows * 0.35);

            crossingLine[0].x = 0;
            crossingLine[0].y = intHorizontalLinePosition;

            crossingLine[1].x = imgFrame1.cols - 1;
            crossingLine[1].y = intHorizontalLinePosition;

            while (capVideo.isOpened() && chCheckForEscKey != 27) {

                vector<Blob> currentFrameBlobs;

                imgFrame1Copy = imgFrame1.clone();
                imgFrame2Copy = imgFrame2.clone();


                cvtColor(imgFrame1Copy, imgFrame1Copy, COLOR_BGR2GRAY);
                cvtColor(imgFrame2Copy, imgFrame2Copy, COLOR_BGR2GRAY);

                GaussianBlur(imgFrame1Copy, imgFrame1Copy, cv::Size(5, 5), 0);
                GaussianBlur(imgFrame2Copy, imgFrame2Copy, cv::Size(5, 5), 0);

                absdiff(imgFrame1Copy, imgFrame2Copy, imgDifference);

                threshold(imgDifference, imgThresh, 30, 255.0, THRESH_BINARY);

                imshow("imgThresh", imgThresh);

                Mat structuringElement3x3 = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
                Mat structuringElement5x5 = getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
                Mat structuringElement7x7 = getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
                Mat structuringElement15x15 = getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));

                for (unsigned int i = 0; i < 2; i++) {
                    dilate(imgThresh, imgThresh, structuringElement5x5);
                    dilate(imgThresh, imgThresh, structuringElement5x5);
                    erode(imgThresh, imgThresh, structuringElement5x5);
                }

                Mat imgThreshCopy = imgThresh.clone();

                vector<vector<Point>> contours;

                findContours(imgThreshCopy, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

                drawAndShowContours(imgThresh.size(), contours, "imgContours");

                vector<vector<Point>> convexHulls(contours.size());

                for (unsigned int i = 0; i < contours.size(); i++) {
                    convexHull(contours[i], convexHulls[i]);
                }

                drawAndShowContours(imgThresh.size(), convexHulls, "imgConvexHulls");

                for (auto &convexHull : convexHulls) {
                    Blob possibleBlob(convexHull);

                    if (possibleBlob.currentBoundingRect.area() > 400 &&
                        possibleBlob.dblCurrentAspectRatio > 0.2 &&
                        possibleBlob.dblCurrentAspectRatio < 4.0 &&
                        possibleBlob.currentBoundingRect.width > 30 &&
                        possibleBlob.currentBoundingRect.height > 30 &&
                        possibleBlob.dblCurrentDiagonalSize > 60.0 &&
                        (contourArea(possibleBlob.currentContour) / (double)possibleBlob.currentBoundingRect.area()) > 0.50) {
                        currentFrameBlobs.push_back(possibleBlob);
                    }
                }

                drawAndShowContours(imgThresh.size(), currentFrameBlobs, "imgCurrentFrameBlobs");

                if (blnFirstFrame == true) {
                    for (auto &currentFrameBlob : currentFrameBlobs) {
                        blobs.push_back(currentFrameBlob);
                    }
                } else {
                    matchCurrentFrameBlobsToExistingBlobs(blobs, currentFrameBlobs);
                }

                drawAndShowContours(imgThresh.size(), blobs, "imgBlobs");

                imgFrame2Copy = imgFrame2.clone();

                drawBlobInfoOnImage(blobs, imgFrame2Copy);

                bool blnAtLeastOneBlobCrossedTheLine = checkIfBlobsCrossedTheLine(blobs, intHorizontalLinePosition, carCount);

                if (blnAtLeastOneBlobCrossedTheLine == true) {
                    line(imgFrame2Copy, crossingLine[0], crossingLine[1], SCALAR_GREEN, 2);
                } else {
                    line(imgFrame2Copy, crossingLine[0], crossingLine[1], SCALAR_RED, 2);
                }

                drawCarCountOnImage(carCount, imgFrame2Copy);

                imshow("imgFrame2Copy", imgFrame2Copy);



                currentFrameBlobs.clear();

                imgFrame1 = imgFrame2.clone();

                if ((capVideo.get(CAP_PROP_POS_FRAMES) + 1) < capVideo.get(CAP_PROP_FRAME_COUNT)) {
                    capVideo.read(imgFrame2);
                } else {
                    std::cout << "end of video\n";
                    break;
                }

                blnFirstFrame = false;
                frameCount++;
                chCheckForEscKey = cv::waitKey(1);
            }

            if (chCheckForEscKey != 27) {
                cv::waitKey(0);
            }
       }
}

