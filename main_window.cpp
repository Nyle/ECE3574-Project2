#include <QApplication>
#include <QVBoxLayout>
#include "main_window.hpp"
#include "message_widget.hpp"
#include "canvas_widget.hpp"
#include "repl_widget.hpp"
#include "qt_interpreter.hpp"

MainWindow::MainWindow(QWidget * parent) : QWidget(parent) {
    message = new MessageWidget();
    canvas = new CanvasWidget();
    repl = new REPLWidget();
    interpreter = new QtInterpreter();
    QEventLoop::connect(interpreter, SIGNAL(info(QString)),
                        message, SLOT(info(QString)));
    QEventLoop::connect(interpreter, SIGNAL(error(QString)),
                        message, SLOT(error(QString)));
    QEventLoop::connect(interpreter, SIGNAL(drawGraphic(QGraphicsItem *)),
                        canvas, SLOT(addGraphic(QGraphicsItem *)));
    QEventLoop::connect(repl, SIGNAL(lineEntered(QString)),
                        interpreter, SLOT(parseAndEvaluate(QString)));

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(message);
    layout->addWidget(canvas);
    layout->addWidget(repl);
    setLayout(layout);
}

MainWindow::MainWindow(std::string filename, QWidget * parent) :
    MainWindow(parent){
    
}
