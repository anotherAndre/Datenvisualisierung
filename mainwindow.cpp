#include "mainwindow.h"
#include "opengldisplaywidget.h"

#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // The main window contains only a single widget, the OpenGL viewport.
    // For the purpose of this exercise, we implement the entire visualization
    // pipeline in this OpenGL widget. This may not be the best system
    // architecture, but it makes things sufficently simple for us.

    std::cout << "mainwinfow init i guess\n";

    OpenGLDisplayWidget *openGLDisplay = new OpenGLDisplayWidget(this);

    // Request an OpenGL context format compatible with version 3.3.
    QSurfaceFormat format;

    format.setVersion(3, 3);

    format.setProfile(QSurfaceFormat::CoreProfile);

    // Please uncomment if you use MacOS (source: https://forum.qt.io/topic/75759/qopengl-on-mac-qcocoaglcontext-falling-back-to-unshared-context/3)
    //QSurfaceFormat::setDefaultFormat(format); // only on macOS

    openGLDisplay->setFormat(format);

    setCentralWidget(openGLDisplay);
    // Fenster Größte X, Y
    resize(900, 900);

    std::cout << "maindow out \n";
}


MainWindow::~MainWindow()
{
}
