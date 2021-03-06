#ifndef MESSAGE_WIDGET_HPP
#define MESSAGE_WIDGET_HPP

#include <QWidget>
#include <QLineEdit>
class QString;
class QLabel;
class QPalette;

class MessageWidget : public QWidget {
    Q_OBJECT
private:
    QLineEdit * text;
    QLabel * label;
    QPalette defaultPalette, redPalette;
public:
    // Default construct a MessageWidget displaying no text
    MessageWidget(QWidget * parent = nullptr);
public slots:
    // a public slot accepting an informational message to display, clearing
    // any error formatting
    void info(QString message);
    
    // a public slot accepting an error message to display as selected text
    // highlighted with a red background.
    void error(QString message);
};

#endif // MESSAGE_WIDGET_HPP
