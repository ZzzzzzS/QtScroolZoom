/*
 * @Author: Zhou Zishun
 * @Date: 2021-04-07 20:41:08
 * @LastEditors: Zhou Zishun
 * @LastEditTime: 2021-04-08 00:09:29
 * @Description: file content
 */

#include "ScrollScale.hpp"
#include <QLabel>
#include <QDebug>

ScrollScale::ScrollScale(QWidget *parents)
    : QLabel(parents)
{
    this->setAlignment(Qt::AlignCenter);
}

ScrollScale::~ScrollScale()
{
}

void ScrollScale::LoadPicture(QPixmap &Picture)
{
    this->OriginalPicture = Picture;
    this->ScrolledPicture = this->OriginalPicture;
    this->setPixmap(Picture.scaled(this->size(), Qt::KeepAspectRatio));
    this->SelectedSize.StartPoint.width = 0;
    this->SelectedSize.StartPoint.height = 0;
    //HACK
    this->SelectedSize.Length.width = this->ScrolledPicture.width() / 2;
    this->SelectedSize.Length.height = this->ScrolledPicture.height() / 2;
    this->SelectedSize.Ratio = (double)(this->ScrolledPicture.height()) / (double)(this->ScrolledPicture.width());

    qDebug() << "size" << this->ScrolledPicture.size();
}

void ScrollScale::LoadPicture(QImage &Picture)
{
    this->LoadPicture(QPixmap::fromImage(Picture));
}

void ScrollScale::resizeEvent(QResizeEvent *event)
{
    if (this->ScrolledPicture.isNull())
        this->setText(tr("No Picture"));
    else
        this->setPixmap(this->ScrolledPicture.scaled(event->size(), Qt::KeepAspectRatio));
}

void ScrollScale::mousePressEvent(QMouseEvent *event)
{
    this->ClickedPoint = event->pos();
}

void ScrollScale::mouseMoveEvent(QMouseEvent *event)
{
    int width = event->x() - this->ClickedPoint.x();
    int height = event->y() - this->ClickedPoint.y();

    if ((width + this->SelectedSize.Length.width) > OriginalPicture.width())
        width = OriginalPicture.width() - this->SelectedSize.Length.width;

    if ((height + this->SelectedSize.Length.height) > OriginalPicture.height())
        height = OriginalPicture.height() - this->SelectedSize.Length.height;

    if (width < 0)
        width = 0;
    if (height < 0)
        height = 0;

    this->SelectedSize.StartPoint.width = width;
    this->SelectedSize.StartPoint.height = height;

    qDebug() << "x=" << width << "y=" << height;
}

void ScrollScale::wheelEvent(QWheelEvent *event)
{
    this->SelectedSize.Length.width += ((double)(event->angleDelta().y()) * SCROLL_SCALE);
    this->SelectedSize.Length.height += ((double)(event->angleDelta().y()) * SCROLL_SCALE * SelectedSize.Ratio);

    if (this->SelectedSize.Length.width > this->OriginalPicture.width())
        this->SelectedSize.Length.width = this->OriginalPicture.width();
    else if (this->SelectedSize.Length.width < MIN_SELECTED_AREA)
        this->SelectedSize.Length.width = MIN_SELECTED_AREA;

    if (this->SelectedSize.Length.height > this->OriginalPicture.height())
        this->SelectedSize.Length.height = this->OriginalPicture.height();
    else if (this->SelectedSize.Length.height < (MIN_SELECTED_AREA * (double)(this->SelectedSize.Ratio)))
        this->SelectedSize.Length.height = MIN_SELECTED_AREA * (double)(this->SelectedSize.Ratio);

    int width = this->SelectedSize.StartPoint.width;
    int height = this->SelectedSize.StartPoint.height;

    if ((width + this->SelectedSize.Length.width) > OriginalPicture.width())
        width = OriginalPicture.width() - this->SelectedSize.Length.width;

    if ((height + this->SelectedSize.Length.height) > OriginalPicture.height())
        height = OriginalPicture.height() - this->SelectedSize.Length.height;

    if (width < 0)
        width = 0;
    if (height < 0)
        height = 0;

    this->SelectedSize.StartPoint.width = width;
    this->SelectedSize.StartPoint.height = height;

    qDebug() << "x=" << width << "y=" << height;
    qDebug() << "rx=" << SelectedSize.Length.width << "ry=" << SelectedSize.Length.height;
}

cv::Mat ScrollScale::ConvertQPixmapToMat(QPixmap &InputImage)
{
    cv::Mat OutImage = cv::Mat::zeros(cv::Size(InputImage.width(), InputImage.height()), CV_8UC3);

    return OutImage;
}

QPixmap ScrollScale::ConvertMatToQPixmap(cv::Mat &InputImage)
{
    QPixmap OutImage(InputImage.cols, InputImage.rows);

    return OutImage;
}
