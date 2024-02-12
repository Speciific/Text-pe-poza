#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <string>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Text pe poza");

    ui->processButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadImageButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Selecteaza imagine", "", "Imagini (*.png *.jpg *.jpeg *.bmp *.gif)");
    if (!filePath.isEmpty())
    {
        QImage qImage(filePath);
        ui->imageLabel->setPixmap(QPixmap::fromImage(qImage));
        image = cv::imread(filePath.toStdString());
    }
    ui->processButton->setEnabled(true);
}

void MainWindow::on_processButton_clicked()
{
    if (!image.empty())
    {
        imageCopy = image.clone();

        QString text = ui->textLineEdit->toPlainText();

        cv::Scalar textColor(color.blue(), color.green(), color.red(), color.alpha());

        cv::putText(imageCopy, "", cv::Point(Y_point, X_point), cv::FONT_HERSHEY_SIMPLEX, fontSize, textColor, fontWeight);

        cv::putText(imageCopy, text.toStdString(), cv::Point(Y_point, X_point), cv::FONT_HERSHEY_SIMPLEX, fontSize, textColor, fontWeight);

        cv::cvtColor(imageCopy, imageCopy, cv::COLOR_BGR2RGB);

        QImage processedImage(imageCopy.data, imageCopy.cols, imageCopy.rows, imageCopy.step, QImage::Format_RGB888);
        ui->imageLabel->setPixmap(QPixmap::fromImage(processedImage));

    }
    ui->saveButton->setEnabled(true);
}

void MainWindow::on_saveButton_clicked()
{
    if (!imageCopy.empty())
    {
        QString savePath = QFileDialog::getSaveFileName(this, "Salveaza imaginea", "", "Imagine (*.png)");
        if (!savePath.isEmpty())
        {

        cv::Mat imageCopyRGB;
        cv::cvtColor(imageCopy, imageCopyRGB, cv::COLOR_BGR2RGB);

        cv::imwrite(savePath.toStdString(), imageCopyRGB);
        }
    }
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    QString cdt("");
    cdt.append(QString::number(value));

    this->ui->label->setText(cdt);

    fontSize = value;
}


void MainWindow::on_colorButton_clicked()
{
    color = QColorDialog::getColor(Qt::black, this);
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    QString cdt("");
    cdt.append(QString::number(value));

    this->ui->label_2->setText(cdt);

    fontWeight = value;
}


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    QString cdt("X=");
    cdt.append(QString::number(value));

    this->ui->label_3->setText(cdt);

    X_point = value;
}


void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    QString cdt("Y=");
    cdt.append(QString::number(value));

    this->ui->label_4->setText(cdt);

    Y_point = value;
}

