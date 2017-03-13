#include "qgraphics_arc_item.hpp"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

void QGraphicsArcItem::paint(QPainter * painter,
                             const QStyleOptionGraphicsItem * option,
                             QWidget * widget) {
    painter->drawArc(rect(), startAngle(), spanAngle());
}


