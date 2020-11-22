#include "actionlistener.h"
#include "cadscene.h"

/////////////////////////////////////
//public:
ActionListener::ActionListener(CADScene* scene){
	this->_scene = scene;
	this->setRect(QRectF(-600, -360, 1280, 720));
	this->setPos(QPointF(0, 0));
	_scene->addItem(this);
}

ActionListener::~ActionListener()
{
}

/////////////////////////////////////
//private:
void ActionListener::mousePressEvent(QGraphicsSceneMouseEvent * event){
	this->_scene->MousePressEvent(event);
}

void ActionListener::hoverMoveEvent(QGraphicsSceneHoverEvent * event)
{
	this->_scene->MouseMoveEvent(event);
}
