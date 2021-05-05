#pragma once

#include "NodeItem.h"
#include "EdgeItem.h"

#include <QGraphicsView>
#include <QList>
#include <QString>
#include <QVector>


class NodeItem;
class EdgeItem;
class QGraphicsScene;


class SearchTreeView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit SearchTreeView(QWidget *parent = nullptr);

    void addNode(const QString &label);

    void removeNode(const QString &label);

    void itemMoved();

private:
    QGraphicsScene *_scene;
    QList<NodeItem *> _nodeList;
    QList<EdgeItem *> _edgeList;
    int _maximumDepth;
    QVector<QPoint> _nodePositions;

    void calculateNodePositions(int depth);
    static constexpr int powerOfTwo(int power);
};

