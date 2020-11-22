#include "cadpart.h"
#include "cadscene.h"
#include "frmconfirmsubdivide.h"
#include <QKeyEvent>
#include <QDebug>
#include <algorithm>
//////////////////////////
//public:
CADPart::CADPart(CADScene* scene){
	this->_origin = QPointF(0, 0);
	this->_originVertex = new Vertex();
	this->_originVertex->SetPostition(_origin);
    this->_scene = scene;
	_scene->addItem(_originVertex);
    this->SetEditMode(false);
    //this->SetActive(true);
    this->SetSelected(false);
    this->_isControlPressed = false;
	this->SetSelectMode(SMPart);
	this->_status = Idle;
	this->_moveSetting = Normal;
	this->_rotateSetting = SCenter;
	this->_gradingSetting = false;
}

CADPart::CADPart(CADScene * scene, PartType type) : CADPart(scene){
	//this->_origin = QPointF(0, 0);
	switch (type)
	{
	case Dot:
		this->AddVertex(QPointF(0, 0));
		break;
	case Poly:
		
		this->AddVertex(QPointF(-50, -50));
		this->AddVertex(QPointF(-50, 50));
		this->AddVertex(QPointF(50, 50));
		this->AddVertex(QPointF(50, -50));

		for (int i = 0; i < 3; i++) {
			this->AddEdge(this->_vertexes[i], this->_vertexes[i + 1]);
		}
		this->AddEdge(this->_vertexes[0], this->_vertexes[3]);
		break;
	case Line:
		this->AddVertex(QPointF(0, 0));
		this->AddVertex(QPointF(100, 0));
		this->AddEdge(this->_vertexes[0], this->_vertexes[1]);
		break;
	case Circle:
		double angle = 0;
		double r = 100;
		const double Val = 2 * 3.1415926;
		int vCount = 32;

		for (int i = 0; i < vCount; i++) {
			this->AddVertex(QPointF(cos(angle) * r, sin(angle) * r));
			angle += (Val / vCount);
		}
		for (int i = 0; i < vCount - 1; i++) {
			this->AddEdge(this->_vertexes[i], this->_vertexes[i + 1]);
		}
		this->AddEdge(this->_vertexes[0], this->_vertexes[vCount - 1]);

		break;
	}
}

CADPart::CADPart(CADScene * scene, PartType type, QPointF pos) : CADPart(scene, type) {
	this->MoveTo(pos);
	ConfirmAction(true);
}

CADPart::~CADPart(){
	for (auto v : this->_vertexes) {
		delete v;
	}
	for (auto e : this->_edges) {
		delete e;
	}
	delete _originVertex;
}

void CADPart::AddVertex(QPointF pos){
    auto v = new Vertex(pos, this);
	v->SetActive(_selectMode == SMVertex);
	v->SetRPos(pos - this->_origin);
    this->_vertexes.push_back(v);
	this->_scene->addItem(v);
}

void CADPart::AddVertex(Vertex *v){
	v->SetActive(_selectMode == SMVertex);
	this->_vertexes.push_back(v);
	this->_scene->addItem(v);
}

void CADPart::SetActive(bool val){
    this->_isActive = val;
}

bool CADPart::EditMode(){
	return this->_isEditMode;
}

bool CADPart::Active(){
    return this->_isActive;
}

void CADPart::SetEditMode(bool val){
	ClearSelected();
    this->_isEditMode = val;
    if(this->_isEditMode){
		this->SetSelectMode(SMVertex);
		for (auto e : _edges) {
			e->SetGradingVisible(_gradingSetting);
		}
    }
    else{
		this->SetSelectMode(SMPart);
		for (auto e : _edges) {
			e->SetGradingVisible(false);
		}
    }
}

SelectMode CADPart::GetSelectMode()
{
	return this->_selectMode;
}

void CADPart::SetSelectMode(SelectMode val){
	this->_selectMode = val;
	switch (_selectMode)
	{
	case SMVertex:
		for (auto v : this->_vertexes) {
			v->SetActive(true);
		}
		for (auto e : this->_edges) {
			e->SetActive(false);
		}
		break;
	case SMEdge:
		for (auto v : this->_vertexes) {
			v->SetActive(false);
		}
		for (auto e : this->_edges) {
			e->SetActive(true);
		}
		break;
	case SMPart:
		for (auto v : this->_vertexes) {
			v->SetActive(false);
		}
		for (auto e : this->_edges) {
			e->SetActive(false);
		}
		break;
	default:
		break;
	}
}

bool CADPart::Selected(){
	return this->_isSelected;
}

void CADPart::SetSelected(bool val){
    this->_isSelected = val;
	_originVertex->SetSelected(val);
    for(auto v : this->_vertexes){
        v->SetSelected(val);
    }
    for(auto e : this->_edges){
        e->SetSelected(val);
    }
}

void CADPart::ProcessMouseEventV(Vertex* sender, QGraphicsSceneMouseEvent* event){
    if(this->_isEditMode && this->_selectMode == SMVertex && _status == Idle){
		if (_isControlPressed) {
			if (!SelectVertex(sender)) {
				UnSelectVertex(sender);
			}
		}
		else {
			bool temp = sender->Selected();
			ClearSelected();
			if (temp) {
				UnSelectVertex(sender);
			}
			else {
				SelectVertex(sender);
			}
		}
    }
	else if (this->_isEditMode && _status == Grading) {
		if (event->button() == Qt::MouseButton::LeftButton) {
			sender->SetGradingSetting(!sender->GradingSetting());
			this->Update();
		}
		else {
			MousePressEvent(event);
		}
	}
	else if (this->_isEditMode && _status != Idle) {
		MousePressEvent(event);
	}
    else if (!this->_isEditMode) {
		this->_scene->ProcessMouseEventP(this, event);
    }
}

void CADPart::ProcessMouseEventE(Edge * sender, QGraphicsSceneMouseEvent * event){
	if (this->_isEditMode && this->_selectMode == SMEdge && _status == Idle) {
		if (_isControlPressed) {
			if (!SelectEdge(sender)) {
				UnSelectEdge(sender);
			}
		}
		else {
			bool temp = sender->Selected();
			ClearSelected();
			if (temp) {
				UnSelectEdge(sender);
			}
			else {
				SelectEdge(sender);
			}
		}
	}
	else if (this->_isEditMode && _status == Subdivide) {
		ClearSelected();
		auto v1 = sender->V1();
		auto v2 = sender->V2();
		DeleteEdgeOnly(sender);
		_actionVertex = new Vertex(v2->pos(), this);
		
		this->AddVertex(_actionVertex);
		this->AddEdge(_actionVertex, v1);
		this->AddEdge(_actionVertex, v2);
		SetSelectMode(SMVertex);
		SelectVertex(_actionVertex);
		_actionOrigin = v1->pos();
		float length = GetLength(v1->pos() - v2->pos());
		float len = GetLength(v1->pos() - event->pos());
		float factorA = len / length;
		_actionVertex->Scale(_actionOrigin, factorA, factorA);
		
		_dialog = new FrmConfirmSubdivide(this, factorA, NULL);
		_dialog->show();
		this->_scene->ChangeCursor();
	}
	else if (this->_isEditMode) {
		MousePressEvent(event);
	}
	else if(!this->_isEditMode) {
		this->_scene->ProcessMouseEventP(this, event);
	}
}

void CADPart::KeyPressEvent(QKeyEvent *event){
	if (_isEditMode) {
		switch (this->_status)
		{
		case Idle:
			switch (event->key()) {
			case Qt::Key_Tab:
				this->SetEditMode(false);
				this->SetSelected(true);
				this->_scene->SetEditMode(false);
				break;
			case Qt::Key_Control:
				this->_isControlPressed = true;
				break;
			case Qt::Key_F:
				if (this->_selectedVertexes.size() > 1 && _selectMode == SMVertex) {
					for (int i = 0; i < this->_selectedVertexes.size() - 1; i++) {
						this->AddEdge(_selectedVertexes[i], _selectedVertexes[i + 1]);
					}
				}
				break;
			case Qt::Key_1:
				this->SetSelectMode(SMVertex);
				break;
			case Qt::Key_2:
				this->SetSelectMode(SMEdge);
				break;
			case Qt::Key_G:
				StartMoving();
				break;
			case Qt::Key_R:
				if (_selectedVertexes.size() > 1) {
					StartRotating();
				}
				break;
			case Qt::Key_S:
				if (_selectedVertexes.size() > 1) {
					StartScaling();
				}
				break;
			case Qt::Key_E:
				StartExtruding();
				break;
			case Qt::Key_Delete:
				DeleteSelected();
				break;
			case Qt::Key_A:
				for (auto v : _vertexes) {
					SelectVertex(v);
				}
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

void CADPart::KeyReleaseEvent(QKeyEvent *event){
	if (_isEditMode) {
		switch (event->key()) {
		case Qt::Key_Control:
			this->_isControlPressed = false;
			break;
		default:
			break;
		}
	}
}

void CADPart::MousePressEvent(QGraphicsSceneMouseEvent *event){
	if (!_isControlPressed && _status == Idle) {
		ClearSelected();
	}
	else if (_status == Grading) {
		if (event->button() == Qt::MouseButton::RightButton) {
			this->_scene->ChangeCursor();
			for (auto e : _edges) {
				e->SetGradingVisible(_gradingSetting);
				this->_status = Idle;
			}
		}
	}
	else if (_status != Idle) {
		if (event->button() == Qt::MouseButton::LeftButton) {
			ConfirmMove(true);
		}
		else if (event->button() == Qt::MouseButton::RightButton) {
			ConfirmMove(false);
		}
	}
}

void CADPart::MouseMoveEvent(QGraphicsSceneHoverEvent *event){
	switch (_status)
	{
	case Moving:
		if (!_moveFlag) {
			_mousePos = event->pos();
			_moveFlag = true;
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
			for (auto v : _selectedVertexes) {
				v->Move(dpos);
			}
		}
		break;
	case Rotating:
		if (!_moveFlag) {
			_mousePos = event->pos();
			_moveFlag = true;
			switch (_rotateSetting)
			{
			case Origin:
				_actionOrigin = QPointF(0, 0);
				break;
			case Center:
				_actionOrigin = this->_origin;
				break;
			case SCenter:
				CalculateSO();
				_actionOrigin = this->_selectOrigin;
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
			for (auto v : _selectedVertexes) {
				v->Rotate(_actionOrigin, dgree);
			}
		}
		break;
	case Scaling:
		if (!_moveFlag) {
			_mousePos = event->pos();
			_moveFlag = true;
			switch (_rotateSetting)
			{
			case Origin:
				_actionOrigin = QPointF(0, 0);
				break;
			case Center:
				_actionOrigin = this->_origin;
				break;
			case SCenter:
				CalculateSO();
				_actionOrigin = this->_selectOrigin;
				break;
			default:
				break;
			}
		}
		else {
			double len0 = GetLength(_mousePos - _actionOrigin);
			double len1 = GetLength(event->pos() - _actionOrigin);
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
			for (auto v : this->_selectedVertexes) {
				v->Scale(_actionOrigin, factorX, factorY);
			}
		}
		break;
	default:
		break;
	}
}

bool CADPart::SelectEdge(Edge *e) {
	auto iter = find(this->_selectedEdges.begin(), this->_selectedEdges.end(), e);
	if (iter == _selectedEdges.end()) {
		e->SetSelected(true);
		this->_selectedEdges.push_back(e);
		SelectVertexEdgeOnly(e->V1());
		SelectVertexEdgeOnly(e->V2());
		return true;
	}
	else {
		return false;
	}
}

void CADPart::UnSelectEdgeOnly(Edge *e){
	e->SetSelected(false);
	auto iter = find(this->_selectedEdges.begin(), this->_selectedEdges.end(), e);
	if (iter != _selectedEdges.end()) {
		_selectedEdges.erase(iter);
	}
}

MoveSetting CADPart::GetMoveSetting()
{
	return this->_moveSetting;
}

void CADPart::SetMoveSetting(MoveSetting val)
{
	this->_moveSetting = val;
}

RotateSetting CADPart::GetRotateSetting()
{
	return this->_rotateSetting;
}

void CADPart::SetRotateSetting(RotateSetting val)
{
	this->_rotateSetting = val;
}

ScaleSetting CADPart::GetScaleSetting()
{
	return this->_scaleSetting;
}

void CADPart::SetScaleSetting(ScaleSetting val)
{
	this->_scaleSetting = val;
}

QPointF CADPart::GetOrigin()
{
	return _origin;
}

void CADPart::Move(QPointF dpos){
	this->_origin = _backupOrigin + dpos;
	this->_originVertex->SetPostition(_origin);
	for (auto v : _vertexes) {
		v->Move(dpos);
	}
}

void CADPart::MoveTo(QPointF pos){
	this->_origin = pos;
	this->_originVertex->SetPostition(_origin);
	for (auto v : _vertexes) {
		v->MoveTo(v->GetRPos() + pos);
	}
}

void CADPart::Rotate(QPointF origin, float angle){
	for (auto v : _vertexes) {
		v->Rotate(origin, angle);
	}
	int x = origin.x() + (_origin.x() - origin.x()) * cosf(angle) - (_origin.y() - origin.y()) * sinf(angle);
	int y = origin.y() + (_origin.x() - origin.x()) * sinf(angle) + (_origin.y() - origin.y()) * cosf(angle);
	this->_origin = QPointF(x, y);
}

void CADPart::Scale(QPointF origin, float factorX, float factorY){
	for (auto v : _vertexes) {
		v->Scale(origin, factorX, factorY);
	}
	int x = origin.x() + factorX * (this->_origin.x() - origin.x());
	int y = origin.y() + factorY * (this->_origin.y() - origin.y());
	this->_origin = QPointF(x, y);
}

void CADPart::RotateAndScale(QPointF origin, float angle, float scaleFactor){
	int x = origin.x() + (_origin.x() - origin.x()) * cosf(angle) - (_origin.y() - origin.y()) * sinf(angle);
	int y = origin.y() + (_origin.x() - origin.x()) * sinf(angle) + (_origin.y() - origin.y()) * cosf(angle);
	this->_origin = QPointF(x, y);
	this->_origin = origin + scaleFactor * (this->_origin - origin);

	for (auto v : _vertexes) {
		v->RotateAndScale(origin, angle, scaleFactor);
	}
}

void CADPart::BackUpPosition(){
	_backupOrigin = this->_origin;
}

void CADPart::ConfirmAction(bool val){
	if (_status == Subdivide) {
		delete _dialog;
		this->_status = Idle;
		if (val) {
			_actionVertex->ConfirmMove(true);
		}
		else {
			_actionVertex->Scale(_actionOrigin, 0.5, 0.5);
			_actionVertex->ConfirmMove(true);
		}
	}
	else {
		if (val) {
			for (auto v : _vertexes) {
				v->ConfirmMove(true);
			}
		}
		else {
			this->_origin = _backupOrigin;
			this->_originVertex->SetPostition(_origin);
			for (auto v : _vertexes) {
				v->ConfirmMove(false);
			}
		}
	}
}

void CADPart::DeleteAll(){
	this->_status = Deleted;
	for (auto v : _vertexes) {
		_scene->removeItem(v);
	}
	for (auto e : _edges) {
		_scene->removeItem(e);
	}
	_scene->removeItem(_originVertex);
}

void CADPart::CombineWithPart(CADPart *part){
	for (auto v : part->_vertexes) {
		this->_vertexes.push_back(v);
		v->SetPart(this);
	}
	for (auto e : part->_edges) {
		this->_edges.push_back(e);
		e->SetPart(this);
	}
	part->_vertexes.clear();
	part->_edges.clear();
}

void CADPart::StartSubdivide(){
	if (_isEditMode && _selectMode == SMEdge && _status == Idle) {
		this->_scene->ChangeCursor();
		this->_status = Subdivide;
	}
}

void CADPart::UpdateVal(float val)
{
	_actionVertex->Scale(_actionOrigin, val, val);
}

CADScene * CADPart::GetScene()
{
	return this->_scene;
}

void CADPart::StartGrading()
{
	if (_isEditMode && _status == Idle && _selectMode == SMVertex) {
		this->_scene->ChangeCursor();
		for (auto e : _edges) {
			e->SetGradingVisible(true);
		}
		this->_status = Grading;
	}
}

void CADPart::SetGradingSetting(bool val)
{
	this->_gradingSetting = val;
	for (auto e : _edges) {
		e->SetGradingVisible(val);
	}
}

bool CADPart::GradingSetting()
{
	return this->_gradingSetting;
}

double CADPart::GetLength(QPointF point)
{
	return sqrt(point.x() * point.x() + point.y() * point.y());
}

/////////////////////////////////////////////
//private:

Edge* CADPart::AddEdge(Vertex* v1, Vertex* v2){
    if(!v1->IsConnectedTo(v2)){
        auto e = new Edge(v1, v2, this);
		e->SetActive(_selectMode == SMEdge);
		e->InitGrading();
		e->SetGradingVisible(this->_gradingSetting);
        this->_edges.push_back(e);
        this->_scene->addItem(e);
		return e;
    }
	return NULL;
}

void CADPart::ClearSelected(){
    for(auto v : this->_selectedVertexes){
        v->SetSelected(false);
    }
    for(auto e : this->_selectedEdges){
        e->SetSelected(false);
    }
    this->_selectedEdges.clear();
    this->_selectedVertexes.clear();
}

void CADPart::DeleteSelected(){
	switch (_selectMode)
	{
	case SMVertex:
		for (auto v : _selectedVertexes) {
			DeleteVertex(v);
		}
		break;
	case SMEdge:
		for (auto e : _selectedEdges) {
			DeleteEdge(e);
		}
		break;
	default:
		break;
	}
	ClearSelected();
}

void CADPart::DeleteVertex(Vertex *v){
	auto edges = v->GetEdges();
	for (auto e : *edges) {
		DeleteEdgeOnly(e);
	}

	this->_scene->removeItem(v);
	auto iter = find(this->_vertexes.begin(), this->_vertexes.end(), v);
	if (iter != _vertexes.end()) {
		this->_vertexes.erase(iter);
	}
	iter = find(this->_selectedVertexes.begin(), this->_selectedVertexes.end(), v);
	if (iter != _selectedVertexes.end()) {
		_selectedVertexes.erase(iter);
	}
	delete v;
}

void CADPart::DeleteEdge(Edge *e){
	e->V1()->DeleteEdge(e);
	e->V2()->DeleteEdge(e);

	if (!e->V1()->HasEdge()) {
		DeleteVertex(e->V1());
	}
	if (!e->V2()->HasEdge()) {
		DeleteVertex(e->V2());
	}

	this->_scene->removeItem(e);
	auto iter = find(this->_edges.begin(), this->_edges.end(), e);
	if (iter != _edges.end()) {
		this->_edges.erase(iter);
	}
	iter = find(this->_selectedEdges.begin(), this->_selectedEdges.end(), e);
	if (iter != _selectedEdges.end()) {
		this->_selectedEdges.erase(iter);
	}
	delete e;
}

void CADPart::DeleteEdgeOnly(Edge *e){
	e->V1()->DeleteEdge(e);
	e->V2()->DeleteEdge(e);
	this->_scene->removeItem(e);
	auto iter = find(this->_edges.begin(), this->_edges.end(), e);
	if (iter != _edges.end()) {
		this->_edges.erase(iter);
	}
	iter = find(this->_selectedEdges.begin(), this->_selectedEdges.end(), e);
	if (iter != _selectedEdges.end()) {
		this->_selectedEdges.erase(iter);
	}
	delete e;
}

bool CADPart::SelectVertex(Vertex *v){
	auto iter = find(this->_selectedVertexes.begin(), this->_selectedVertexes.end(), v);
	if (iter == _selectedVertexes.end()) {
		v->SetSelected(true);
		iter = find(this->_selectedVertexes.begin(), this->_selectedVertexes.end(), v);
		if (iter == _selectedVertexes.end()) {
			this->_selectedVertexes.push_back(v);
		}
		return true;
	}
	else {
		return false;
	}
}

void CADPart::SelectVertexEdgeOnly(Vertex *v)
{
	auto iter = find(this->_selectedVertexes.begin(), this->_selectedVertexes.end(), v);
	if (iter == _selectedVertexes.end()) {
		v->SetSelectedEdgeOnly(true);
		this->_selectedVertexes.push_back(v);
	}
}

void CADPart::UnSelectVertex(Vertex *v){
	v->SetSelected(false);
	auto iter = find(this->_selectedVertexes.begin(), this->_selectedVertexes.end(), v);
	if (iter != _selectedVertexes.end()) {
		_selectedVertexes.erase(iter);
	}
}

void CADPart::UnSelectEdge(Edge *e) {
	e->SetSelected(false);
	auto iter = find(this->_selectedEdges.begin(), this->_selectedEdges.end(), e);
	if (iter != _selectedEdges.end()) {
		_selectedEdges.erase(iter);
	}
	if (!e->V1()->HasEdgeSelected()) {
		UnSelectVertex(e->V1());
	}
	if (!e->V2()->HasEdgeSelected()) {
		UnSelectVertex(e->V2());
	}
}

void CADPart::StartMoving(){
	this->_status = Moving;
	this->_scene->SetMouseTracing(true);
	this->_moveFlag = false;
}

void CADPart::ConfirmMove(bool val){
	this->_status = Idle;
	this->_scene->SetMouseTracing(false);
	this->_moveSetting = Normal;
	this->_scaleSetting = SNormal;
	
	for (auto v : this->_selectedVertexes) {
		v->ConfirmMove(val);
	}
}

void CADPart::StartRotating(){
	this->_status = Rotating;
	this->_scene->SetMouseTracing(true);
	this->_moveFlag = false;
}

void CADPart::StartScaling(){
	this->_status = Scaling;
	this->_scene->SetMouseTracing(true);
	this->_moveFlag = false;
}

void CADPart::StartExtruding(){
	if (this->_selectedVertexes.size() > 0) {
		this->_scene->SetMouseTracing(true);
		if (_selectMode == SMVertex) {
			vector<Vertex*> containerV;
			for (auto v : _selectedVertexes) {
				auto ev = new Vertex(v->GetPosition(), this);
				this->AddVertex(ev);
				this->AddEdge(ev, v);
				containerV.push_back(ev);
			}
			ClearSelected();
			for (auto v : containerV) {
				SelectVertex(v);
			}
			StartMoving();
		}
	}
}

void CADPart::CalculateSO(){
	_selectOrigin = QPointF(0, 0);
	for (auto v : _selectedVertexes) {
		_selectOrigin += v->GetPosition();
	}
	_selectOrigin /= _selectedVertexes.size();
}

void CADPart::Update()
{
	for (auto e : _edges) {
		e->Update();
	}
}
