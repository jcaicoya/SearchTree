#pragma once

#include <QString>
#include <QGraphicsItem>

class SearchTreeView;


class NodeItem : public QGraphicsItem
{
public:
    NodeItem(SearchTreeView *searchTreeView, const QString &label, NodeItem *parent = nullptr, NodeItem *leftChild = nullptr, NodeItem *rightChild = nullptr);

    NodeItem * getParent() const { return _parent; }
    NodeItem * getLeftChild() const { return _leftChild; }
    NodeItem * getRightChild() const { return _rightChild; }

    void setParent(NodeItem *parent) { _parent = parent; }
    void setLeftChild(NodeItem *leftChild) { _leftChild = leftChild; }
    void setRightChild(NodeItem *rightChild) { _rightChild = rightChild; }

    bool advancePosition();

    enum { Type = UserType + 1 };
    int type() const override { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    SearchTreeView *_searchTreeView;

    QString _label;
    NodeItem *_parent;
    NodeItem *_leftChild;
    NodeItem *_rightChild;

    QPointF _newPos;

    static constexpr int _height = 50;
    static constexpr int _width = _height;
    static constexpr int _x = -1 * _height / 2;
    static constexpr int _y = _x;
    static constexpr int _boundingRectAdjust = 2;
};

