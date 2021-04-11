/*
 * @Author: Zhou Zishun
 * @Date: 2021-04-07 20:41:08
 * @LastEditors: Zhou Zishun
 * @LastEditTime: 2021-04-11 12:50:32
 * @Description: file content
 */

#include "ScrollScale.hpp"
#include <QLabel>
#include <QDebug>

ScrollScale::ScrollScale(QWidget *parents)
    : QLabel(parents)
{
    this->setAlignment(Qt::AlignCenter);
    this->setCursor(QCursor(Qt::OpenHandCursor));
}

ScrollScale::~ScrollScale()
{
}

void ScrollScale::SelectPicture()
{
    this->ScrolledPicture = this->OriginalPicture.copy(this->SelectedSize.x(), SelectedSize.y(), SelectedSize.width(), SelectedSize.height());
    this->setPixmap(this->ScrolledPicture.scaled(this->size(), Qt::KeepAspectRatio));
    qDebug() << "x=" << SelectedSize.x() << "y=" << SelectedSize.y();
    qDebug() << "rx=" << SelectedSize.width() << "ry=" << SelectedSize.height();
}

void ScrollScale::LoadPicture(QPixmap &Picture)
{
    this->OriginalPicture = Picture;
    this->ScrolledPicture = this->OriginalPicture;
    this->setPixmap(Picture.scaled(this->size(), Qt::KeepAspectRatio));
    this->SelectedSize.setX(0);
    this->SelectedSize.setY(0);
    this->SelectedSize.setWidth(this->ScrolledPicture.width());
    this->SelectedSize.setHeight(this->ScrolledPicture.height());
    this->Ratio = (double)(this->ScrolledPicture.height()) / (double)(this->ScrolledPicture.width());
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
    this->setCursor(QCursor(Qt::ClosedHandCursor));

    if (this->ScrolledPicture.isNull())
        return;

    this->ClickedPoint.setX(this->SelectedSize.x() + event->pos().x() * (double)this->ScrolledPicture.width() / this->pixmap()->width());
    this->ClickedPoint.setY(this->SelectedSize.y() + event->pos().y() * (double)this->ScrolledPicture.height() / this->pixmap()->height());

    qDebug() << "clicked";
    this->SelectPicture();
}

void ScrollScale::mouseMoveEvent(QMouseEvent *event)
{

    if (this->ScrolledPicture.isNull())
        return;

    int width = this->ClickedPoint.x() - event->x() * (double)this->ScrolledPicture.width() / this->pixmap()->width();
    int height = this->ClickedPoint.y() - event->y() * (double)this->ScrolledPicture.height() / this->pixmap()->height();

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

    this->SelectPicture();
}

void ScrollScale::wheelEvent(QWheelEvent *event)
{
    this->setCursor(QCursor(Qt::OpenHandCursor));

    if (this->ScrolledPicture.isNull())
        return;

    int PreviousWidth = this->SelectedSize.width();
    int PreviousHeight = this->SelectedSize.height();

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

    int width = this->SelectedSize.x() + (PreviousWidth - this->SelectedSize.width()) / 2;
    int height = this->SelectedSize.y() + (PreviousHeight - this->SelectedSize.height()) / 2;

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

    this->SelectPicture();
}

void ScrollScale::mouseReleaseEvent(QMouseEvent *ev)
{
    this->setCursor(QCursor(Qt::OpenHandCursor));
}
