#ifndef REPL_WIDGET_HPP
#define REPL_WIDGET_HPP

#include <QWidget>

class REPLWidget : public QWidget {
    // Default construct a REPLWidget
    REPLWidget(QWidget * parent = nullptr);
    
    // A signal that sends the current edited text as a QString when the
    // return key is pressed.
    void lineEntered(QString);
};

#endif // REPL_WIDGET_HPP
