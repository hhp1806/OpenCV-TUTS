#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "QFileDialog"

#include <string>
#include <cstring>
#include <QWidget>
#include <QColor>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

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
    void on_sld_value_sliderMoved(int position);
    void on_sld_type_sliderMoved(int position);

//    void onColorChanged();

//    void on_btn_hsv_clicked();

    void on_sld_upred_sliderMoved(int position);

    void on_sld_upbl_sliderMoved(int position);

    void on_sld_upgr_sliderMoved(int position);

    void on_sld_lowred_sliderMoved(int position);

    void on_sld_lowbl_sliderMoved(int position);

    void on_sld_lowgr_sliderMoved(int position);

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
