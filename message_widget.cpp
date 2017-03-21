#include "message_widget.hpp"
#include <QString>
#include <QHBoxLayout>
#include <QLabel>

MessageWidget::MessageWidget(QWidget * parent) : QWidget(parent) {
    text = new QLineEdit();
    text->setReadOnly(true);

    label = new QLabel("Message:");
    
    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(text);
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
    setStyleSheet("QLineEdit {"
                  "  color: red"
                  "}");
}
