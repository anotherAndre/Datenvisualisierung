#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>
#include <iostream>


int main(int argc, char *argv[])
{
    // We stick with the standard "main" program that QtCreator generates
    // upon creation of a new "Qt Widgets Application". It creates a single
    // main window into which we can embed the OpenGL display.
    std::cout << "entry in main \n";
    QApplication a(argc, argv);
    std::cout << "main 1 \n";
    // entry in das Programm
    MainWindow w;
    std::cout << "main 2\n";
    w.show();

    std::cout << "main 3\n";

    return a.exec();
}
