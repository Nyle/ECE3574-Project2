#include "message_widget.hpp"
#include <QString>
#include <QHBoxLayout>

MessageWidget::MessageWidget(QWidget * parent) : QWidget(parent) {
    text = new QLineEdit(this);
    text->setReadOnly(false);
    
    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->addWidget(text);
    setStyleSheet("QLineEdit {"
                  "  color: red"
                  "}");
    setLayout(layout);
}

void MessageWidget::info(QString message) {
    text->setText(message);
    text->deselect();
    setStyleSheet("");
}
    
void MessageWidget::error(QString message) {
    text->setText(message);
    text->selectAll();
    setStyleSheet("color: red");
}
