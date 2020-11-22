#pragma once
#include <QGraphicsItem>
#include <cadscene.h>

class ActionListener : public QGraphicsRectItem
{
public:
	ActionListener(CADScene*);
	~ActionListener();

private:
	CADScene* _scene;
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
};