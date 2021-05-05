#include "OperationWidget.h"

#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>


OperationWidget::OperationWidget(QWidget *parent) : QWidget(parent)
{
    QLabel *depthLabel = new QLabel(tr("Enter depth: "));

    QSpinBox *depthSpinBox = new QSpinBox;
    depthSpinBox->setRange(-1, 5);

    QHBoxLayout *grouplayout = new QHBoxLayout;
    grouplayout->addWidget(depthLabel);
    grouplayout->addWidget(depthSpinBox);

    QGroupBox *group = new QGroupBox(this);
    group->setLayout(grouplayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(group);

    setLayout(mainLayout);
}
