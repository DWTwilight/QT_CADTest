#ifndef CADPART_H
#define CADPART_H

#include "edge.h"
#include "vertex.h"
#include <vector>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <vector>
using namespace std;
class CADScene;
class FrmConfirmSubdivide;

enum PartType {Dot, Poly, Line, Circle};
enum SelectMode {SMVertex, SMEdge, SMPart};
enum Status {Idle, Moving, Rotating, Scaling, Extruding, Deleted, CreatEllipse, CreatLine, Grading, Subdivide, AdjustingCircle, AdjustingLine};
enum MoveSetting {Normal, XOnly, YOnly};
enum RotateSetting {Origin, Center, SCenter};
enum ScaleSetting {SNormal, SXOnly, SYOnly};

class CADPart
{
public:
    CADPart(CADScene *scene);
	CADPart(CADScene *scene, PartType type);
	CADPart(CADScene *scene, PartType type, QPointF pos);
	~CADPart();

    bool Selected();
    void SetSelected(bool);
    bool Active();
    void SetActive(bool);
    bool EditMode();
    void SetEditMode(bool);
	SelectMode GetSelectMode();
	void SetSelectMode(SelectMode);
    void AddVertex(QPointF);
	void AddVertex(Vertex*);
    void ProcessMouseEventV(Vertex* sender, QGraphicsSceneMouseEvent* event);
	void ProcessMouseEventE(Edge* sender, QGraphicsSceneMouseEvent* event);
	void KeyPressEvent(QKeyEvent*);
	void KeyReleaseEvent(QKeyEvent*);
	void MousePressEvent(QGraphicsSceneMouseEvent*);
	void MouseMoveEvent(QGraphicsSceneHoverEvent*);
	bool SelectEdge(Edge*);
	void UnSelectEdgeOnly(Edge*);
	MoveSetting GetMoveSetting();
	void SetMoveSetting(MoveSetting);
	RotateSetting GetRotateSetting();
	void SetRotateSetting(RotateSetting);
	ScaleSetting GetScaleSetting();
	void SetScaleSetting(ScaleSetting);
	QPointF GetOrigin();
	void Move(QPointF);
	void MoveTo(QPointF);
	void Rotate(QPointF, float);
	void Scale(QPointF, float, float);
	void RotateAndScale(QPointF, float, float);
	void BackUpPosition();
	void ConfirmAction(bool);
	void DeleteAll();
	void CombineWithPart(CADPart*);
	void StartSubdivide();
	void UpdateVal(float val);
	CADScene* GetScene();
	void StartGrading();
	void SetGradingSetting(bool);
	bool GradingSetting();

	static double GetLength(QPointF);

private:
    bool _isSelected;
    bool _isActive;
    bool _isEditMode;
    bool _isControlPressed;
	Status _status;
    CADScene* _scene;
    vector<Vertex*> _vertexes;
    vector<Edge*> _edges;
    vector<Vertex*> _selectedVertexes;
    vector<Edge*> _selectedEdges;
    QPointF _origin;
	QPointF _backupOrigin;
	QPointF _selectOrigin;
	QPointF _mousePos;
	QPointF _actionOrigin;
    float _rotation;
	SelectMode _selectMode;
	MoveSetting _moveSetting;
	RotateSetting _rotateSetting;
	ScaleSetting _scaleSetting;
	bool _moveFlag;
	Vertex* _originVertex;
	Vertex* _actionVertex;
	FrmConfirmSubdivide* _dialog;
	bool _gradingSetting;

    Edge* AddEdge(Vertex*, Vertex*);
    void ClearSelected();
	void DeleteSelected();
	void DeleteVertex(Vertex*);
	void DeleteEdge(Edge*);
	void DeleteEdgeOnly(Edge*);
	bool SelectVertex(Vertex*);
	void SelectVertexEdgeOnly(Vertex*);
	void UnSelectVertex(Vertex*);
	void UnSelectEdge(Edge*);
	void StartMoving();
	void ConfirmMove(bool);
	void StartRotating();
	void StartScaling();
	void StartExtruding();
	void CalculateSO();
	void Update();
};
#endif // CADPART_H
