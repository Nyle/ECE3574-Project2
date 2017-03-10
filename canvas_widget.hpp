#ifndef CANVAS_WIDGET_HPP
#define CANVAS_WIDGET_HPP

#include<QWidget>
class QGraphicsItem;

class CanvasWidget : public QWidget {
    // Default construct a CanvasWidget
    CanvasWidget(QWidget * parent = nullptr);
    
    // A public slot that accepts a signal in the form of a QGraphicsItem
    // pointer containing an object derived from QGraphicsItem to draw
    void addGraphic(QGraphicsItem * item);
};

#endif // CANVAS_WIDGET_HPP
