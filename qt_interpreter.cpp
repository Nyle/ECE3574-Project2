#include "qt_interpreter.hpp"
#include <QString>
#include <QGraphicsItem>
#include <string>
#include <sstream>
#include "interpreter_semantic_error.hpp"

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
        emit info(this->interpreter.eval().to_string().c_str());
        // TODO: Draw graphics items
    } catch (InterpreterSemanticError e) {
        emit error(e.what());
    }
}
