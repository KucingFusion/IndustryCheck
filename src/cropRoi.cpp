#include "cropRoi.h"


#define LINEWIDTH 1
#define SPACING   2
#define POINTSIZE 5
#define PADDING   4


cropRoi::cropRoi(QWidget *parent)
    : QWidget(parent)
    , m_minWidth(80)
    , m_minHeight(80)
    , m_widthCount(4)
    , m_heightCount(4)
    , m_curDirec(NONE)
    , m_bFixSized(false)
{  
    // 初始化代码
    this->setMouseTracking(true);

}


void cropRoi::paintEvent(QPaintEvent *event) 
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 绘制内部的线条
    drawInternalLines(painter); 
    // 绘制边框
    drawBorder(painter);
    // 绘制一些边框上的点
    drawPoints(painter);
    // 显示裁切框大小
    drawSizeText(painter);
    cropWidth  = this->width();
    cropHeight = this->height();
    //qDebug("width = %d, heigth = %d", this->width(), this->height());
}

void cropRoi::drawBorder(QPainter &painter)
{
    painter.setPen( QPen{QColor{3,125,203},SPACING});
    painter.drawRect( SPACING, SPACING, this->width()-SPACING*2,  this->height()-SPACING*2 );

}

void cropRoi::drawPoints(QPainter &painter)
{
    painter.setPen( QPen{QColor{3,125,203},POINTSIZE});
    painter.drawPoint(SPACING,SPACING);
    painter.drawPoint(this->width()/2, SPACING);
    painter.drawPoint(this->width()-SPACING, SPACING);
    painter.drawPoint(SPACING, this->height()/2);
    painter.drawPoint(SPACING, this->height()-SPACING);
    painter.drawPoint(this->width()-SPACING, this->height()/2);
    painter.drawPoint(this->width()-SPACING, this->height()-SPACING);
    painter.drawPoint(this->width()/2, this->height()-SPACING);
}

void cropRoi::drawInternalLines(QPainter &painter)
{
    QPainterPath cropRoi_path;
    
    cropRoi_path.addRect(SPACING, SPACING, this->width()-SPACING*2,  this->height()-SPACING*2);

    painter.setClipPath(cropRoi_path);
    painter.setClipping(true);

    painter.setPen( QPen{QColor{230,230,230},LINEWIDTH,Qt::DashLine});
    for (int i=1; i<m_widthCount; i++) {
        int width = this->width() / m_widthCount;
        painter.drawLine( i*width,  SPACING , i*width , this->height()-SPACING);
    }

    for (int i=1; i<m_heightCount; i++) {
        int heigth = this->height()/ m_heightCount;
        painter.drawLine( SPACING ,i*heigth,   this->width()- SPACING, i*heigth);
    }

    painter.setClipping(false);
}

void cropRoi::drawSizeText(QPainter &painter)
{
    painter.setPen( QPen{QColor{255,0,0}});
    //QString showText = QString("(") + QString::number(this->width() * m_cropbox->zoomRatio) + "," + QString::number(this->height() * m_cropbox->zoomRatio) + ")";
    QPointF topleft{(qreal)this->width()-(qreal)m_minWidth, (qreal)this->height()-(qreal)20};
    QSizeF size{(qreal)m_minWidth,20};
    QRectF position {topleft, size};
    QTextOption option{Qt::AlignVCenter | Qt::AlignRight };
    //painter.drawText(position, showText, option);
}

void cropRoi::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_bMovingFlag = true;
        m_dragPosition = event->globalPosition().toPoint() - this->pos();
    }
    event->accept();
}

void cropRoi::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    QPoint parent_point = mapToParent(point);
    QPoint global_point = event->globalPosition().toPoint();

    if (!m_bMovingFlag) {
        setDirection(point);
    } else {
        if (m_curDirec == NONE)
            handleMove(global_point);
        else
            handleResize(parent_point);
    }
    event->accept();
}


void cropRoi::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    if(event->button()==Qt::LeftButton)
        m_bMovingFlag = false;
    event->accept();
}

void cropRoi::handleMove(QPoint mouse_globalpos)
{
    QWidget* parent_widget = (QWidget *)this->parent();
    QPoint end_point = mouse_globalpos - m_dragPosition ;
    if (parent_widget) {
        int new_x = judgePosition(end_point.x(), 0, parent_widget->width()-this->width());
        end_point.setX(new_x);

        int new_y = judgePosition(end_point.y(), 0, parent_widget->height()-this->height());
        end_point.setY( new_y );
    }
    move( end_point );
    corpPoint = end_point; 
}

void cropRoi::handleResize(QPoint mouse_parentpos)
{
    if (!m_bMovingFlag)
        return;

    QRect rectMove = this->geometry();

    QPoint valid_point{mouse_parentpos} ;

    QWidget* parent_widget = (QWidget *)this->parent();
    valid_point.setX( judgePosition(valid_point.x(), 0, parent_widget->width()) );
    valid_point.setY( judgePosition(valid_point.y(), 0, parent_widget->height()) );

    switch(m_curDirec) {
    case UP:
        handleResizeUp(valid_point, rectMove, parent_widget);
        break;
    case DOWN:
        handleResizeDown(valid_point, rectMove, parent_widget);
        break;
    case LEFT:
        handleResizeLeft(valid_point, rectMove, parent_widget);
        break;
    case RIGHT:
        handleResizeRight(valid_point, rectMove, parent_widget);
        break;
    case RIGHTTOP:
        handleResizeRightTop(valid_point, rectMove, parent_widget);
        break;
    case RIGHTBOTTOM:
        handleResizeRightBottom(valid_point, rectMove, parent_widget);
        break;
    case LEFTTOP:
        handleResizeLeftTop(valid_point, rectMove, parent_widget);
        break;
    case LEFTBOTTOM:
        handleResizeLeftBottom(valid_point, rectMove, parent_widget);
        break;
    default:
        break;
    }

    this->setGeometry(rectMove);
}

void cropRoi::handleResizeUp(QPoint &valid_point, QRect &rectNew, const QWidget *parent_widget)
{
   if (rectNew.bottom() - valid_point.y() + 1  <= m_minHeight)
        valid_point.setY( rectNew.bottom() - m_minHeight + 1);

    rectNew.setTop( valid_point.y() );
}

void cropRoi::handleResizeDown(QPoint &valid_point, QRect &rectNew, const QWidget *parent_widget)
{
    if ( valid_point.y() - rectNew.top() + 1 <= m_minHeight)
        valid_point.setY( rectNew.top() + m_minHeight - 1);

    rectNew.setBottom( valid_point.y() );
}

void cropRoi::handleResizeLeft(QPoint &valid_point, QRect &rectNew, const QWidget *parent_widget)
{
    if ( rectNew.right() - valid_point.x() + 1 <= m_minWidth)
        valid_point.setX( rectNew.right() - m_minWidth + 1);

    rectNew.setLeft( valid_point.x() );
}

void cropRoi::handleResizeRight(QPoint &valid_point, QRect &rectNew, const QWidget *parent_widget)
{
    if ( valid_point.x() - rectNew.left() + 1 <= m_minWidth)
        valid_point.setX( rectNew.left() + m_minWidth - 1);

    rectNew.setRight( valid_point.x() );
}

void cropRoi::handleResizeRightTop(QPoint &valid_point, QRect &rectNew, const QWidget *parent_widget)
{ 
    if (valid_point.x() - rectNew.left() + 1 <= m_minWidth)
        valid_point.setX( rectNew.left() + m_minWidth - 1);

    if (rectNew.bottom() - valid_point.y() + 1 <= m_minHeight )
        valid_point.setY( rectNew.bottom() - m_minHeight + 1 );

    rectNew.setRight(valid_point.x());
    rectNew.setTop(valid_point.y());
}

void cropRoi::handleResizeRightBottom(QPoint &valid_point, QRect &rectNew, const QWidget *parent_widget)
{
    
    if (valid_point.x() - rectNew.left() + 1 <= m_minWidth)
        valid_point.setX( m_minWidth + rectNew.left() - 1 );

    if (valid_point.y() - rectNew.top() + 1 <= m_minHeight)
        valid_point.setY( rectNew.top() + m_minHeight - 1);
    

    rectNew.setRight(valid_point.x());
    rectNew.setBottom(valid_point.y());
}

void cropRoi::handleResizeLeftTop(QPoint &valid_point, QRect &rectNew, const QWidget *parent_widget)
{
    Q_UNUSED(parent_widget);
    
    if (rectNew.right() - valid_point.x() + 1 <= m_minWidth)
        valid_point.setX( rectNew.right() - m_minWidth + 1 );

    if (rectNew.bottom() - valid_point.y() + 1 <= m_minHeight)
        valid_point.setY( rectNew.bottom() - m_minHeight + 1);
    

    rectNew.setLeft(valid_point.x());
    rectNew.setTop(valid_point.y());
}

void cropRoi::handleResizeLeftBottom(QPoint &valid_point, QRect &rectNew, const QWidget *parent_widget)
{
    Q_UNUSED(parent_widget);

    
    if (rectNew.right() - valid_point.x() + 1 <= m_minWidth)
        valid_point.setX( rectNew.right() - m_minWidth + 1);

    if (valid_point.y() - rectNew.top() + 1 <= m_minHeight)
        valid_point.setY( rectNew.top() + m_minHeight - 1);
    

    rectNew.setLeft(valid_point.x());
    rectNew.setBottom(valid_point.y());
}

void cropRoi::setDirection(QPoint point)
{
    if (m_bFixSized) {
        m_curDirec = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
        return;
    }

    int width = this->width();
    int heigth = this->height();

    if ( PADDING >= point.x() && 0 <= point.x() &&  PADDING  >= point.y() && 0 <= point.y())
    {
        m_curDirec = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if(width - PADDING <= point.x() && width >= point.x() && heigth - PADDING <= point.y() && heigth >= point.y())
    {
        m_curDirec = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if(PADDING >= point.x() && 0 <= point.x() && heigth - PADDING <= point.y() && heigth >= point.y())
    {
        m_curDirec = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if(PADDING >= point.y() && 0 <= point.y() && width - PADDING <= point.x() && width >= point.x())
    {
        m_curDirec = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if(PADDING >= point.x() && 0 <= point.x())
    {
        m_curDirec = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if(PADDING >= point.y() && 0 <= point.y())
    {
        m_curDirec = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else if(width - PADDING <= point.x() && width >= point.x())
    {
        m_curDirec = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if(heigth - PADDING <= point.y() && heigth >= point.y())
    {
        m_curDirec = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else
    {
        m_curDirec = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

inline int cropRoi::judgePosition(int origin, int min, int max)
{
    if (origin < min)  return min;
    if (origin > max)  return max;
    return origin;
}
