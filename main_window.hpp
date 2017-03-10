#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QWidget>

class MainWindow : public QWidget {
    // Default construct a MainWindow
    MainWindow(QWidget * parent = nullptr);
    
    // Default construct a MainWidow, using filename as the script file to
    // attempt to preload
    MainWindow(std::string filename, QWidget * parent = nullptr);
};

#endif // MAIN_WINDOW_HPP
