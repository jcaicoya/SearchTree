#pragma once

#include <QString>
#include <QGraphicsItem>

class SearchTreeView;
class Edge;


class Node : public QGraphicsItem
{
public:
    Node(SearchTreeView *searchTreeView, const QString &label, Node *parent = nullptr, Node *leftChild = nullptr, Node *rightChild = nullptr);

    Node * getParent() const { return _parent; }
    Node * getLeftChild() const { return _leftChild; }
    Node * getRightChild() const { return _rightChild; }

    void setParent(Node *parent) { _parent = parent; }
    void setLeftChild(Node *leftChild) { _leftChild = leftChild; }
    void setRightChild(Node *rightChild) { _rightChild = rightChild; }

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
    Node *_parent;
    Node *_leftChild;
    Node *_rightChild;
    Edge *_edge;

    QPointF _newPos;


    static constexpr int _height = 50;
    static constexpr int _width = _height;
    static constexpr int _x = -1 * _height / 2;
    static constexpr int _y = _x;
    static constexpr int _boundingRectAdjust = 2;
};

