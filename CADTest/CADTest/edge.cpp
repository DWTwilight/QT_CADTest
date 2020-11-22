#include "edge.h"
#include "cadpart.h"
#include "gradingpath.h"
#include "cadscene.h"
#include <QPen>
////////////////////////////////////////////////
//public:
Edge::Edge(Vertex *v1, Vertex *v2){
    this->_v1 = v1;
    this->_v2 = v2;
    _v1->AddEdge(this);
    _v2->AddEdge(this);
    this->Update();
    this->SetActive(false);
    this->SetSelected(false);
	this->setFocus();
}

Edge::Edge(Vertex* v1, Vertex* v2, CADPart* part) : Edge(v1, v2){
    this->_part = part;
}

Edge::~Edge()
{
	for (auto gp : _gradingPaths) {
		this->_part->GetScene()->removeItem(gp);
		delete gp;
	}
}

void Edge::Update(){
    this->setLine(_v1->GetPosition().x(), _v1->GetPosition().y(), _v2->GetPosition().x(), _v2->GetPosition().y());
	for (auto gp : _gradingPaths) {
		gp->Update();
	}
}

bool Edge::Selected(){
    return this->_isSelected;
}

void Edge::SetSelected(bool val){
    this->_isSelected = val;
    this->_isSelected ? this->SetColor(Qt::red) : this->SetColor(Qt::black);
}

bool Edge::Active(){
    return this->_isActive;
}

void Edge::SetActive(bool val){
    this->_isActive = val;
    this->setAcceptHoverEvents(_isActive);
}

bool Edge::Contains(Vertex* v){
    return (_v1 == v) || (_v2 == v);
}

Vertex * Edge::V1()
{
	return _v1;
}

Vertex * Edge::V2()
{
	return _v2;
}

void Edge::SetPart(CADPart *part)
{
	this->_part = part;
}

QPointF Edge::GetPartOrigin()
{
	return this->_part->GetOrigin();
}

void Edge::InitGrading()
{
	for (int i = 0; i < GradingFacotrs.size(); i++) {
		auto gp = new GradingPath(this, GradingColors[i], GradingFacotrs[i]);
		this->_gradingPaths.push_back(gp);
		this->_part->GetScene()->addItem(gp);
	}
	this->SetGradingVisible(false);
}

void Edge::SetGradingVisible(bool val)
{
	for (auto gp : _gradingPaths) {
		gp->SetVisible(val);
	}
}

////////////////////////////////////////////////
//private:
void Edge::SetColor(QColor color){
    QPen pen = this->pen();
    pen.setColor(color);
    pen.setWidth(3);
    this->setPen(pen);
}

void Edge::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    if(!_isSelected){
        this->SetColor(Qt::green);
    }
}

void Edge::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    if(!_isSelected){
        this->SetColor(Qt::black);
    }
}

void Edge::mousePressEvent(QGraphicsSceneMouseEvent *event){
	this->_part->ProcessMouseEventE(this, event);
}
