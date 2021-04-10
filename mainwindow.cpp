/*
 * @Author: Zhou Zishun
 * @Date: 2021-04-05 22:57:44
 * @LastEditors: Zhou Zishun
 * @LastEditTime: 2021-04-10 21:11:29
 * @Description: file content
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ScrollScale.hpp"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->LabelLayout = new QGridLayout(this->ui->centralwidget);
    this->Label = new ScrollScale(this->ui->centralwidget);
    this->LabelLayout->addWidget(this->Label);
    this->Label->LoadPicture(QPixmap("C:/Users/ZhouZishun/OneDrive/Images/Saved Pictures/IMG_0025.JPG"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
