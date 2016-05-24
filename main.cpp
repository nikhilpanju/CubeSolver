#include "mainwindow.h"
#include "solver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication CubeSolverApp(argc, argv);
    MainWindow window;
    window.show();

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    return CubeSolverApp.exec();
}
