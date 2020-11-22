#ifndef CADSCENE_H
#define CADSCENE_H

#include "vertex.h"
#include "cadpart.h"
#include <QObject>
#include <QGraphicsScene>
#include <vector>
using namespace std;
class MainWindow;
class ActionListener;
class FrmConfirmCreation;
enum SceneSetting {Default, Empty};

class CADScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CADScene(MainWindow*, QGraphicsView*);
	CADScene(MainWindow*, QGraphicsView*, SceneSetting);
	~CADScene();

	void ProcessMouseEventP(CADPart* sender, QGraphicsSceneMouseEvent* event);
	void KeyPressEvent(QKeyEvent*);
	void KeyReleaseEvent(QKeyEvent*);
	void AddPart(CADPart*);
	void SetMouseTracing(bool);
	void SetEditMode(bool);
	void MousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void MouseMoveEvent(QGraphicsSceneHoverEvent *mouseEvent);
	void Reset(SceneSetting);
	void StartAction(Status);
	void ChangeFactor();
	void ConfirmAction(bool);
	void SetTLineFlag(bool);
	void ChangeGradingSetting();
	void ChangeCursor();

signals:

public slots:

private:
	MainWindow* _mainWindow;
	QGraphicsView* _view;
	ActionListener* _actionListener;
    vector<CADPart*> _parts;
	vector<CADPart*> _selectedParts;
	CADPart* _editPart;
	bool _isEditMode;
	Status _status;
	MoveSetting _moveSetting;
	RotateSetting _rotateSetting;
	ScaleSetting _scaleSetting;
	bool _actionFlag;
	QPointF _mousePos;
	QPointF _actionOrigin;
	bool _isControlPressed;
	FrmConfirmCreation* _dialog;
	float _factorA;
	float _factorB;
	bool _tLineFlag;
	bool _cursorState;
	
	void ClearSelected();
	bool SelectPart(CADPart*);
	void UnSelectPart(CADPart*);
	void DeleteSelected();
	void DeletePart(CADPart*);
	void CombineSelected();
	QPointF CalculateSCenter();
};

#endif // CADSCENE_H
