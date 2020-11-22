#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"
#include <QGraphicsItem>
class GradingPath;
const vector<float> GradingFacotrs = { 0.6f, 1.5f };
const vector<QColor> GradingColors = { Qt::GlobalColor::blue, Qt::GlobalColor::yellow };

class Edge : public QGraphicsLineItem
{
public:
    Edge(Vertex*, Vertex*);
    Edge(Vertex*, Vertex*, CADPart*);
	~Edge();

    void Update();
    bool Selected();
    void SetSelected(bool);
    bool Active();
    void SetActive(bool);
    bool Contains(Vertex*);
	Vertex* V1();
	Vertex* V2();
	void SetPart(CADPart*);
	QPointF GetPartOrigin();
	void InitGrading();
	void SetGradingVisible(bool);

private:
    Vertex* _v1;
    Vertex* _v2;
    CADPart* _part;
    bool _isSelected;
    bool _isActive; //does it respond to hover events?
	vector<GradingPath*> _gradingPaths;

    void SetColor(QColor);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // EDGE_H
