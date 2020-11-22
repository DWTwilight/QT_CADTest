#include "cadscene.h"
#include "mainwindow.h"
#include "actionlistener.h"
#include "frmconfirmcreation.h"
#include <QGraphicsScene>
#include <QGraphicsView>
const float PI = 3.1415926f;

////////////////////////////////////////
//public:
CADScene::CADScene(MainWindow* mainWindow, QGraphicsView* view) : QGraphicsScene(){
	this->_mainWindow = mainWindow;
	this->_view = view;
	this->setSceneRect(view->viewport()->rect());
	view->setScene(this);
	this->_actionListener = new ActionListener(this);

	this->_isEditMode = false;
	this->_status = Idle;
	this->_moveSetting = Normal;
	this->_rotateSetting = SCenter;
	this->_isControlPressed = false;
	this->_tLineFlag = false;
	this->_cursorState = false;
}

CADScene::CADScene(MainWindow* mainWindow, QGraphicsView* view, SceneSetting setting) : CADScene(mainWindow, view) {
	switch (setting)
	{
	case Default:
		this->AddPart(new CADPart(this, Poly, QPointF(0, 0)));
		break;
	default:
		break;
	}
}

CADScene::~CADScene(){
	for (auto p : this->_parts) {
		delete p;
	}
	delete _actionListener;
}

void CADScene::ProcessMouseEventP(CADPart * sender, QGraphicsSceneMouseEvent *event){
	if (!_isEditMode) {
		if (_status == Idle) {
			if (_isControlPressed) {
				if (!SelectPart(sender)) {
					UnSelectPart(sender);
				}
			}
			else {
				bool temp = sender->Selected();
				ClearSelected();
				if (temp) {
					UnSelectPart(sender);
				}
				else {
					SelectPart(sender);
				}
			}
		}
		else {
			MousePressEvent(event);
		}
	}
}

void CADScene::KeyPressEvent(QKeyEvent* event){
	if (_isEditMode) {
		_editPart->KeyPressEvent(event);
	}
	else {
		switch (_status)
		{
		case Idle:
			switch (event->key()) {
			case Qt::Key_Tab:
				if (_selectedParts.size() > 0) {
					this->SetEditMode(true);
				}
				break;
			case Qt::Key_G:
				StartAction(Moving);
				break;
			case Qt::Key_R:
				StartAction(Rotating);
				break;
			case Qt::Key_S:
				StartAction(Scaling);
				break;
			case Qt::Key_Control:
				this->_isControlPressed = true;
				break;
			case Qt::Key_Delete:
				DeleteSelected();
				break;
			case Qt::Key_A:
				for (auto p : _parts) {
					SelectPart(p);
				}
				break;
			case Qt::Key_J:
				CombineSelected();
				break;
			default:
				break;
			}
			break;
		case Moving:
			switch (event->key())
			{
			case Qt::Key_X:
				_moveSetting = (_moveSetting == XOnly) ? Normal : XOnly;
				break;
			case Qt::Key_Y:
				_moveSetting = (_moveSetting == YOnly) ? Normal : YOnly;
				break;
			default:
				break;
			}
			break;
		case Rotating:
			break;
		case Scaling:
			switch (event->key())
			{
			case Qt::Key_X:
				_scaleSetting = (_scaleSetting == SXOnly) ? SNormal : SXOnly;
				break;
			case Qt::Key_Y:
				_scaleSetting = (_scaleSetting == SYOnly) ? SNormal : SYOnly;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void CADScene::KeyReleaseEvent(QKeyEvent* event){
	if (_isEditMode) {
		_editPart->KeyReleaseEvent(event);
	}
	else {
		switch (_status)
		{
		case Idle:
			switch (event->key())
			{
			case Qt::Key_Control:
				this->_isControlPressed = false;
				break;
			default:
				break;
			}
			break;
		case Moving:
			break;
		case Rotating:
			break;
		case Scaling:
			break;
		case Extruding:
			break;
		default:
			break;
		}
	}
}

void CADScene::AddPart(CADPart *part){
	this->_parts.push_back(part);
}

void CADScene::SetMouseTracing(bool val)
{
	this->_actionListener->setAcceptHoverEvents(val);
}

void CADScene::MouseMoveEvent(QGraphicsSceneHoverEvent * event){
	if (_isEditMode) {
		_editPart->MouseMoveEvent(event);
	}
	else {
		switch (_status)
		{
		case Moving:
			if (!_actionFlag) {
				_mousePos = event->pos();
				_actionFlag = true;
			}
			else {
				QPointF dpos = event->pos() - _mousePos;
				switch (_moveSetting)
				{
				case XOnly:
					dpos.setY(0);
					break;
				case YOnly:
					dpos.setX(0);
					break;
				default:
					break;
				}
				for (auto p : _selectedParts) {
					p->Move(dpos);
				}
			}
			break;
		case Rotating:
			if (!_actionFlag) {
				_mousePos = event->pos();
				_actionFlag = true;
				switch (_rotateSetting)
				{
				case Origin:
					_actionOrigin = QPointF(0, 0);
					break;
				case Center:
					_actionOrigin = QPointF(0, 0);
					break;
				case SCenter:
					_actionOrigin = CalculateSCenter();
					break;
				default:
					break;
				}
			}
			else {
				QPointF dpos = event->pos() - _mousePos;
				QPointF r = _mousePos - _actionOrigin;
				float dgree = dpos.x() * r.y() - dpos.y() * r.x();
				dgree /= -20000.0;
				for (auto p : _selectedParts) {
					p->Rotate(_actionOrigin, dgree);
				}
			}
			break;
		case Scaling:
			if (!_actionFlag) {
				_mousePos = event->pos();
				_actionFlag = true;
				switch (_rotateSetting)
				{
				case Origin:
					_actionOrigin = QPointF(0, 0);
					break;
				case Center:
					_actionOrigin = QPointF(0, 0);
					break;
				case SCenter:
					_actionOrigin = CalculateSCenter();
					break;
				default:
					break;
				}
			}
			else {
				double len0 = CADPart::GetLength(_mousePos - _actionOrigin);
				double len1 = CADPart::GetLength(event->pos() - _actionOrigin);
				float factorX = len1 / len0;
				float factorY = len1 / len0;
				switch (_scaleSetting)
				{
				case SXOnly:
					factorY = 1;
					break;
				case SYOnly:
					factorX = 1;
					break;
				default:
					break;
				}
				for (auto p : this->_selectedParts) {
					p->Scale(_actionOrigin, factorX, factorY);
				}
			}
			break;
		case CreatEllipse:
			if (!_actionFlag) {
				_mousePos = event->pos();
				_actionFlag = true;
			}
			else {
				float factorX = abs(event->pos().x() - _mousePos.x()) / 100.0;
				float factorY = abs(event->pos().y() - _mousePos.y()) / 100.0;
				for (auto p : this->_selectedParts) {
					p->Scale(_actionOrigin, factorX, factorY);
				}
			}
			break;
		case CreatLine:
			if (!_actionFlag) {
				_mousePos = event->pos();
				_actionFlag = true;
			}
			else {
				float scaleFactor = CADPart::GetLength(event->pos() - this->_actionOrigin) / 100.0;
				float angel = acosf(QPointF::dotProduct(event->pos() - this->_actionOrigin, QPointF(1, 0)) / CADPart::GetLength(event->pos() - this->_actionOrigin));
				if (event->pos().y() < _actionOrigin.y()) {
					angel = -angel;
				}

				if (_tLineFlag) {
					int count = (int)((angel + PI / 8) * 4 / PI);
					angel = count * PI / 4;
                    _factorB = -angel;
				}

				_selectedParts[0]->RotateAndScale(_actionOrigin, angel, scaleFactor);
			}
			break;
		default:
			break;
		}
	}
}

void CADScene::Reset(SceneSetting setting)
{
	if (!this->_isEditMode) {
		for (auto p : _parts) {
			p->DeleteAll();
			delete p;
		}
		_parts.clear();
		_selectedParts.clear();
		switch (setting)
		{
		case Default:
			this->AddPart(new CADPart(this, Poly));
			break;
		case Empty:
			break;
		default:
			break;
		}
	}
}

void CADScene::MousePressEvent(QGraphicsSceneMouseEvent * mouseEvent){
	if (_isEditMode) {
		_editPart->MousePressEvent(mouseEvent);
	}
	else {
		if (_status == Idle) {
			this->ClearSelected();
		}
		else if(_status == Moving || _status == Scaling || _status == Rotating){
			if (mouseEvent->button() == Qt::MouseButton::LeftButton) {
				ConfirmAction(true);
			}
			else if (mouseEvent->button() == Qt::MouseButton::RightButton) {
				ConfirmAction(false);
			}
		}
		else {
			if (_actionFlag) {
				if (mouseEvent->button() == Qt::MouseButton::LeftButton) {
					Status temp = _status;
					//ConfirmAction(true);
					
					float factorA;
					float factorB;
					switch (temp)
					{
					case CreatEllipse:
						factorA = abs(mouseEvent->pos().x() - _mousePos.x()) / 100;
						factorB = abs(mouseEvent->pos().y() - _mousePos.y()) / 100;
						this->_dialog = new FrmConfirmCreation(this, QString("Long Axis"), factorA, QString("Short Axis"), factorB, NULL);
						_dialog->show();
						this->ChangeCursor();
						this->_status = AdjustingCircle;
						_factorA = factorA;
						_factorB = factorB;
						break;
					case CreatLine:
						factorA = CADPart::GetLength(mouseEvent->pos() - _actionOrigin) / 100.0;
						factorB = acosf(QPointF::dotProduct(mouseEvent->pos() - this->_actionOrigin, QPointF(1, 0)) / CADPart::GetLength(mouseEvent->pos() - this->_actionOrigin));
						if (mouseEvent->pos().y() > _actionOrigin.y()) {
							factorB = -factorB;
						}
                        if(_tLineFlag){
                            this->_dialog = new FrmConfirmCreation(this, QString("Length"), factorA, QString("Angel"), _factorB * 180.0 / PI, NULL);
                        }
                        else{
                            this->_dialog = new FrmConfirmCreation(this, QString("Length"), factorA, QString("Angel"), factorB * 180.0 / PI, NULL);
                        }

						_dialog->show();
						this->ChangeCursor();
						this->_status = AdjustingLine;
						_factorA = factorA;
						_factorB = factorB;
						break;
					default:
						break;
					}
				}
				else if (mouseEvent->button() == Qt::MouseButton::RightButton) {
					this->ChangeCursor();
					ConfirmAction(false);
				}
			}
			else {
				_actionOrigin = mouseEvent->pos();
				CADPart* part;
				switch (_status)
				{
				case CreatEllipse:
					part = new CADPart(this, Circle, mouseEvent->pos());
					part->Scale(part->GetOrigin(), 0, 0);
					this->AddPart(part);
					this->SelectPart(part);
					break;
				case CreatLine:
					part = new CADPart(this, Line, mouseEvent->pos());
					part->Scale(part->GetOrigin(), 0, 0);
					this->AddPart(part);
					this->SelectPart(part);
					break;
				}
				this->SetMouseTracing(true);
			}
		}
	}
}

void CADScene::SetEditMode(bool val) {
	this->_isEditMode = val;
	this->_mainWindow->SetEditMode(val);
	if (_isEditMode) {
		_editPart = _selectedParts[0];
		this->ClearSelected();
		this->_selectedParts.push_back(_editPart);
		_editPart->SetEditMode(true);
	}
}

void CADScene::StartAction(Status action)
{
	if (action == Subdivide) {
		if(_isEditMode)
			_editPart->StartSubdivide();
	}
	else if (action == Grading) {
		if(_isEditMode)
			_editPart->StartGrading();
	}
	else if(!_isEditMode) {
		this->_status = action;
		this->_actionFlag = false;
		if (action == Scaling || action == Moving || action == Rotating) {
			if (this->_selectedParts.size() > 0) {
				this->SetMouseTracing(true);
				for (auto p : _selectedParts) {
					p->BackUpPosition();
				}
			}
		}
		else {
			this->ChangeCursor();
			ClearSelected();
		}
	}
}

void CADScene::ChangeFactor()
{
	float factorA = _dialog->GetFactorA();
	float factorB = _dialog->GetFactorB();
	switch (_status)
	{
	case AdjustingCircle:
		_selectedParts[0]->Scale(_actionOrigin, factorA, factorB);
		break;
	case AdjustingLine:
		_selectedParts[0]->RotateAndScale(_actionOrigin, -factorB * 3.1415926 / 180.0, factorA);
		break;
	default:
		break;
	}
}

void CADScene::ConfirmAction(bool val){
	if (_status == Moving || _status == Rotating || _status == Scaling) {
		for (auto p : _selectedParts) {
			p->ConfirmAction(val);
		}
	}
	else {
		if (val) {
			for (auto p : _selectedParts) {
				p->ConfirmAction(val);
			}
		}
		else {
			DeleteSelected();
		}

		if (_status == AdjustingCircle || _status == AdjustingLine) {
			delete this->_dialog;
		}
	}
	this->_status = Idle;
	this->_moveSetting = Normal;
	this->_scaleSetting = SNormal;
	this->SetMouseTracing(false);
	this->_tLineFlag = false;
}

void CADScene::SetTLineFlag(bool val)
{
	_tLineFlag = val;
}

void CADScene::ChangeGradingSetting()
{
	if (_isEditMode) {
		_editPart->SetGradingSetting(!_editPart->GradingSetting());
	}
}

void CADScene::ChangeCursor()
{
	_cursorState ? this->_view->setCursor(Qt::ArrowCursor) : this->_view->setCursor(Qt::CrossCursor);
	_cursorState = !_cursorState;
}

///////////////////////////////////////////////////////
//private:
void CADScene::ClearSelected(){
	for (auto p : this->_selectedParts) {
		p->SetSelected(false);
	}
	_selectedParts.clear();
}

bool CADScene::SelectPart(CADPart *p){
	auto iter = find(this->_selectedParts.begin(), this->_selectedParts.end(), p);
	if (iter == _selectedParts.end()) {
		p->SetSelected(true);
		this->_selectedParts.push_back(p);
		return true;
	}
	else {
		return false;
	}
}

void CADScene::UnSelectPart(CADPart *p){
	p->SetSelected(false);
	auto iter = find(this->_selectedParts.begin(), this->_selectedParts.end(), p);
	if (iter != _selectedParts.end()) {
		_selectedParts.erase(iter);
	}
}

void CADScene::DeleteSelected(){
	for (auto p : _selectedParts) {
		DeletePart(p);
	}
	_selectedParts.clear();
}

void CADScene::DeletePart(CADPart *p){
	p->DeleteAll();
	auto iter = find(this->_parts.begin(), this->_parts.end(), p);
	if (iter != _parts.end()) {
		_parts.erase(iter);
	}
	delete p;
}

void CADScene::CombineSelected(){
	auto res = _selectedParts[0];
	if (_selectedParts.size() > 1) {
		for (int i = 1; i < _selectedParts.size(); i++) {
			res->CombineWithPart(_selectedParts[i]);
			DeletePart(_selectedParts[i]);
		}

		this->_selectedParts.clear();
		SelectPart(res);
	}
}

QPointF CADScene::CalculateSCenter()
{
	QPointF res(0, 0);
	for (auto p : _selectedParts) {
		res += p->GetOrigin();
	}
	res /= _selectedParts.size();
	return res;
}
