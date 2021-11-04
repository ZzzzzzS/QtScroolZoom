/*
 * @Author: Zhou Zishun
 * @Date: 2021-05-19 17:39:13
 * @LastEditors: Zhou Zishun
 * @LastEditTime: 2021-05-28 14:00:41
 * @Description: file content
 */
#include "ScrollZoomWidget.h"
#include <QtWidgets/QApplication>

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <qdebug.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ScrollZoomWidget w;
	w.setAttribute(Qt::WA_QuitOnClose, true);
	w.show();

	if (argc > 1)
	{
		w.loadimage(argv[1]);
	}

	return a.exec();
}
