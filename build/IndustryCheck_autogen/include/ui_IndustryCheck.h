/********************************************************************************
** Form generated from reading UI file 'IndustryCheck.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INDUSTRYCHECK_H
#define UI_INDUSTRYCHECK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IndustryCheck
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox_0;
    QPushButton *connectDeviceBtn;
    QLabel *deviceNameLabel;
    QComboBox *deviceComboBox;
    QGroupBox *groupBox_1;
    QLabel *label;
    QGroupBox *groupBox_2;
    QTextBrowser *textBrowser;
    QGroupBox *groupBox_3;
    QLabel *captureModelabel;
    QComboBox *captureModecomboBox;
    QLabel *triggerModelabel;
    QComboBox *triggerModecomboBox;
    QPushButton *captureStateBtn;
    QPushButton *settempRoiBtn;
    QGroupBox *groupBox_4;
    QLabel *binarizationThreshold;
    QSlider *binarizationSlider;
    QLabel *binarizationthresholdNum;
    QLabel *morphkernal;
    QLabel *morphkernalNum;
    QSlider *morphkernalSlider;
    QLabel *canny;
    QLineEdit *cannyEditNum1;
    QLabel *cannyNum1;
    QLabel *cannyNum2;
    QLineEdit *cannyEditNum2;
    QLabel *contoursArea;
    QLineEdit *contoursAreaEdit;
    QPushButton *saveParameterBtn;
    QLabel *contoursLength;
    QLineEdit *contoursLengthEdit;
    QLabel *tempMatch;
    QPushButton *tempMatchRoi;
    QGroupBox *groupBox_5;
    QLabel *geometricDetection;
    QPushButton *detectionBtn;
    QLabel *geometricCalculation;
    QPushButton *calculationBtn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QWidget *IndustryCheck)
    {
        if (IndustryCheck->objectName().isEmpty())
            IndustryCheck->setObjectName("IndustryCheck");
        IndustryCheck->resize(1249, 943);
        QFont font;
        font.setPointSize(10);
        IndustryCheck->setFont(font);
        centralwidget = new QWidget(IndustryCheck);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setGeometry(QRect(0, 0, 1241, 941));
        groupBox_0 = new QGroupBox(centralwidget);
        groupBox_0->setObjectName("groupBox_0");
        groupBox_0->setGeometry(QRect(932, 10, 260, 91));
        connectDeviceBtn = new QPushButton(groupBox_0);
        connectDeviceBtn->setObjectName("connectDeviceBtn");
        connectDeviceBtn->setGeometry(QRect(20, 50, 220, 30));
        connectDeviceBtn->setFont(font);
        deviceNameLabel = new QLabel(groupBox_0);
        deviceNameLabel->setObjectName("deviceNameLabel");
        deviceNameLabel->setGeometry(QRect(20, 10, 80, 30));
        deviceNameLabel->setFont(font);
        deviceComboBox = new QComboBox(groupBox_0);
        deviceComboBox->setObjectName("deviceComboBox");
        deviceComboBox->setGeometry(QRect(90, 10, 150, 30));
        groupBox_1 = new QGroupBox(centralwidget);
        groupBox_1->setObjectName("groupBox_1");
        groupBox_1->setGeometry(QRect(10, 10, 912, 608));
        label = new QLabel(groupBox_1);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 912, 608));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 620, 912, 211));
        textBrowser = new QTextBrowser(groupBox_2);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(0, 0, 911, 211));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(932, 120, 260, 181));
        groupBox_3->setFont(font);
        captureModelabel = new QLabel(groupBox_3);
        captureModelabel->setObjectName("captureModelabel");
        captureModelabel->setGeometry(QRect(20, 20, 80, 30));
        captureModecomboBox = new QComboBox(groupBox_3);
        captureModecomboBox->setObjectName("captureModecomboBox");
        captureModecomboBox->setGeometry(QRect(90, 20, 150, 30));
        triggerModelabel = new QLabel(groupBox_3);
        triggerModelabel->setObjectName("triggerModelabel");
        triggerModelabel->setGeometry(QRect(20, 60, 80, 30));
        triggerModecomboBox = new QComboBox(groupBox_3);
        triggerModecomboBox->setObjectName("triggerModecomboBox");
        triggerModecomboBox->setGeometry(QRect(90, 60, 150, 30));
        captureStateBtn = new QPushButton(groupBox_3);
        captureStateBtn->setObjectName("captureStateBtn");
        captureStateBtn->setGeometry(QRect(20, 100, 220, 30));
        captureStateBtn->setFont(font);
        settempRoiBtn = new QPushButton(groupBox_3);
        settempRoiBtn->setObjectName("settempRoiBtn");
        settempRoiBtn->setGeometry(QRect(20, 140, 220, 30));
        settempRoiBtn->setFont(font);
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(932, 320, 260, 361));
        binarizationThreshold = new QLabel(groupBox_4);
        binarizationThreshold->setObjectName("binarizationThreshold");
        binarizationThreshold->setGeometry(QRect(20, 60, 80, 30));
        binarizationSlider = new QSlider(groupBox_4);
        binarizationSlider->setObjectName("binarizationSlider");
        binarizationSlider->setEnabled(false);
        binarizationSlider->setGeometry(QRect(20, 90, 220, 22));
        binarizationSlider->setMaximum(255);
        binarizationSlider->setOrientation(Qt::Orientation::Horizontal);
        binarizationthresholdNum = new QLabel(groupBox_4);
        binarizationthresholdNum->setObjectName("binarizationthresholdNum");
        binarizationthresholdNum->setGeometry(QRect(140, 60, 100, 30));
        binarizationthresholdNum->setAlignment(Qt::AlignmentFlag::AlignCenter);
        morphkernal = new QLabel(groupBox_4);
        morphkernal->setObjectName("morphkernal");
        morphkernal->setGeometry(QRect(20, 110, 80, 30));
        morphkernalNum = new QLabel(groupBox_4);
        morphkernalNum->setObjectName("morphkernalNum");
        morphkernalNum->setGeometry(QRect(140, 110, 100, 30));
        morphkernalNum->setAlignment(Qt::AlignmentFlag::AlignCenter);
        morphkernalSlider = new QSlider(groupBox_4);
        morphkernalSlider->setObjectName("morphkernalSlider");
        morphkernalSlider->setEnabled(false);
        morphkernalSlider->setGeometry(QRect(20, 140, 220, 22));
        morphkernalSlider->setMaximum(30);
        morphkernalSlider->setOrientation(Qt::Orientation::Horizontal);
        canny = new QLabel(groupBox_4);
        canny->setObjectName("canny");
        canny->setGeometry(QRect(20, 170, 80, 30));
        cannyEditNum1 = new QLineEdit(groupBox_4);
        cannyEditNum1->setObjectName("cannyEditNum1");
        cannyEditNum1->setEnabled(false);
        cannyEditNum1->setGeometry(QRect(70, 200, 45, 25));
        cannyEditNum1->setAlignment(Qt::AlignmentFlag::AlignCenter);
        cannyNum1 = new QLabel(groupBox_4);
        cannyNum1->setObjectName("cannyNum1");
        cannyNum1->setGeometry(QRect(20, 200, 40, 30));
        cannyNum2 = new QLabel(groupBox_4);
        cannyNum2->setObjectName("cannyNum2");
        cannyNum2->setGeometry(QRect(130, 200, 40, 30));
        cannyEditNum2 = new QLineEdit(groupBox_4);
        cannyEditNum2->setObjectName("cannyEditNum2");
        cannyEditNum2->setEnabled(false);
        cannyEditNum2->setGeometry(QRect(185, 200, 45, 25));
        cannyEditNum2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        contoursArea = new QLabel(groupBox_4);
        contoursArea->setObjectName("contoursArea");
        contoursArea->setGeometry(QRect(20, 280, 91, 30));
        contoursAreaEdit = new QLineEdit(groupBox_4);
        contoursAreaEdit->setObjectName("contoursAreaEdit");
        contoursAreaEdit->setEnabled(false);
        contoursAreaEdit->setGeometry(QRect(130, 280, 100, 25));
        contoursAreaEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        saveParameterBtn = new QPushButton(groupBox_4);
        saveParameterBtn->setObjectName("saveParameterBtn");
        saveParameterBtn->setGeometry(QRect(20, 320, 220, 30));
        saveParameterBtn->setFont(font);
        contoursLength = new QLabel(groupBox_4);
        contoursLength->setObjectName("contoursLength");
        contoursLength->setGeometry(QRect(20, 240, 91, 30));
        contoursLengthEdit = new QLineEdit(groupBox_4);
        contoursLengthEdit->setObjectName("contoursLengthEdit");
        contoursLengthEdit->setEnabled(false);
        contoursLengthEdit->setGeometry(QRect(130, 240, 100, 25));
        contoursLengthEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        tempMatch = new QLabel(groupBox_4);
        tempMatch->setObjectName("tempMatch");
        tempMatch->setGeometry(QRect(20, 20, 80, 30));
        tempMatchRoi = new QPushButton(groupBox_4);
        tempMatchRoi->setObjectName("tempMatchRoi");
        tempMatchRoi->setEnabled(false);
        tempMatchRoi->setGeometry(QRect(90, 20, 151, 30));
        tempMatchRoi->setFont(font);
        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(932, 720, 260, 111));
        geometricDetection = new QLabel(groupBox_5);
        geometricDetection->setObjectName("geometricDetection");
        geometricDetection->setGeometry(QRect(20, 10, 80, 30));
        detectionBtn = new QPushButton(groupBox_5);
        detectionBtn->setObjectName("detectionBtn");
        detectionBtn->setGeometry(QRect(140, 10, 100, 30));
        geometricCalculation = new QLabel(groupBox_5);
        geometricCalculation->setObjectName("geometricCalculation");
        geometricCalculation->setGeometry(QRect(20, 50, 80, 30));
        calculationBtn = new QPushButton(groupBox_5);
        calculationBtn->setObjectName("calculationBtn");
        calculationBtn->setGeometry(QRect(140, 50, 100, 30));
        menubar = new QMenuBar(IndustryCheck);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1202, 33));
        statusbar = new QStatusBar(IndustryCheck);
        statusbar->setObjectName("statusbar");
        statusbar->setGeometry(QRect(0, 0, 3, 21));

        retranslateUi(IndustryCheck);

        QMetaObject::connectSlotsByName(IndustryCheck);
    } // setupUi

    void retranslateUi(QWidget *IndustryCheck)
    {
        IndustryCheck->setWindowTitle(QCoreApplication::translate("IndustryCheck", "IndustryCheck", nullptr));
        groupBox_0->setTitle(QString());
        connectDeviceBtn->setText(QCoreApplication::translate("IndustryCheck", "\346\211\223\345\274\200", nullptr));
        deviceNameLabel->setText(QCoreApplication::translate("IndustryCheck", "\350\256\276\345\244\207\345\220\215\357\274\232", nullptr));
        groupBox_1->setTitle(QString());
        label->setText(QString());
        groupBox_2->setTitle(QString());
        groupBox_3->setTitle(QCoreApplication::translate("IndustryCheck", "\345\233\276\345\203\217\351\207\207\351\233\206", nullptr));
        captureModelabel->setText(QCoreApplication::translate("IndustryCheck", "\351\207\207\351\233\206\346\250\241\345\274\217\357\274\232", nullptr));
        triggerModelabel->setText(QCoreApplication::translate("IndustryCheck", "\350\247\246\345\217\221\346\250\241\345\274\217\357\274\232", nullptr));
        captureStateBtn->setText(QCoreApplication::translate("IndustryCheck", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        settempRoiBtn->setText(QCoreApplication::translate("IndustryCheck", "\350\256\276\347\275\256\346\250\241\346\235\277ROI", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("IndustryCheck", "\345\233\276\345\203\217\345\244\204\347\220\206", nullptr));
        binarizationThreshold->setText(QCoreApplication::translate("IndustryCheck", "\344\272\214\345\200\274\345\214\226\351\230\210\345\200\274\357\274\232", nullptr));
        binarizationthresholdNum->setText(QCoreApplication::translate("IndustryCheck", "0", nullptr));
        morphkernal->setText(QCoreApplication::translate("IndustryCheck", "\345\275\242\346\200\201\345\255\246\346\240\270\345\277\203\357\274\232", nullptr));
        morphkernalNum->setText(QCoreApplication::translate("IndustryCheck", "0", nullptr));
        canny->setText(QCoreApplication::translate("IndustryCheck", "Canny\350\276\271\347\274\230\357\274\232", nullptr));
        cannyNum1->setText(QCoreApplication::translate("IndustryCheck", "\351\230\210\345\200\2741\357\274\232", nullptr));
        cannyNum2->setText(QCoreApplication::translate("IndustryCheck", "\351\230\210\345\200\2742\357\274\232", nullptr));
        contoursArea->setText(QCoreApplication::translate("IndustryCheck", "\350\277\207\346\273\244\350\275\256\345\273\223\351\235\242\347\247\257\357\274\232", nullptr));
        saveParameterBtn->setText(QCoreApplication::translate("IndustryCheck", "\350\256\276\347\275\256\345\217\202\346\225\260", nullptr));
        contoursLength->setText(QCoreApplication::translate("IndustryCheck", "\350\277\207\346\273\244\350\275\256\345\273\223\351\225\277\345\272\246\357\274\232", nullptr));
        tempMatch->setText(QCoreApplication::translate("IndustryCheck", "\346\250\241\346\235\277\345\214\271\351\205\215\357\274\232", nullptr));
        tempMatchRoi->setText(QCoreApplication::translate("IndustryCheck", "\345\214\271\351\205\215\346\250\241\346\235\277ROI", nullptr));
        groupBox_5->setTitle(QString());
        geometricDetection->setText(QCoreApplication::translate("IndustryCheck", "\345\207\240\344\275\225\346\243\200\346\265\213\357\274\232", nullptr));
        detectionBtn->setText(QCoreApplication::translate("IndustryCheck", "\345\274\200\345\247\213\346\243\200\346\265\213", nullptr));
        geometricCalculation->setText(QCoreApplication::translate("IndustryCheck", "\345\207\240\344\275\225\350\256\241\347\256\227\357\274\232", nullptr));
        calculationBtn->setText(QCoreApplication::translate("IndustryCheck", "\345\274\200\345\247\213\350\256\241\347\256\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IndustryCheck: public Ui_IndustryCheck {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INDUSTRYCHECK_H
