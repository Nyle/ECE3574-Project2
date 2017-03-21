#include "qt_interpreter.hpp"
#include <QString>
#include <QGraphicsItem>
#include <string>
#include <sstream>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include "qgraphics_arc_item.hpp"
#include "interpreter_semantic_error.hpp"
#include "expression.hpp"
#include <tuple>
#include <cmath>

// Radius for displaying points
const qreal RADIUS = 0.2;
QGraphicsEllipseItem * pointToGraphic(Point point) {
    return new QGraphicsEllipseItem(std::get<0>(point) - RADIUS,
                                    std::get<1>(point) - RADIUS,
                                    RADIUS, RADIUS);
}

QGraphicsLineItem * lineToGraphic(Line line) {
    return new QGraphicsLineItem(std::get<0>(line.p1), std::get<1>(line.p1),
                                 std::get<0>(line.p2), std::get<1>(line.p2));
}

QGraphicsArcItem * arcToGraphic(Arc arc) {
    qreal dx = std::get<0>(arc.start) - std::get<0>(arc.center);
    qreal dy = std::get<1>(arc.start) - std::get<1>(arc.center);
    qreal radius = sqrt(pow(dx, 2) + pow(dy, 2));
    QGraphicsArcItem * result = new QGraphicsArcItem();
    result->setRect(std::get<0>(arc.center) - radius,
                    std::get<1>(arc.center) - radius,
                    2 * radius, 2 * radius);
    // Angles are in 16ths of a degree
    result->setStartAngle((int) (atan2(-dy, dx) * 180 / atan2(0, -1) * 16));
    result->setSpanAngle((int) (arc.angle  * 180 / atan2(0, -1) * 16));
    return result;
}

QGraphicsItem * QtInterpreter::drawableToGraphic(Drawable drw) {
    QGraphicsItem * result = 0;
    switch (drw.type) {
    case POINT:
        return pointToGraphic(drw.point);
        break;
    case LINE:
        result = lineToGraphic(drw.line);
        break;
    case ARC:
        result = arcToGraphic(drw.arc);
        break;
    default:
        result = 0;
        // We should never reach here
    }
    return result;
}

QtInterpreter::QtInterpreter(QObject * parent) {
    interpreter = Interpreter();
}

void QtInterpreter::parseAndEvaluate(QString entry) {
    std::stringstream entrystream;
    entrystream << entry.toStdString();
    if (!interpreter.parse(entrystream)) {
        emit error(interpreter.getparsingerror().c_str());
        return;
    }
    try {
        emit info(interpreter.eval().to_string().c_str());
        std::vector<QGraphicsItem *> todraw;
        for (auto const &drw : interpreter.getToDraw()) {
            emit drawGraphic(drawableToGraphic(drw));
        }
    } catch (InterpreterSemanticError e) {
        emit error(e.what());
    }
}
