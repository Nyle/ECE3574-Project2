#include "canvas_widget.hpp"
#include <QVBoxLayout>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>

CanvasWidget::CanvasWidget(QWidget * parent) : QWidget(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(view);
    setLayout(layout);
}

void CanvasWidget::addGraphic(QGraphicsItem * item) {
    scene->addItem(item);
}
