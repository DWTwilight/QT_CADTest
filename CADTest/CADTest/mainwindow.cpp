#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vertex.h"
#include "edge.h"
#include "cadpart.h"
#include <QGraphicsScene>
#include <QDebug>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

	this->_scene = new CADScene(this, this->_ui->gpvView, Default);
}

MainWindow::~MainWindow()
{
    delete _ui;
	delete _scene;
}

void MainWindow::SetEditMode(bool val){
	if (val) {
		this->_ui->lblMode->setText("Edit Mode");
		this->_ui->lblMode->setStyleSheet("color:red;");
	}
	else {
		this->_ui->lblMode->setText("Object Mode");
		this->_ui->lblMode->setStyleSheet("color:black;");
	}
}

void MainWindow::keyPressEvent(QKeyEvent * event){
	this->_scene->KeyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent * event){
	this->_scene->KeyReleaseEvent(event);
}


void MainWindow::on_actionDefault_Scene_triggered()
{
	this->_scene->Reset(Default);
}

void MainWindow::on_actionEmpty_Scene_triggered()
{
	this->_scene->Reset(Empty);
}

void MainWindow::on_actionEnter_Exit_EditMode_Tab_triggered()
{
	auto keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Tab, Qt::KeyboardModifier::NoModifier, QString(), false, 1);
	keyPressEvent(keyEvent);
	delete(keyEvent);
}

void MainWindow::on_actionMove_G_triggered()
{
	auto keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_G, Qt::KeyboardModifier::NoModifier, QString(), false, 1);
	keyPressEvent(keyEvent);
	delete(keyEvent);
}

void MainWindow::on_actionRotate_R_triggered()
{
	auto keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_R, Qt::KeyboardModifier::NoModifier, QString(), false, 1);
	keyPressEvent(keyEvent);
	delete(keyEvent);
}

void MainWindow::on_actionScale_S_triggered()
{
	auto keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_S, Qt::KeyboardModifier::NoModifier, QString(), false, 1);
	keyPressEvent(keyEvent);
	delete(keyEvent);
}

void MainWindow::on_actionSelect_All_A_triggered()
{
	auto keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::KeyboardModifier::NoModifier, QString(), false, 1);
	keyPressEvent(keyEvent);
	delete(keyEvent);
}

void MainWindow::on_actionDelete_delete_triggered()
{
	auto keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Delete, Qt::KeyboardModifier::NoModifier, QString(), false, 1);
	keyPressEvent(keyEvent);
	delete(keyEvent);
}

void MainWindow::on_actionVertex_triggered()
{
	auto keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_1, Qt::KeyboardModifier::NoModifier, QString(), false, 1);
	keyPressEvent(keyEvent);
	delete(keyEvent);
}

void MainWindow::on_actionEdge_num2_triggered()
{
	auto keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_2, Qt::KeyboardModifier::NoModifier, QString(), false, 1);
	keyPressEvent(keyEvent);
	delete(keyEvent);
}

void MainWindow::on_actionConnect_Selected_F_triggered()
{
	auto keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_F, Qt::KeyboardModifier::NoModifier, QString(), false, 1);
	keyPressEvent(keyEvent);
	delete(keyEvent);
}

void MainWindow::on_actionExtrude_E_triggered()
{
	auto keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_E, Qt::KeyboardModifier::NoModifier, QString(), false, 1);
	keyPressEvent(keyEvent);
	delete(keyEvent);
}

void MainWindow::on_actionCombine_Selected_J_triggered()
{
	auto keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_J, Qt::KeyboardModifier::NoModifier, QString(), false, 1);
	keyPressEvent(keyEvent);
	delete(keyEvent);
}

void MainWindow::on_btnEllipse_clicked()
{
	this->_scene->StartAction(CreatEllipse);
}

void MainWindow::on_btnLine_clicked()
{
	this->_scene->StartAction(CreatLine);
}

void MainWindow::on_btnTLine_clicked()
{
	this->_scene->StartAction(CreatLine);
	this->_scene->SetTLineFlag(true);
}

void MainWindow::on_btnGrading_clicked()
{
	this->_scene->StartAction(Grading);
}

void MainWindow::on_btnSubdivide_clicked()
{
	this->_scene->StartAction(Subdivide);
}

void MainWindow::on_actionGrading_Settings_triggered()
{
	this->_scene->ChangeGradingSetting();
}
