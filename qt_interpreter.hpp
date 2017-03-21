#ifndef QT_INTERPRETER_HPP
#define QT_INTERPRETER_HPP

#include <QObject>
#include "interpreter.hpp"
class QGraphicsItem;
class QString;
struct Drawable;

class QtInterpreter : public QObject {
    Q_OBJECT
private:
    Interpreter interpreter;
    // Convert a graphics type expression to a QGraphicsItem corresponding to
    // the item that that expression should draw
    QGraphicsItem * drawableToGraphic(Drawable drw);
public:
    // Default construct an QtInterpreter with the default environment and an
    // empty AST
    QtInterpreter(QObject * parent = nullptr);
signals:
    // a signal emitting a graphic to be drawn as a pointer
    void drawGraphic(QGraphicsItem * item);

    // a signal emitting an informational message
    void info(QString message);

    // a signal emitting an error message
    void error(QString message);
public slots:
    // a public slot that accepts and expression string and parses/evaluates it
    void parseAndEvaluate(QString entry);
};

#endif // QT_INTERPRETER_HPP
