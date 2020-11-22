#include "frmconfirmcreation.h"
#include "ui_frmconfirmcreation.h"

FrmConfirmCreation::FrmConfirmCreation(CADScene* scene, QString nameA, float factorA, QString nameB, float factorB, QWidget *parent ) : _factorA(factorA), _factorB(factorB),
    QDialog(),
    _ui(new Ui::FrmConfirmCreation)
{
	_initFlag = false;
	this->setWindowTitle(QString("Adusting"));
	_scene = scene;
    _ui->setupUi(this);
	_ui->lblFactorA->setText(nameA);
	_ui->lblFactorB->setText(nameB);
	_ui->txtFactorA->setText(QString::number(factorA));
	_ui->txtFactorB->setText(QString::number(factorB));

	

	_initFlag = true;
}

FrmConfirmCreation::~FrmConfirmCreation()
{
    delete _ui;
}

float FrmConfirmCreation::GetFactorA()
{
	try
	{
		return _factorA;
	}
	catch (const std::exception&)
	{
		return 0.0f;
	}
}

float FrmConfirmCreation::GetFactorB()
{
	try
	{
		return _factorB;
	}
	catch (const std::exception&)
	{
		return 0.0f;
	}
	
}

void FrmConfirmCreation::on_txtFactorA_textChanged(const QString &arg1)
{
	if (_initFlag) {
		float factor;
		try
		{
			factor = arg1.toFloat();
		}
		catch (const std::exception&)
		{
			factor = 0;
		}
		_factorA = factor;
		_scene->ChangeFactor();
	}
}

void FrmConfirmCreation::on_txtFactorB_textChanged(const QString &arg1)
{
	if (_initFlag) {
		float factor;
		try
		{
			factor = arg1.toFloat();
		}
		catch (const std::exception&)
		{
			factor = 0;
		}
		_factorB = factor;
		_scene->ChangeFactor();
	}
}

void FrmConfirmCreation::on_btnOK_clicked()
{
	_scene->ConfirmAction(true);
}

void FrmConfirmCreation::on_btnCancel_clicked()
{
	_scene->ConfirmAction(false);
}
