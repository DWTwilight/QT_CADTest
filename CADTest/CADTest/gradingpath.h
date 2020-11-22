#pragma once
#include <QGraphicsItem>
#include "edge.h"

class GradingPath : public QGraphicsLineItem
{
public:
	GradingPath(Edge* edge, QColor color, float factor);
	~GradingPath();

	void Update();
	void SetVisible(bool);

private:
	Edge* _edge;
	float _factor;

	void SetColor(QColor color);
};

