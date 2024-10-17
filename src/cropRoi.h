#ifndef CROPROI_H_
#define CROPROI_H_

#include <QWidget>
#include <QPainterPath>
#include <QPainter>
#include <QMouseEvent>
#include "cropbox.h"


class cropbox;

class cropRoi : public QWidget {
    friend class cropbox;
    Q_OBJECT
    enum Direction { UP=0, DOWN, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };

public:
    explicit cropRoi(QWidget *parent = nullptr);
    // 你可以在这里添加其他公有函数和变量

protected:
    void paintEvent(QPaintEvent *event) override; // 如果需要重写绘制事件

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void drawBorder(QPainter &painter);
    void drawPoints(QPainter &painter);
    void drawInternalLines(QPainter &painter);
    void drawSizeText(QPainter &painter);


    void handleMove(QPoint mouse_globalpos);
    void handleResize(QPoint mouse_parentpos);

    void handleResizeUp(QPoint &valid_point, QRect &rectNew, const QWidget *parent_widget);
    void handleResizeDown(QPoint &valid_point, QRect &rectNew, const QWidget *parent_widget);
    void handleResizeLeft(QPoint &valid_point, QRect &rectNew, const QWidget *parent_widget);
    void handleResizeRight(QPoint &valid_point, QRect &rectNew, const QWidget *parent_widget);
    void handleResizeRightTop(QPoint &valid_point, QRect &rectNew, const QWidget *parent_widget);
    void handleResizeRightBottom(QPoint &valid_point, QRect &rectNew, const QWidget *parent_widget);
    void handleResizeLeftTop(QPoint &valid_point, QRect &rectNew, const QWidget *parent_widget);
    void handleResizeLeftBottom(QPoint &valid_point, QRect &rectNew, const QWidget *parent_widget);
    void setDirection(QPoint point);

    inline int judgePosition(int origin, int min, int max);

private:

    int m_minWidth;
    int m_minHeight;
    
    int m_widthCount;
    int m_heightCount;

    bool m_bFixSized;
    bool m_bMovingFlag;
    Direction m_curDirec;

    QPoint m_dragPosition;
    QPoint corpPoint;
    int cropWidth, cropHeight;
    cropbox * m_cropbox;

    
};

#endif
