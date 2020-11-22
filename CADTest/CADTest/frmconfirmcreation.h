#ifndef FRMCONFIRMCREATION_H
#define FRMCONFIRMCREATION_H

#include <QDialog>
#include "cadscene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class FrmConfirmCreation;
}
QT_END_NAMESPACE

class FrmConfirmCreation : public QDialog
{
    Q_OBJECT

public:
    explicit FrmConfirmCreation(CADScene* scene, QString nameA, float factorA, QString nameB, float factorB, QWidget *parent = nullptr );
    ~FrmConfirmCreation();

	float GetFactorA();
	float GetFactorB();

private slots:
    void on_txtFactorA_textChanged(const QString &arg1);
    void on_txtFactorB_textChanged(const QString &arg1);
    void on_btnOK_clicked();
    void on_btnCancel_clicked();

private:
    Ui::FrmConfirmCreation *_ui;
	CADScene* _scene;
	float _factorA;
	float _factorB;
	bool _initFlag;
};

#endif // FRMCONFIRMCREATION_H
