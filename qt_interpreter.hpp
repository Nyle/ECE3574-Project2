#ifndef QT_INTERPRETER_HPP
#define QT_INTERPRETER_HPP

#include <QObject>
class QGraphicsItem;
class QString;

class QtInterpreter : public QObject {
    // Default construct an QtInterpreter with the default environment and an
    // empty AST
    QtInterpreter(QObject * parent = nullptr);

    // a signal emitting a graphic to be drawn as a pointer
    void drawGraphic(QGraphicsItem * item);

    // a signal emitting an informational message
    void info(QString message);

    // a signal emitting an error message
    void error(QString message);

    // a public slot that accepts and expression string and parses/evaluates it
    void parseAndEvaluate(QString entry);
};

#endif // QT_INTERPRETER_HPP
