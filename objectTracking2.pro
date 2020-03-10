#-------------------------------------------------
#
# Project created by QtCreator 2016-05-30T18:42:28
# Author: Nauroze Hoath
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = objectTracking2
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp
INCLUDEPATH += C:\opencv\build\include

LIBS += -LC:\opencv\opencv-build\bin\
libopencv_calib3d420 \
libopencv_core420 \
libopencv_features2d420 \
libopencv_flann420 \
libopencv_highgui420 \
libopencv_imgcodecs420 \
libopencv_imgproc420 \
libopencv_ml420 \
libopencv_objdetect420 \
libopencv_photo420 \
libopencv_stitching420 \
libopencv_video420 \
libopencv_videoio420 \

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
