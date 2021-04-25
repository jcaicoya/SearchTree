#pragma once

#include <QGraphicsView>


class SearchTreeView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit SearchTreeView(QWidget *parent = nullptr);

    void itemMoved();
};

