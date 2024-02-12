#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QColorDialog>
#include <opencv2/opencv.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadImageButton_clicked();

    void on_processButton_clicked();

    void on_saveButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_colorButton_clicked();

    void on_horizontalSlider_2_valueChanged(int value);

    void on_verticalSlider_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    cv::Mat image;
    cv::Mat imageCopy;
    int fontSize;
    int fontWeight;
    int X_point;
    int Y_point;
    QColor color;

};

#endif // MAINWINDOW_H
