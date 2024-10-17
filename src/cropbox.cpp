#include "cropbox.h"
#include "ui_cropbox.h"

#include "IndustryCheck.h"
#include "ui_IndustryCheck.h"

#include "cropRoi.h"
#include "myThread.h"

cropbox::cropbox(IndustryCheck&m_industrycheck_, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::cropbox)
    , m_industrycheck(m_industrycheck_)
{
    ui->setupUi(this);
    m_cropRoi = new cropRoi(this->ui->label);
    m_cropRoi->resize(100, 100);
    this->setMouseTracking(true);
    label_imageshow();

    connect(ui->confirmBtn, QOverload<bool>::of(&QPushButton::clicked), this, &cropbox::slot_confirm_btn);
    connect(ui->cancelBtn,  QOverload<bool>::of(&QPushButton::clicked), this, &cropbox::slot_cancel_btn);
}

cropbox::~cropbox()
{
    delete ui;
}

void cropbox::label_imageshow()
{
    if(m_industrycheck.displayImage.isNull())
    {
        ui->confirmBtn->setEnabled(false);
        ui->cancelBtn->setEnabled(false);
        ui->confirmBtn->setStyleSheet("background-color:gray");
        ui->cancelBtn->setStyleSheet("background-color:gray");
    }
    else
    {
        ui->confirmBtn->setEnabled(true);
        ui->cancelBtn->setEnabled(true);
        ui->label->setPixmap(QPixmap::fromImage(m_industrycheck.displayImage));
        ui->label->setScaledContents(true);
        zoomRatio = m_industrycheck.displayImage.width() / ui->label->width();
    }
}

void cropbox::slot_confirm_btn()
{
    QRect cropRect(m_cropRoi->corpPoint * zoomRatio, QSize(m_cropRoi->cropWidth * zoomRatio, m_cropRoi->cropHeight * zoomRatio));
    cropped = m_industrycheck.displayImage.copy(cropRect);
    qDebug("FIRST zoo =%d", zoomRatio);
    qDebug("FIRST cv_roi:%d, %d", cropped.width(), cropped.height());
    cropped.save("data/marchROI.jpg");
    m_industrycheck.qcvROI = cropped;
    this->close();
}

void cropbox::slot_cancel_btn()
{
    this->close();
}
