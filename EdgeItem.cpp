#include "EdgeItem.h"

#include "NodeItem.h"
#include <qmath.h>
#include <QPainter>


EdgeItem::EdgeItem(NodeItem *fromNodeItem, NodeItem *toNodeItem)
    : _fromNodeItem(fromNodeItem)
    , _toNodeItem(toNodeItem)
    , _fromPoint()
    , _toPoint()
    , _arrowSize(10)

{
    setAcceptedMouseButtons(QFlags<Qt::MouseButton>(Qt::NoButton));
    adjust();
}


void EdgeItem::setFromNode(NodeItem *fromNodeItem)
{
    _fromNodeItem = fromNodeItem;
    adjust();
}


void EdgeItem::setToNode(NodeItem *fromNodeItem)
{
    _fromNodeItem = fromNodeItem;
    adjust();
}


void EdgeItem::adjust()
{
    if (!_fromNodeItem || !_toNodeItem)
    {
        return;
    }

    QLineF line(mapFromItem(_fromNodeItem, 0, 0), mapFromItem(_toNodeItem, 0, 0));
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


QRectF EdgeItem::boundingRect() const
{
    if (!_fromNodeItem || !_toNodeItem)
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


void EdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!_fromNodeItem || !_toNodeItem)
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
