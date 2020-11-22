#include "vertex.h"
#include "cadpart.h"
#include <QGraphicsItem>
#include <QPen>
#include <QDebug>
#include <algorithm>
Vertex::Vertex()
{
	this->setRect(QRect(-3, -3, 6, 6));
	this->SetActive(false);
	this->SetSelected(false);
	this->SetPostition(QPointF(0, 0));
	this->setVisible(true);
	this->setAcceptedMouseButtons(Qt::MouseButton::NoButton);
	this->_gradingSetting = false;
}
///////////////////////////////////////////////////
//public:
Vertex::Vertex(QPointF pos){
    this->setRect(QRect(-5, -5, 10, 10));
    this->SetActive(false);
    this->SetSelected(false);
    this->SetPostition(pos);
}

Vertex::Vertex(QPointF pos, CADPart* part) : Vertex(pos){
    this->_part  = part;
}

QPointF Vertex::GetPosition(){
    return this->pos();
}

void Vertex::SetPostition(QPointF pos){
    this->_position = pos;
    this->setPos(pos);
	for (auto e : _edges) {
		e->Update();
	}
}

void Vertex::SetRPos(QPointF val){
	this->_rPosition = val;
}

bool Vertex::Selected(){
    return this->_isSelected;
}

void Vertex::SetSelected(bool val){
    this->_isSelected = val;
	if (this->_isSelected) {
		this->SetColor(Qt::red);
		for (auto e : _edges) {
			if (e->V1()->Selected() && e->V2()->Selected()) {
				_part->SelectEdge(e);
			}
		}
	}
	else {
		this->SetColor(Qt::black);
		for (auto e : _edges) {
			if (e->Selected()) {
				_part->UnSelectEdgeOnly(e);
			}
		}
	}
}

void Vertex::SetSelectedEdgeOnly(bool val)
{
	this->_isSelected = val;
	if (this->_isSelected) {
		this->SetColor(Qt::red);
	}
	else {
		this->SetColor(Qt::black);
	}
}

void Vertex::AddEdge(Edge* edge){
    this->_edges.push_back(edge);
}

void Vertex::DelteEdge(Edge* e){
	auto iter = find(this->_edges.begin(), this->_edges.end(), e);
	this->_edges.erase(iter);
}

void Vertex::ClearEdge(){
	this->_edges.clear();
}

void Vertex::SetActive(bool val){
    this->_isActive = val;
    this->setAcceptHoverEvents(_isActive);
	this->setVisible(val);
}

bool Vertex::Active(){
    return this->_isActive;
}

bool Vertex::IsConnectedTo(Vertex* v){
    for(auto e : this->_edges){
        if(e->Contains(v)){
            return true;
        }
    }
    return false;
}

bool Vertex::HasEdgeSelected()
{
	for (auto e : this->_edges) {
		if (e->Selected())
			return true;
	}
	return false;
}

bool Vertex::HasEdge()
{
	return !(this->_edges.size() == 0);
}

void Vertex::DeleteEdge(Edge* e){
	auto iter = find(this->_edges.begin(), this->_edges.end(), e);
	if (iter != _edges.end()) {
		_edges.erase(iter);
	}
}

vector<Edge*>* Vertex::GetEdges()
{
	return &_edges;
}

void Vertex::Move(QPointF dpos){
	/*auto pos = this->pos();
	pos += dpos;
	this->setPos(pos);
	for (auto e : _edges) {
		e->Update();
	}*/
	this->MoveTo(_position + dpos);
}

void Vertex::MoveTo(QPointF pos){
	this->setPos(pos);
	for (auto e : _edges) {
		e->Update();
	}
}

void Vertex::Rotate(QPointF origin, float angle){
	int x = origin.x() + (_position.x() - origin.x()) * cosf(angle) - (_position.y() - origin.y()) * sinf(angle);
	int y = origin.y() + (_position.x() - origin.x()) * sinf(angle) + (_position.y() - origin.y()) * cosf(angle);
	this->MoveTo(QPointF(x, y));
}

void Vertex::Scale(QPointF origin, float scaleFactorX, float scaleFactorY){
	int x = origin.x() + scaleFactorX * (this->_position.x() - origin.x());
	int y = origin.y() + scaleFactorY * (this->_position.y() - origin.y());
	this->MoveTo(QPointF(x, y));
}

void Vertex::RotateAndScale(QPointF origin, float angle, float scaleFactor){
	int x = origin.x() + (_position.x() - origin.x()) * cosf(angle) - (_position.y() - origin.y()) * sinf(angle);
	int y = origin.y() + (_position.x() - origin.x()) * sinf(angle) + (_position.y() - origin.y()) * cosf(angle);
	x = origin.x() + scaleFactor * (x - origin.x());
	y = origin.y() + scaleFactor * (y - origin.y());
	this->MoveTo(QPointF(x, y));
}

void Vertex::ConfirmMove(bool val){
	if (val) {
		this->_position = pos();
		this->_rPosition = this->_position - _part->GetOrigin();
	}
	else {
		this->MoveTo(_position);
	}
}

QPointF Vertex::GetRPos()
{
	return this->_rPosition;
}

void Vertex::SetPart(CADPart *part)
{
	this->_part = part;
}
bool Vertex::GradingSetting()
{
	return this->_gradingSetting;
}
void Vertex::SetGradingSetting(bool val)
{
	this->_gradingSetting = val;
}
///////////////////////////////////////////////////
//private:
void Vertex::SetColor(QColor color){
    QPen pen = this->pen();
    pen.setColor(color);

    this->setPen(pen);
    this->setBrush(color);
}

void Vertex::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    if(!_isSelected){
        this->SetColor(Qt::green);
    }
}

void Vertex::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    if(!_isSelected){
        this->SetColor((Qt::black));
    }
}

void Vertex::mousePressEvent(QGraphicsSceneMouseEvent *event){
	this->_part->ProcessMouseEventV(this, event);
}
