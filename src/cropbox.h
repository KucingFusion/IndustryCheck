#ifndef CROPBOX_H
#define CROPBOX_H

#include <QWidget>
#include <QPainterPath>
#include <QPainter>
#include <QMouseEvent>
#include <opencv2/opencv.hpp>



namespace Ui {
class cropbox;
}

class IndustryCheck;
class ImgProcessThread;
class cropRoi;

class cropbox : public QWidget
{
    friend class IndustryCheck;
    friend class ImgProcessThread;
    friend class cropRoi;
    Q_OBJECT

public:
    explicit cropbox(IndustryCheck&m_industrycheck_, QWidget *parent = nullptr);
    ~cropbox();

    void label_imageshow();

private slots:
    void slot_confirm_btn();
    void slot_cancel_btn();

public:
    QImage              cropped;
    int                 zoomRatio;

private:
    Ui::cropbox         *ui;
    IndustryCheck&      m_industrycheck;
    cropRoi*            m_cropRoi;
};

#endif // CROPBOX_H
