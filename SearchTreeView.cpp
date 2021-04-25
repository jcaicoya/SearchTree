#include "SearchTreeView.h"

#include "Node.h"



SearchTreeView::SearchTreeView(QWidget *parent)
    : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-400, -400, 800, 800);
    setScene(scene);

    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    //setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //scale(qreal(0.8), qreal(0.8));
    setMinimumSize(800, 800);


    Node *node1 = new Node(this, "100");
    node1->setPos(0, 0);


    Node *node2 = new Node(this, "200");
    node2->setPos(0, 200);

    Node *node3 = new Node(this, "30");
    node3->setPos(200, 200);

    Node *node4 = new Node(this, "400");
    node4->setPos(300, 300);

    scene->addItem(node1);
    scene->addItem(node2);
    scene->addItem(node3);
    scene->addItem(node4);

}


void SearchTreeView::itemMoved()
{
    /*
    if (!_imerId)
    {
        _timerId = startTimer(1000 / 25);
    }
    */
}

