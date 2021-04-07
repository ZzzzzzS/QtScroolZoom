/*
 * @Author: Zhou Zishun
 * @Date: 2021-04-07 20:40:48
 * @LastEditors: Zhou Zishun
 * @LastEditTime: 2021-04-08 00:05:58
 * @Description: file content
 */

#pragma once
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QResizeEvent>
#include <opencv2/opencv.hpp>
#include <QPoint>

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

    cv::Mat OriginalPicture_CV;
    cv::Mat ScrolledPicture_CV;

    struct SelectedSize_t
    {
        cv::Size_<int> StartPoint;
        cv::Size_<int> Length;
        double Ratio;
    };

    SelectedSize_t SelectedSize;

    QPoint ClickedPoint;

private:
    static cv::Mat ConvertQPixmapToMat(QPixmap &InputImage);
    static QPixmap ConvertMatToQPixmap(cv::Mat &InputImage);

    void SelectImage();

protected:
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
};
