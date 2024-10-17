/********************************************************************************
** Form generated from reading UI file 'cropbox.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CROPBOX_H
#define UI_CROPBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cropbox
{
public:
    QWidget *widget;
    QLabel *label;
    QPushButton *confirmBtn;
    QPushButton *cancelBtn;

    void setupUi(QWidget *cropbox)
    {
        if (cropbox->objectName().isEmpty())
            cropbox->setObjectName("cropbox");
        cropbox->resize(1388, 982);
        cropbox->setStyleSheet(QString::fromUtf8("background-color: rgb(236, 236, 236);"));
        widget = new QWidget(cropbox);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 10, 1368, 912));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 1368, 912));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        confirmBtn = new QPushButton(cropbox);
        confirmBtn->setObjectName("confirmBtn");
        confirmBtn->setGeometry(QRect(1180, 940, 90, 30));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        confirmBtn->setFont(font);
        confirmBtn->setStyleSheet(QString::fromUtf8("QPushButton:hover{\n"
"	background-color: rgb(236,71,88);\n"
"}\n"
"\n"
"QPushButton {\n"
"    color: rgb(255, 255, 255);\n"
"	background-color: rgb(237, 85, 101);\n"
"}"));
        cancelBtn = new QPushButton(cropbox);
        cancelBtn->setObjectName("cancelBtn");
        cancelBtn->setGeometry(QRect(1290, 940, 90, 30));
        cancelBtn->setFont(font);
        cancelBtn->setStyleSheet(QString::fromUtf8("QPushButton:hover{\n"
"	background-color: rgb(24,166,137)\n"
"}\n"
"\n"
"QPushButton {\n"
"    color: rgb(255, 255, 255);\n"
"	background-color: rgb(26, 177, 146);\n"
"}"));

        retranslateUi(cropbox);

        QMetaObject::connectSlotsByName(cropbox);
    } // setupUi

    void retranslateUi(QWidget *cropbox)
    {
        cropbox->setWindowTitle(QCoreApplication::translate("cropbox", "cropROI", nullptr));
        label->setText(QString());
        confirmBtn->setText(QCoreApplication::translate("cropbox", "\347\241\256\350\256\244", nullptr));
        cancelBtn->setText(QCoreApplication::translate("cropbox", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cropbox: public Ui_cropbox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CROPBOX_H
