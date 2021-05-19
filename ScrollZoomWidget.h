/*
 * @Author: Zhou Zishun
 * @Date: 2021-05-19 17:39:13
 * @LastEditors: Zhou Zishun
 * @LastEditTime: 2021-05-19 17:50:19
 * @Description: file content
 */
#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ScrollZoomWidget.h"
#include "ScrollScale.h"
#include <qthread.h>

class ScrollZoomWidget : public QMainWindow
{
	Q_OBJECT

public:
	ScrollZoomWidget(QWidget *parent = Q_NULLPTR);

	void loadimage();

signals:
	void StartCamera(QString name);

private:
	Ui::ScrollZoomWidgetClass ui;

	QTimer *UpdateTimer;
	cv::VideoCapture *Capture;

	int SyncCount;

private slots:
	void UpdateSlot();
};
