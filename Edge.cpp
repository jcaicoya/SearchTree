#include "Edge.h"

#include "Node.h"
#include <qmath.h>
#include <QPainter>


Edge::Edge(Node *fromNode, Node *toNode)
    : _fromNode(fromNode)
    , _toNode(toNode)
    , _fromPoint()
    , _toPoint()
    , _arrowSize(10)

{
    setAcceptedMouseButtons(0);
    adjust();
}


void Edge::setFromNode(Node *fromNode)
{
    _fromNode = fromNode;
    adjust();
}


void Edge::adjust()
{
    if (!_fromNode || !_toNode)
    {
        return;
    }

    QLineF line(mapFromItem(_fromNode, 0, 0), mapFromItem(_toNode, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.))
    {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        _fromPoint = line.p1() + edgeOffset;
        _toPoint = line.p2() - edgeOffset;
    }
    else
    {
        _fromPoint = _toPoint = line.p1();
    }
}


QRectF Edge::boundingRect() const
{
    if (!_fromNode || !_toNode)
    {
        return QRectF();
    }

    qreal penWidth = 1;
    qreal extra = (penWidth + _arrowSize) / 2.0;

    return QRectF(_fromPoint, QSizeF(_toPoint.x() - _fromPoint.x(),
                                      _toPoint.y() - _fromPoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}


void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!_fromNode || !_toNode)
    {
        return;
    }

    QLineF line(_fromPoint, _toPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
    {
        return;
    }

    // Draw the line itself
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    // Draw the arrows
    double angle = std::atan2(-line.dy(), line.dx());

    QPointF _fromNodeArrowP1 = _fromPoint + QPointF(sin(angle + M_PI / 3) * _arrowSize,
                                                  cos(angle + M_PI / 3) * _arrowSize);
    QPointF _fromNodeArrowP2 = _fromPoint + QPointF(sin(angle + M_PI - M_PI / 3) * _arrowSize,
                                                  cos(angle + M_PI - M_PI / 3) * _arrowSize);
    QPointF _toNodeArrowP1 = _toPoint + QPointF(sin(angle - M_PI / 3) * _arrowSize,
                                              cos(angle - M_PI / 3) * _arrowSize);
    QPointF _toNodeArrowP2 = _toPoint + QPointF(sin(angle - M_PI + M_PI / 3) * _arrowSize,
                                              cos(angle - M_PI + M_PI / 3) * _arrowSize);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p1() << _fromNodeArrowP1 << _fromNodeArrowP2);
    painter->drawPolygon(QPolygonF() << line.p2() << _toNodeArrowP1 << _toNodeArrowP2);
}
