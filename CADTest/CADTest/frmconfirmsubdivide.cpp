#include "frmconfirmsubdivide.h"
#include "ui_frmconfirmsubdivide.h"

FrmConfirmSubdivide::FrmConfirmSubdivide(CADPart* part, float val, QWidget *parent) :
    QDialog(),
    _ui(new Ui::FrmConfirmSubdivide)
{
	_initFlag = false;
    _ui->setupUi(this);
	this->_part = part;
	this->_ui->txtVal->setText(QString::number(val));
	_initFlag = true;
}

FrmConfirmSubdivide::~FrmConfirmSubdivide()
{
    delete _ui;
}

float FrmConfirmSubdivide::GetVal()
{
	return _val;
}

void FrmConfirmSubdivide::on_txtVal_textChanged(const QString &arg1)
{
	if (_initFlag) {
		try
		{
			_val = arg1.toFloat();
		}
		catch (const std::exception&)
		{
			_val = 0.5f;
		}
		if (_val < 0) {
			_val = 0;
			this->_ui->txtVal->setText(QString("0"));
		}
		else if (_val > 1) {
			_val = 1;
			this->_ui->txtVal->setText(QString("1"));
		}

		_part->UpdateVal(_val);
	}
}

void FrmConfirmSubdivide::on_btnOK_clicked()
{
	_part->ConfirmAction(true);
}

void FrmConfirmSubdivide::on_btnCancel_clicked()
{
	_part->ConfirmAction(false);
}
