#pragma once


#include <QGraphicsItem>

class NodeItem;

//! [0]
class EdgeItem : public QGraphicsItem
{
public:
    EdgeItem(NodeItem *from, NodeItem *to);

    void setFromNode(NodeItem *fromNodeItem);
    void setToNode(NodeItem *fromNodeItem);
    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    NodeItem *_fromNodeItem;
    NodeItem *_toNodeItem;

    QPointF _fromPoint;
    QPointF _toPoint;
    qreal _arrowSize;
};
