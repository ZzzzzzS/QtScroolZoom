/*
 * @Author: Zhou Zishun
 * @Date: 2021-04-05 22:57:44
 * @LastEditors: Zhou Zishun
 * @LastEditTime: 2021-04-10 23:04:30
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

    this->ui->Label->LoadPicture(QPixmap("C:/Users/ZhouZishun/OneDrive/Images/Saved Pictures/IMG_0025.JPG"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
