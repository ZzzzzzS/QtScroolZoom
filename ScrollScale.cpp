/*
 * @Author: Zhou Zishun
 * @Date: 2021-04-07 20:41:08
 * @LastEditors: Zhou Zishun
 * @LastEditTime: 2021-04-09 09:49:21
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

void ScrollScale::SelectImage()
{
}

void ScrollScale::SelectPicture()
{
    this->ScrolledPicture = this->OriginalPicture.copy(this->SelectedSize.x(), SelectedSize.y(), SelectedSize.width(), SelectedSize.height());
    this->setPixmap(this->ScrolledPicture.scaled(this->size(), Qt::KeepAspectRatio));
}

void ScrollScale::LoadPicture(QPixmap &Picture)
{
    this->OriginalImage = Picture.toImage();
    this->OriginalPicture = Picture;
    this->ScrolledPicture = this->OriginalPicture;
    this->ScrolledImage = this->ScrolledPicture.toImage();
    this->setPixmap(Picture.scaled(this->size(), Qt::KeepAspectRatio));
    this->SelectedSize.setX(0);
    this->SelectedSize.setY(0);
    this->SelectedSize.setWidth(this->ScrolledPicture.width());
    this->SelectedSize.setHeight(this->ScrolledPicture.height());
    this->Ratio = (double)(this->ScrolledPicture.height()) / (double)(this->ScrolledPicture.width());

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
    int width = this->ClickedPoint.x() - event->x();
    int height = this->ClickedPoint.y() - event->y();

    if ((width + this->SelectedSize.width()) > OriginalPicture.width())
        width = OriginalPicture.width() - this->SelectedSize.width();

    if ((height + this->SelectedSize.height()) > OriginalPicture.height())
        height = OriginalPicture.height() - this->SelectedSize.height();

    if (width < 0)
        width = 0;
    if (height < 0)
        height = 0;

    this->SelectedSize.setX(width);
    this->SelectedSize.setY(height);

    qDebug() << "x=" << SelectedSize.x() << "y=" << SelectedSize.y();
    qDebug() << "rx=" << SelectedSize.width() << "ry=" << SelectedSize.height();

    this->SelectPicture();
}

void ScrollScale::wheelEvent(QWheelEvent *event)
{
    this->SelectedSize.setWidth(this->SelectedSize.width() - ((double)(event->angleDelta().y()) * SCROLL_SCALE));
    this->SelectedSize.setHeight(this->SelectedSize.height() - ((double)(event->angleDelta().y()) * SCROLL_SCALE * Ratio));

    if (this->SelectedSize.width() > this->OriginalPicture.width())
        this->SelectedSize.setWidth(this->OriginalPicture.width());
    else if (this->SelectedSize.width() < MIN_SELECTED_AREA)
        this->SelectedSize.setWidth(MIN_SELECTED_AREA);

    if (this->SelectedSize.height() > this->OriginalPicture.height())
        this->SelectedSize.setHeight(this->OriginalPicture.height());
    else if (this->SelectedSize.height() < (MIN_SELECTED_AREA * (double)(this->Ratio)))
        this->SelectedSize.setHeight(MIN_SELECTED_AREA * (double)(this->Ratio));

    int width = this->SelectedSize.x();  // + (this->SelectedSize.width() - ((double)(event->angleDelta().y()) * SCROLL_SCALE)) / 2;
    int height = this->SelectedSize.y(); //+ (this->SelectedSize.height() - ((double)(event->angleDelta().y()) * SCROLL_SCALE * Ratio)) / 2;

    if ((width + this->SelectedSize.width()) > OriginalPicture.width())
        width = OriginalPicture.width() - this->SelectedSize.width();

    if ((height + this->SelectedSize.height()) > OriginalPicture.height())
        height = OriginalPicture.height() - this->SelectedSize.height();

    if (width < 0)
        width = 0;
    if (height < 0)
        height = 0;

    this->SelectedSize.setX(width);
    this->SelectedSize.setY(height);

    qDebug() << "x=" << width << "y=" << height;
    qDebug() << "rx=" << SelectedSize.width() << "ry=" << SelectedSize.height();
    this->SelectPicture();
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
