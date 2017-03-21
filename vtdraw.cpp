#include <cstdlib>
#include <QApplication>
#include "main_window.hpp"

int main(int argc, char ** argv) {
    QApplication app(argc, argv);

    MainWindow * mainWindow = new MainWindow();
    mainWindow->show();
    
    return app.exec();
};
