#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QWidget>
class MessageWidget;
class CanvasWidget;
class REPLWidget;
class QtInterpreter;

class MainWindow : public QWidget {
    Q_OBJECT
private:
    MessageWidget * message;
    CanvasWidget * canvas;
    REPLWidget * repl;
    QtInterpreter * interpreter;
public:
    // Default construct a MainWindow
    MainWindow(QWidget * parent = nullptr);
    
    // Default construct a MainWidow, using filename as the script file to
    // attempt to preload
    MainWindow(std::string filename, QWidget * parent = nullptr);
};

#endif // MAIN_WINDOW_HPP
