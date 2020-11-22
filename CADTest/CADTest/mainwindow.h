#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "cadpart.h"
#include "cadscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

	void SetEditMode(bool);

private slots:
    void on_actionDefault_Scene_triggered();
    void on_actionEmpty_Scene_triggered();
    void on_actionEnter_Exit_EditMode_Tab_triggered();
    void on_actionMove_G_triggered();
    void on_actionRotate_R_triggered();
    void on_actionScale_S_triggered();
    void on_actionSelect_All_A_triggered();
    void on_actionDelete_delete_triggered();
    void on_actionVertex_triggered();
    void on_actionEdge_num2_triggered();
    void on_actionConnect_Selected_F_triggered();
    void on_actionExtrude_E_triggered();
    void on_actionCombine_Selected_J_triggered();
    void on_btnEllipse_clicked();
    void on_btnLine_clicked();
    void on_btnTLine_clicked();
    void on_btnGrading_clicked();
    void on_btnSubdivide_clicked();
    void on_actionGrading_Settings_triggered();

private:
    Ui::MainWindow *_ui;
	CADScene* _scene;
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
};
#endif // MAINWINDOW_H
