#include <QApplication>
#include "../include/ballwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    BallWindow window;
    window.resize(800, 600);
    window.setWindowTitle("Moving Balls");
    window.show();
    
    return app.exec();
}