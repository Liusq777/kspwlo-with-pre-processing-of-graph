/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *calculateButton;
    QLineEdit *input2;
    QLineEdit *input1;
    QLabel *label_1;
    QLabel *lable_2;
    QLabel *label_3;
    QLineEdit *showResult;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(484, 560);
        Widget->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 245, 244);"));
        calculateButton = new QPushButton(Widget);
        calculateButton->setObjectName("calculateButton");
        calculateButton->setGeometry(QRect(200, 260, 101, 31));
        input2 = new QLineEdit(Widget);
        input2->setObjectName("input2");
        input2->setGeometry(QRect(200, 110, 121, 31));
        input1 = new QLineEdit(Widget);
        input1->setObjectName("input1");
        input1->setGeometry(QRect(200, 40, 121, 31));
        label_1 = new QLabel(Widget);
        label_1->setObjectName("label_1");
        label_1->setGeometry(QRect(80, 40, 91, 20));
        lable_2 = new QLabel(Widget);
        lable_2->setObjectName("lable_2");
        lable_2->setGeometry(QRect(80, 110, 91, 21));
        label_3 = new QLabel(Widget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(80, 440, 67, 17));
        showResult = new QLineEdit(Widget);
        showResult->setObjectName("showResult");
        showResult->setGeometry(QRect(160, 390, 171, 131));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        calculateButton->setText(QCoreApplication::translate("Widget", "calculate", nullptr));
        label_1->setText(QCoreApplication::translate("Widget", "parameter 1", nullptr));
        lable_2->setText(QCoreApplication::translate("Widget", "parameter 2", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "result", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
