#ifndef Q_GRAPHICS_ARC_ITEM_HPP
#define Q_GRAPHICS_ARC_ITEM_HPP

#include <QGraphicsEllipseItem>
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;

class QGraphicsArcItem : public QGraphicsEllipseItem {
public:
    // Re-implements paint method to draw arc without lines from center to
    // ends
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget = 0);
};

#endif // Q_GRAPHICS_ARC_ITEM_HPP
