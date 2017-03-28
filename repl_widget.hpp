#ifndef REPL_WIDGET_HPP
#define REPL_WIDGET_HPP

#include <QWidget>
#include <vector>
class QLineEdit;
class QLabel;
class QKeyEvent;

class REPLWidget : public QWidget {
    Q_OBJECT
private:
    QLineEdit * text;
    QLabel * label;
    std::vector<QString> history;
    size_t history_position;
public:
    // Default construct a REPL Widget
    REPLWidget(QWidget * parent = nullptr);

    // Catch key press event
    bool eventFilter(QObject* obj, QEvent *event);
public slots:
    // Run the currently entered line
    void runLine();
signals:
    // A signal that sends the current edited text as a QString when the
    // return key is pressed.
    void lineEntered(QString);
};

#endif // REPL_WIDGET_HPP
