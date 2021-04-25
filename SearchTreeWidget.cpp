#include "SearchTreeWidget.h"

#include "OperationWidget.h"
#include "SearchTreeView.h"
#include <QLabel>
#include <QHBoxLayout>


SearchTreeWidget::SearchTreeWidget(QWidget *parent)
    : QWidget(parent)
    , _operationWidget(nullptr)
    , _searchTreeView(nullptr)
{
    _operationWidget = new OperationWidget;
    _searchTreeView = new SearchTreeView;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_operationWidget);
    layout->addWidget(_searchTreeView);

    setLayout(layout);
}
