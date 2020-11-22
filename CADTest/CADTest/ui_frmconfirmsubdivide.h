/********************************************************************************
** Form generated from reading UI file 'frmconfirmsubdivide.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMCONFIRMSUBDIVIDE_H
#define UI_FRMCONFIRMSUBDIVIDE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FrmConfirmSubdivide
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *txtVal;
    QPushButton *btnOK;
    QPushButton *btnCancel;

    void setupUi(QDialog *FrmConfirmSubdivide)
    {
        if (FrmConfirmSubdivide->objectName().isEmpty())
            FrmConfirmSubdivide->setObjectName(QString::fromUtf8("FrmConfirmSubdivide"));
        FrmConfirmSubdivide->resize(380, 100);
        FrmConfirmSubdivide->setMinimumSize(QSize(380, 100));
        FrmConfirmSubdivide->setMaximumSize(QSize(380, 100));
        label = new QLabel(FrmConfirmSubdivide);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 54, 12));
        label_2 = new QLabel(FrmConfirmSubdivide);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(170, 30, 54, 12));
        label_3 = new QLabel(FrmConfirmSubdivide);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 10, 54, 12));
        txtVal = new QLineEdit(FrmConfirmSubdivide);
        txtVal->setObjectName(QString::fromUtf8("txtVal"));
        txtVal->setGeometry(QRect(70, 30, 91, 20));
        btnOK = new QPushButton(FrmConfirmSubdivide);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(210, 70, 75, 23));
        btnCancel = new QPushButton(FrmConfirmSubdivide);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(300, 70, 75, 23));

        retranslateUi(FrmConfirmSubdivide);

        QMetaObject::connectSlotsByName(FrmConfirmSubdivide);
    } // setupUi

    void retranslateUi(QDialog *FrmConfirmSubdivide)
    {
        FrmConfirmSubdivide->setWindowTitle(QCoreApplication::translate("FrmConfirmSubdivide", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("FrmConfirmSubdivide", "Vertex 1", nullptr));
        label_2->setText(QCoreApplication::translate("FrmConfirmSubdivide", "Vertex 2", nullptr));
        label_3->setText(QCoreApplication::translate("FrmConfirmSubdivide", "Value", nullptr));
        btnOK->setText(QCoreApplication::translate("FrmConfirmSubdivide", "OK", nullptr));
        btnCancel->setText(QCoreApplication::translate("FrmConfirmSubdivide", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FrmConfirmSubdivide: public Ui_FrmConfirmSubdivide {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMCONFIRMSUBDIVIDE_H
