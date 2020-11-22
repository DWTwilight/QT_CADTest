#ifndef FRMCONFIRMSUBDIVIDE_H
#define FRMCONFIRMSUBDIVIDE_H

#include <QDialog>
#include "cadpart.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class FrmConfirmSubdivide;
}
QT_END_NAMESPACE

class FrmConfirmSubdivide : public QDialog
{
    Q_OBJECT

public:
    explicit FrmConfirmSubdivide(CADPart* part, float val, QWidget *parent = nullptr);
    ~FrmConfirmSubdivide();
	float GetVal();

private slots:
    void on_txtVal_textChanged(const QString &arg1);
    void on_btnOK_clicked();
    void on_btnCancel_clicked();

private:
    Ui::FrmConfirmSubdivide *_ui;
	CADPart* _part;
	float _val;
	bool _initFlag;
};

#endif // FRMCONFIRMSUBDIVIDE_H
