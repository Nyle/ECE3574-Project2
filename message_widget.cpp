#include "message_widget.hpp"
#include <QString>
#include <QHBoxLayout>
#include <QLabel>

MessageWidget::MessageWidget(QWidget * parent) : QWidget(parent) {
    text = new QLineEdit();
    text->setReadOnly(true);
    defaultPalette = text->palette();
    redPalette = defaultPalette;
    redPalette.setColor(QPalette::Highlight, QColor(Qt::red));
    
    label = new QLabel("Message:");
    
    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(text);
    setLayout(layout);

}

void MessageWidget::info(QString message) {
    text->setText(message);
    text->deselect();
    text->setPalette(defaultPalette);
}
    
void MessageWidget::error(QString message) {
    text->setText(message);
    text->selectAll();
    text->setPalette(redPalette);

}
