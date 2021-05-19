/*
 * @Author: Zhou Zishun
 * @Date: 2021-05-19 17:39:13
 * @LastEditors: Zhou Zishun
 * @LastEditTime: 2021-05-19 17:50:07
 * @Description: file content
 */
#include "ScrollZoomWidget.h"
#include <opencv2/opencv.hpp>
#include <qtimer.h>
#include <qthreadpool.h>
#include <qdebug.h>

ScrollZoomWidget::ScrollZoomWidget(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->UpdateTimer = new QTimer(this);
	connect(this->UpdateTimer, &QTimer::timeout, this, &ScrollZoomWidget::UpdateSlot);

	this->ui.label->SetDefaultText(tr("无图片"));

	connect(this->ui.label, &ScrollScale::MousePositionChanged, [this](QPoint P) {
		ui.lineEdit->setText("X=" + QString::number(P.x()) + " Y=" + QString::number(P.y()));
	});

	connect(this->ui.label, &ScrollScale::DrawSinglePointSignal, [this](QPoint P) {
		qDebug() << "DrawPoint" << P;
	});

	connect(this->ui.label, &ScrollScale::DrawPointsSignal, [this](std::vector<QPoint> P) {
		for (auto i : P)
		{
			qDebug() << i;
		}
	});
}

void ScrollZoomWidget::loadimage()
{
	cv::Mat a = cv::imread("C:/Users/ZhouZishun/OneDrive/Images/Saved Pictures/IMG_0025.JPG");

	this->ui.label->LoadPictureAsyn(a);

	qApp->processEvents();

	QThreadPool *Thread = new QThreadPool(this);
	this->ui.label->UpdateSyncThreadPool(Thread);

	qApp->processEvents();

	Capture = new cv::VideoCapture();
	//if (!Capture->open("C:/Users/ZhouZishun/Desktop/1.png"))
	if (!Capture->open("C:/Users/ZhouZishun/Videos/288840339/1/1.mp4"))
		return;
	//else
	//UpdateTimer->start(30);

	this->SyncCount = 0;
}

void ScrollZoomWidget::UpdateSlot()
{

	cv::Mat a;
	bool ok = Capture->read(a);
	this->ui.label->LoadPictureAsyn(a);
	if (!ok)
	{
		UpdateTimer->stop();
		delete Capture;
		a.release();
		this->ui.label->LoadPictureAsyn(a);
	}
}
