/*
 * @Author: Zhou Zishun
 * @Date: 2021-04-07 20:40:48
 * @LastEditors: Zhou Zishun
 * @LastEditTime: 2021-04-10 21:58:48
 * @Description: file content
 */

#pragma once
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QResizeEvent>
#include <QPoint>
#include <QRect>

#define SCROLL_SCALE 0.25
#define MIN_SELECTED_AREA 30
#define MOVE_SCALE 1

class ScrollScale : public QLabel
{
    Q_OBJECT
public:
    ScrollScale(QWidget *parents = Q_NULLPTR);
    ~ScrollScale();

    void LoadPicture(QPixmap &Picture);
    void LoadPicture(QImage &Picture);

private:
    /* data */
    QPixmap OriginalPicture;
    QPixmap ScrolledPicture;

    class MyRect
    {
    public:
        void setX(int a)
        {
            X = a;
        }
        void setY(int a)
        {
            Y = a;
        }
        void setWidth(int a)
        {
            Width = a;
        }
        void setHeight(int a)
        {
            Height = a;
        }
        int x()
        {
            return X;
        }
        int y()
        {
            return Y;
        }
        int width()
        {
            return Width;
        }
        int height()
        {
            return Height;
        }

    private:
        int X, Y, Width, Height;
    };

    MyRect SelectedSize;
    double Ratio;

    QPoint ClickedPoint;

private:
    void SelectImage();
    void SelectPicture();

protected:
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
};
