#ifndef VERTEX_H
#define VERTEX_H

#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <vector>
using namespace std;
class CADPart;
class Edge;

class Vertex : public QGraphicsEllipseItem
{
public:
	Vertex();
    Vertex(QPointF);
    Vertex(QPointF, CADPart*);

    QPointF GetPosition();
    void SetPostition(QPointF);
	void SetRPos(QPointF);
    bool Selected();
    void SetSelected(bool);
	void SetSelectedEdgeOnly(bool);
    void AddEdge(Edge*);
    void DelteEdge(Edge*);
    void ClearEdge();
    void SetActive(bool);
    bool Active();
    bool IsConnectedTo(Vertex*);
	bool HasEdgeSelected();
	bool HasEdge();
	void DeleteEdge(Edge*);
	vector<Edge*>* GetEdges();
	void Move(QPointF);
	void MoveTo(QPointF);
	void Rotate(QPointF, float);
	void Scale(QPointF, float, float);
	void RotateAndScale(QPointF, float, float);
	void ConfirmMove(bool);
	QPointF GetRPos();
	void SetPart(CADPart*);
	bool GradingSetting();
	void SetGradingSetting(bool);

private:
    QPointF _position;
	QPointF _rPosition;
	QPointF _backUpPos;
    bool _isSelected;
    bool _isActive;
	bool _gradingSetting;
    CADPart* _part;
    vector<Edge*> _edges;

    void SetColor(QColor color);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // VERTEX_H
