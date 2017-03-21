#include <cstdlib>
#include <QApplication>
#include "main_window.hpp"

int main(int argc, char ** argv) {
    QApplication app(argc, argv);
    MainWindow * mainWindow;
    if (argc == 2) {
        mainWindow = new MainWindow(argv[1]);
    } else {
        mainWindow = new MainWindow();
    }
    mainWindow->show();
    
    return app.exec();
};
