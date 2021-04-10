/*
 * @Author: Zhou Zishun
 * @Date: 2021-04-05 22:57:44
 * @LastEditors: Zhou Zishun
 * @LastEditTime: 2021-04-07 21:00:52
 * @Description: file content
 */
#pragma once

#include <QGridLayout>
#include <QMainWindow>
#include "ScrollScale.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
