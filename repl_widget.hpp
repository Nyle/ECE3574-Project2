#ifndef REPL_WIDGET_HPP
#define REPL_WIDGET_HPP

#include <QWidget>
class QLineEdit;
class QLabel;

class REPLWidget : public QWidget {
    Q_OBJECT
private:
    QLineEdit * text;
    QLabel * label;
public:
    // Default construct a REPLWidget
    REPLWidget(QWidget * parent = nullptr);
public slots:
    // Run the currently entered line
    void runLine();
signals:
    // A signal that sends the current edited text as a QString when the
    // return key is pressed.
    void lineEntered(QString);
};

#endif // REPL_WIDGET_HPP
