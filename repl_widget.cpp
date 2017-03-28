#include <QApplication>
#include "repl_widget.hpp"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QKeyEvent>

REPLWidget::REPLWidget(QWidget * parent) : QWidget(parent) {
    text = new QLineEdit();
    label = new QLabel("vtscript>");

    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(text);
    setLayout(layout);

    QEventLoop::connect(text, SIGNAL(returnPressed()), this, SLOT(runLine()));
    QEventLoop::connect(text, SIGNAL(returnPressed()), text, SLOT(clear()));

    text->installEventFilter(this);
}

bool REPLWidget::eventFilter(QObject* obj, QEvent *event) {
    if (obj == text && event->type() == QEvent::KeyPress) {
        QKeyEvent * keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Up && history_position != 0) {
            history_position -= 1;
            text->setText(history[history_position]);
        } else if (keyEvent->key() == Qt::Key_Down &&
                   history_position != history.size()) {
            history_position += 1;
            text->setText(history_position != history.size() ?
                          history[history_position] : "");
        }
    }
    return QWidget::eventFilter(obj, event);
}

void REPLWidget::runLine() {
    history.push_back(text->text());
    history_position = history.size();
    emit lineEntered(text->text());
}
