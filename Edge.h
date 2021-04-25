#pragma once


#include <QGraphicsItem>

class Node;

//! [0]
class Edge : public QGraphicsItem
{
public:
    Edge(Node *sourceNode, Node *destNode);

    Node *getFromNode() const { return _fromNode; }
    Node *getToNode() const { return _toNode; }

    void setFromNode(Node *fromNode);

    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    Node *_fromNode;
    Node *_toNode;

    QPointF _fromPoint;
    QPointF _toPoint;
    qreal _arrowSize;
};
