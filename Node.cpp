#include "Node.h"

#include "SearchTreeView.h"
#include "Edge.h"
#include <QStyleOptionGraphicsItem>
#include <QDebug>


Node::Node(SearchTreeView *searchTreeView, const QString &label, Node *parent, Node *leftChild, Node *rightChild)
    : _searchTreeView(searchTreeView)
    , _label(label)
    , _parent(parent)
    , _leftChild(leftChild)
    , _rightChild(rightChild)
    , _edge(nullptr)
    , _newPos()

{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);

    _edge = new Edge(parent, this);
}


bool Node::advancePosition()
{
    if (_newPos == pos())
        return false;

    setPos(_newPos);
    return true;
}


QRectF Node::boundingRect() const
{
    return QRectF(_x - _boundingRectAdjust, _y - _boundingRectAdjust, _width + _boundingRectAdjust, _height + _boundingRectAdjust);
}


QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(_x, _y, _width, _height);
    return path;
}


void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    // Bounding rect
    /*
    painter->setPen(QPen(Qt::black, 2));
    painter->drawRect(boundingRect());
    */

    /* Shadow
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);
    */

    /* Gradient background
        QRadialGradient gradient(-3, -3, 10);
        if (option->state & QStyle::State_Sunken) {
            gradient.setCenter(3, 3);
            gradient.setFocalPoint(3, 3);
            gradient.setColorAt(1, QColor(Qt::yellow).lighter(120));
            gradient.setColorAt(0, QColor(Qt::darkYellow).lighter(120));
        } else {
            gradient.setColorAt(0, Qt::yellow);
            gradient.setColorAt(1, Qt::darkYellow);
        }
    painter->setBrush(gradient);
    */

    // Circle
    painter->setBrush(Qt::red);
    painter->setPen(QPen(Qt::black, 2));
    painter->drawEllipse(_x, _y, _width, _height);


    // Text
    painter->setPen(QPen(Qt::white, 0));
    painter->setFont(QFont("Arial", 15, QFont::ExtraBold));
    auto labelBoundingRect = painter->fontMetrics().boundingRect(_label);
    auto currentBoundingRect = boundingRect();
    auto x = static_cast<int>(currentBoundingRect.x() + currentBoundingRect.width() / 2 - labelBoundingRect.width() / 2);
    auto y = static_cast<int>(currentBoundingRect.y() + currentBoundingRect.height() / 2 - labelBoundingRect.height() / 2);
    QRect labelRect { QPoint{x, y}, labelBoundingRect.size() };
    painter->drawText(labelRect, _label);

}


QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        _edge->adjust();
        _searchTreeView->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
