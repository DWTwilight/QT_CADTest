/********************************************************************************
** Form generated from reading UI file 'frmconfirmcreation.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMCONFIRMCREATION_H
#define UI_FRMCONFIRMCREATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FrmConfirmCreation
{
public:
    QLabel *lblFactorA;
    QLabel *lblFactorB;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QLineEdit *txtFactorA;
    QLineEdit *txtFactorB;

    void setupUi(QDialog *FrmConfirmCreation)
    {
        if (FrmConfirmCreation->objectName().isEmpty())
            FrmConfirmCreation->setObjectName(QString::fromUtf8("FrmConfirmCreation"));
        FrmConfirmCreation->resize(360, 120);
        FrmConfirmCreation->setMinimumSize(QSize(360, 120));
        FrmConfirmCreation->setMaximumSize(QSize(360, 120));
        lblFactorA = new QLabel(FrmConfirmCreation);
        lblFactorA->setObjectName(QString::fromUtf8("lblFactorA"));
        lblFactorA->setGeometry(QRect(20, 20, 54, 12));
        lblFactorB = new QLabel(FrmConfirmCreation);
        lblFactorB->setObjectName(QString::fromUtf8("lblFactorB"));
        lblFactorB->setGeometry(QRect(20, 50, 54, 12));
        btnOK = new QPushButton(FrmConfirmCreation);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(190, 80, 75, 23));
        btnCancel = new QPushButton(FrmConfirmCreation);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(280, 80, 75, 23));
        txtFactorA = new QLineEdit(FrmConfirmCreation);
        txtFactorA->setObjectName(QString::fromUtf8("txtFactorA"));
        txtFactorA->setGeometry(QRect(90, 20, 101, 20));
        txtFactorB = new QLineEdit(FrmConfirmCreation);
        txtFactorB->setObjectName(QString::fromUtf8("txtFactorB"));
        txtFactorB->setGeometry(QRect(90, 50, 101, 20));

        retranslateUi(FrmConfirmCreation);

        QMetaObject::connectSlotsByName(FrmConfirmCreation);
    } // setupUi

    void retranslateUi(QDialog *FrmConfirmCreation)
    {
        FrmConfirmCreation->setWindowTitle(QCoreApplication::translate("FrmConfirmCreation", "Dialog", nullptr));
        lblFactorA->setText(QCoreApplication::translate("FrmConfirmCreation", "TextLabel", nullptr));
        lblFactorB->setText(QCoreApplication::translate("FrmConfirmCreation", "TextLabel", nullptr));
        btnOK->setText(QCoreApplication::translate("FrmConfirmCreation", "OK", nullptr));
        btnCancel->setText(QCoreApplication::translate("FrmConfirmCreation", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FrmConfirmCreation: public Ui_FrmConfirmCreation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMCONFIRMCREATION_H
