/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionDefault_Scene;
    QAction *actionEmpty_Scene;
    QAction *actionEnter_Exit_EditMode_Tab;
    QAction *actionMove_G;
    QAction *actionRotate_R;
    QAction *actionScale_S;
    QAction *actionSelect_All_A;
    QAction *actionDelete_delete;
    QAction *actionVertex;
    QAction *actionEdge_num2;
    QAction *actionConnect_Selected_F;
    QAction *actionExtrude_E;
    QAction *actionCombine_Selected_J;
    QAction *actionGrading_Settings;
    QWidget *centralwidget;
    QGraphicsView *gpvView;
    QLabel *lblMode;
    QPushButton *btnEllipse;
    QPushButton *btnLine;
    QPushButton *btnTLine;
    QPushButton *btnSubdivide;
    QPushButton *btnGrading;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuNew;
    QMenu *menuOptions;
    QMenu *menuSelect_Mode;
    QMenu *menuVertex_Tools;
    QMenu *menuObject_Tools;
    QMenu *menuGrading_Settings;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 720);
        MainWindow->setMinimumSize(QSize(1280, 720));
        MainWindow->setMaximumSize(QSize(1280, 720));
        MainWindow->setFocusPolicy(Qt::NoFocus);
        actionDefault_Scene = new QAction(MainWindow);
        actionDefault_Scene->setObjectName(QString::fromUtf8("actionDefault_Scene"));
        actionEmpty_Scene = new QAction(MainWindow);
        actionEmpty_Scene->setObjectName(QString::fromUtf8("actionEmpty_Scene"));
        actionEnter_Exit_EditMode_Tab = new QAction(MainWindow);
        actionEnter_Exit_EditMode_Tab->setObjectName(QString::fromUtf8("actionEnter_Exit_EditMode_Tab"));
        actionMove_G = new QAction(MainWindow);
        actionMove_G->setObjectName(QString::fromUtf8("actionMove_G"));
        actionRotate_R = new QAction(MainWindow);
        actionRotate_R->setObjectName(QString::fromUtf8("actionRotate_R"));
        actionScale_S = new QAction(MainWindow);
        actionScale_S->setObjectName(QString::fromUtf8("actionScale_S"));
        actionSelect_All_A = new QAction(MainWindow);
        actionSelect_All_A->setObjectName(QString::fromUtf8("actionSelect_All_A"));
        actionDelete_delete = new QAction(MainWindow);
        actionDelete_delete->setObjectName(QString::fromUtf8("actionDelete_delete"));
        actionVertex = new QAction(MainWindow);
        actionVertex->setObjectName(QString::fromUtf8("actionVertex"));
        actionEdge_num2 = new QAction(MainWindow);
        actionEdge_num2->setObjectName(QString::fromUtf8("actionEdge_num2"));
        actionConnect_Selected_F = new QAction(MainWindow);
        actionConnect_Selected_F->setObjectName(QString::fromUtf8("actionConnect_Selected_F"));
        actionExtrude_E = new QAction(MainWindow);
        actionExtrude_E->setObjectName(QString::fromUtf8("actionExtrude_E"));
        actionCombine_Selected_J = new QAction(MainWindow);
        actionCombine_Selected_J->setObjectName(QString::fromUtf8("actionCombine_Selected_J"));
        actionGrading_Settings = new QAction(MainWindow);
        actionGrading_Settings->setObjectName(QString::fromUtf8("actionGrading_Settings"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gpvView = new QGraphicsView(centralwidget);
        gpvView->setObjectName(QString::fromUtf8("gpvView"));
        gpvView->setGeometry(QRect(80, 10, 1191, 661));
        gpvView->setMinimumSize(QSize(1191, 661));
        gpvView->setMaximumSize(QSize(1191, 661));
        lblMode = new QLabel(centralwidget);
        lblMode->setObjectName(QString::fromUtf8("lblMode"));
        lblMode->setGeometry(QRect(90, 20, 71, 16));
        btnEllipse = new QPushButton(centralwidget);
        btnEllipse->setObjectName(QString::fromUtf8("btnEllipse"));
        btnEllipse->setGeometry(QRect(10, 10, 61, 61));
        btnEllipse->setFocusPolicy(Qt::NoFocus);
        btnLine = new QPushButton(centralwidget);
        btnLine->setObjectName(QString::fromUtf8("btnLine"));
        btnLine->setGeometry(QRect(10, 80, 61, 61));
        btnLine->setFocusPolicy(Qt::NoFocus);
        btnTLine = new QPushButton(centralwidget);
        btnTLine->setObjectName(QString::fromUtf8("btnTLine"));
        btnTLine->setGeometry(QRect(10, 150, 61, 61));
        btnTLine->setFocusPolicy(Qt::NoFocus);
        btnSubdivide = new QPushButton(centralwidget);
        btnSubdivide->setObjectName(QString::fromUtf8("btnSubdivide"));
        btnSubdivide->setGeometry(QRect(10, 290, 61, 61));
        btnSubdivide->setFocusPolicy(Qt::NoFocus);
        btnSubdivide->setFlat(false);
        btnGrading = new QPushButton(centralwidget);
        btnGrading->setObjectName(QString::fromUtf8("btnGrading"));
        btnGrading->setGeometry(QRect(10, 220, 61, 61));
        btnGrading->setFocusPolicy(Qt::NoFocus);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1280, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuNew = new QMenu(menuFile);
        menuNew->setObjectName(QString::fromUtf8("menuNew"));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuSelect_Mode = new QMenu(menuOptions);
        menuSelect_Mode->setObjectName(QString::fromUtf8("menuSelect_Mode"));
        menuVertex_Tools = new QMenu(menuOptions);
        menuVertex_Tools->setObjectName(QString::fromUtf8("menuVertex_Tools"));
        menuObject_Tools = new QMenu(menuOptions);
        menuObject_Tools->setObjectName(QString::fromUtf8("menuObject_Tools"));
        menuGrading_Settings = new QMenu(menubar);
        menuGrading_Settings->setObjectName(QString::fromUtf8("menuGrading_Settings"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menubar->addAction(menuGrading_Settings->menuAction());
        menuFile->addAction(menuNew->menuAction());
        menuNew->addAction(actionDefault_Scene);
        menuNew->addAction(actionEmpty_Scene);
        menuOptions->addAction(actionEnter_Exit_EditMode_Tab);
        menuOptions->addSeparator();
        menuOptions->addAction(actionMove_G);
        menuOptions->addAction(actionRotate_R);
        menuOptions->addAction(actionScale_S);
        menuOptions->addSeparator();
        menuOptions->addAction(actionSelect_All_A);
        menuOptions->addAction(actionDelete_delete);
        menuOptions->addSeparator();
        menuOptions->addAction(menuSelect_Mode->menuAction());
        menuOptions->addSeparator();
        menuOptions->addAction(menuVertex_Tools->menuAction());
        menuOptions->addAction(menuObject_Tools->menuAction());
        menuSelect_Mode->addAction(actionVertex);
        menuSelect_Mode->addSeparator();
        menuSelect_Mode->addAction(actionEdge_num2);
        menuVertex_Tools->addAction(actionConnect_Selected_F);
        menuVertex_Tools->addAction(actionExtrude_E);
        menuObject_Tools->addAction(actionCombine_Selected_J);
        menuGrading_Settings->addAction(actionGrading_Settings);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CADTest", nullptr));
        actionDefault_Scene->setText(QCoreApplication::translate("MainWindow", "Default Scene", nullptr));
        actionEmpty_Scene->setText(QCoreApplication::translate("MainWindow", "Empty Scene", nullptr));
        actionEnter_Exit_EditMode_Tab->setText(QCoreApplication::translate("MainWindow", "Enter/Exit EditMode(Tab)", nullptr));
        actionMove_G->setText(QCoreApplication::translate("MainWindow", "Move(G)", nullptr));
        actionRotate_R->setText(QCoreApplication::translate("MainWindow", "Rotate(R)", nullptr));
        actionScale_S->setText(QCoreApplication::translate("MainWindow", "Scale(S)", nullptr));
        actionSelect_All_A->setText(QCoreApplication::translate("MainWindow", "Select All(A)", nullptr));
        actionDelete_delete->setText(QCoreApplication::translate("MainWindow", "Delete(delete)", nullptr));
        actionVertex->setText(QCoreApplication::translate("MainWindow", "Vertex(num1)", nullptr));
        actionEdge_num2->setText(QCoreApplication::translate("MainWindow", "Edge(num2)", nullptr));
        actionConnect_Selected_F->setText(QCoreApplication::translate("MainWindow", "Connect Selected(F)", nullptr));
        actionExtrude_E->setText(QCoreApplication::translate("MainWindow", "Extrude(E)", nullptr));
        actionCombine_Selected_J->setText(QCoreApplication::translate("MainWindow", "Combine Selected(J)", nullptr));
        actionGrading_Settings->setText(QCoreApplication::translate("MainWindow", "Change Grading Setting", nullptr));
        lblMode->setText(QCoreApplication::translate("MainWindow", "Object Mode", nullptr));
        btnEllipse->setText(QCoreApplication::translate("MainWindow", "Ellipse", nullptr));
        btnLine->setText(QCoreApplication::translate("MainWindow", "Line", nullptr));
        btnTLine->setText(QCoreApplication::translate("MainWindow", "T Line", nullptr));
        btnSubdivide->setText(QCoreApplication::translate("MainWindow", "Subdivide", nullptr));
        btnGrading->setText(QCoreApplication::translate("MainWindow", "Grading", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuNew->setTitle(QCoreApplication::translate("MainWindow", "New", nullptr));
        menuOptions->setTitle(QCoreApplication::translate("MainWindow", "Options", nullptr));
        menuSelect_Mode->setTitle(QCoreApplication::translate("MainWindow", "Select Mode", nullptr));
        menuVertex_Tools->setTitle(QCoreApplication::translate("MainWindow", "Vertex Tools", nullptr));
        menuObject_Tools->setTitle(QCoreApplication::translate("MainWindow", "Object Tools", nullptr));
        menuGrading_Settings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
