#include "SearchTreeView.h"

#include "NodeItem.h"
#include "EdgeItem.h"


SearchTreeView::SearchTreeView(QWidget *parent)
    : QGraphicsView(parent)
    , _scene(nullptr)
    , _nodeList()
    , _edgeList()
    , _maximumDepth(0)
    , _nodePositions()
{
    _scene = new QGraphicsScene(this);
    _scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    _scene->setSceneRect(-400, -400, 800, 800);
    setScene(_scene);

    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    //setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //scale(qreal(0.8), qreal(0.8));
    setMinimumSize(800, 800);

    calculateNodePositions(3);

    NodeItem *phantomNode = new NodeItem(this, "");
    phantomNode->setPos(0, 0);

    _nodeList.append(phantomNode);

    addNode("A");
    addNode("B");
    addNode("C");


}


void SearchTreeView::addNode(const QString &label)
{
    /* TODO: search label
    if (_nodeList.contains(label))
    {
        return;
    }
    */

    NodeItem *node = new NodeItem(this, label);
    _nodeList.append(node);
    const int numberOfNodes = _nodeList.size();

    qreal xAxisPos = 0;
    qreal yAxisPos = 0;

    if (numberOfNodes > 2)
    {
        qreal xAxisSign = 1;
        if (numberOfNodes % 2 == 1)
        {
            xAxisSign = -1;
        }

        xAxisPos = xAxisSign * 100 * numberOfNodes / 2;
        yAxisPos = 100 * numberOfNodes / 2;
    }

    node->setPos(xAxisPos, yAxisPos);


   EdgeItem *edge = new EdgeItem(_nodeList.at(numberOfNodes - 2), _nodeList.at(numberOfNodes - 1));
   _edgeList.append(edge);

   _scene->addItem(node);
   _scene->addItem(edge);
}


void SearchTreeView::removeNode(const QString &label)
{
    // TODO
}



void SearchTreeView::itemMoved()
{
    /* TODO
    if (!_imerId)
    {
        _timerId = startTimer(1000 / 25);
    }
    */
}


void SearchTreeView::calculateNodePositions(int depth)
{
    if (depth <= _maximumDepth)
    {
        return;
    }

    if (depth <= 2)
    {
        depth = 3;
    }

    _maximumDepth = depth;

    QVector<int> levelInitalPositions;
    int currentInitalPosition = 0;
    levelInitalPositions.append(currentInitalPosition);
    for (int level = 1; level <= depth + 1; level++)
    {
        currentInitalPosition = 2 * currentInitalPosition + 1;
        levelInitalPositions.append(currentInitalPosition);
    }

    //const int numberOfNodes = 2 * currentInitalPosition + 1;
    QVector<QPoint> rightPositions(levelInitalPositions[depth]);

    const qreal xSeparation = 50;
    const qreal ySeparation = 50;
    qreal y = ySeparation * depth;

    for (int pos = levelInitalPositions[depth - 1]; pos < levelInitalPositions[depth]; pos++)
    {
        qreal x = xSeparation / 2 + xSeparation * (pos - levelInitalPositions[depth - 1]);
        rightPositions[pos].setX(x);
        rightPositions[pos].setY(y);
    }

    for (int level = depth - 2; level >= 0; level--)
    {
        y = ySeparation * level;
        for (int pos = levelInitalPositions[level]; pos < levelInitalPositions[level + 1]; pos ++)
        {
            qreal x = (rightPositions[2 * pos + 1].x() + rightPositions[2 * pos +2].x()) / 2;
            rightPositions[pos].setX(x);
            rightPositions[pos].setY(y);
        }
    }

    QVector<QPoint> leftPositions = rightPositions;
    for (auto &leftPosition : leftPositions)
    {
        leftPosition.setX(-1 * leftPosition.x());
    }

    _nodePositions.clear();
    _nodePositions.emplaceBack(0, 0);
    for (int level = 0; level <= depth - 1; level++)
    {
        int begin = levelInitalPositions[level];
        int end = levelInitalPositions[level+1];

        for (int pos = begin; pos < end; pos++)
        {
            _nodePositions.push_back(leftPositions[pos]);
        }

        for (int pos = begin; pos < end; pos++)
        {
            _nodePositions.push_back(rightPositions[pos]);
        }
    }

    qDebug() << _nodePositions;
}


constexpr int SearchTreeView::powerOfTwo(int power)
{
    if (0 == power)
    {
        return 1;
    }

    if (1 == power)
    {
        return 2;
    }

    int result = 2;
    for (int pot = 2; pot <= power; pot++)
    {
        result *= 2;
    }

    return result;
}
