#include "MainWindow.h"

#include "SearchTreeWidget.h"
#include <QHBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    SearchTreeWidget *searchTreeWidget = new SearchTreeWidget;
    setCentralWidget(searchTreeWidget);
}
