#include <QApplication>
#include "repl_widget.hpp"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>

REPLWidget::REPLWidget(QWidget * parent) : QWidget(parent) {
    text = new QLineEdit();
    label = new QLabel("vtscript>");

    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(text);
    setLayout(layout);

    QEventLoop::connect(text, SIGNAL(returnPressed()), this, SLOT(runLine()));
    QEventLoop::connect(text, SIGNAL(returnPressed()), text, SLOT(clear()));
}

void REPLWidget::runLine() {
    emit lineEntered(text->text());
}
