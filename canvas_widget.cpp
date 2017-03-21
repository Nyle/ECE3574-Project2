#include "canvas_widget.hpp"

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>

CanvasWidget::CanvasWidget(QWidget * parent) : QWidget(parent) {
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    view->show();
}

void CanvasWidget::addGraphic(QGraphicsItem * item) {
    scene->addItem(item);
}
