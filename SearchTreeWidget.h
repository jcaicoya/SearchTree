#pragma once

#include <QWidget>

class OperationWidget;
class SearchTreeView;


class SearchTreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchTreeWidget(QWidget *parent = nullptr);

signals:

private:
    OperationWidget *_operationWidget;
    SearchTreeView *_searchTreeView;
};

