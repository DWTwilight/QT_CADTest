#include "gradingpath.h"
#include <edge.h>
#include <QPen>

GradingPath::GradingPath(Edge * edge, QColor color, float factor)
{
	this->_edge = edge;
	this->SetColor(color);
	this->_factor = factor;
	this->Update();
}

GradingPath::~GradingPath()
{

}

void GradingPath::Update()
{
	QPointF origin = _edge->GetPartOrigin();
	QPointF pos1 = _edge->V1()->GradingSetting() ? origin + _factor * (_edge->V1()->pos() - origin) : _edge->V1()->pos();
	QPointF pos2 = _edge->V2()->GradingSetting() ? origin + _factor * (_edge->V2()->pos() - origin) : _edge->V2()->pos();
	this->setLine(pos1.x(), pos1.y(), pos2.x(), pos2.y());
}

void GradingPath::SetVisible(bool val)
{
	this->setVisible(val);
}

void GradingPath::SetColor(QColor color)
{
	QPen pen = this->pen();
	pen.setColor(color);
	pen.setWidth(3);
	this->setPen(pen);
}
