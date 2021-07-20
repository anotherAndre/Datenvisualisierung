#include "opengldisplaywidget.h"
#include "flowdatasource.h"

#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <iostream>
#include "math.h"


OpenGLDisplayWidget::OpenGLDisplayWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      distanceToCamera(-8.0)
{
    std::cout << "init gopengldisplaywidget\n";
    setFocusPolicy(Qt::StrongFocus);
    iz = 0;
    time = 0;
}


OpenGLDisplayWidget::~OpenGLDisplayWidget()
{
    // Clean up visualization pipeline.
    delete bboxRenderer;
    // ....
    // TODO: delete other stuff
    // löschen vom minBboxRenderer
    //delete minBboxRenderer;
    //delete tornadoDataSource;
    //delete hSliceMapper;
    //delete hSliceRenderer;
}


QString OpenGLDisplayWidget::openGLString()
{
    QString profileStr;
    switch (format().profile())
    {
    case QSurfaceFormat::NoProfile:
        profileStr = "no profile";
        break;
    case QSurfaceFormat::CompatibilityProfile:
        profileStr = "compatibility profile";
        break;
    case QSurfaceFormat::CoreProfile:
        profileStr = "core profile";
        break;
    }

    return QString("%1.%2 (%3)").arg(format().majorVersion())
            .arg(format().minorVersion()).arg(profileStr);
}


void OpenGLDisplayWidget::initializeGL()
{
    // Query and display some information about the used OpenGL context.
    std::cout << "Initializing OpenGLDisplayWidget with OpenGL version "
              <<  openGLString().toStdString() << ".\n" << std::flush;

    // Set the backgound color of the OpenGL display
    // enable the depth buffer.
    std::cout << "enable depth test";
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0, 0, 0, 1);

    f->glEnable(GL_DEPTH_TEST);

    // Our own initialization of the visualization pipeline.
    initVisualizationPipeline();
}


void OpenGLDisplayWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio of the current viewport.
    float aspectRatio = float(w) / std::max(1, h);

    // Reset projection and set new perspective projection.
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(45.0, aspectRatio, 0.05, 25.0);

    // Update model-view-projection matrix with new projection.
    updateMVPMatrix();
}


void OpenGLDisplayWidget::paintGL()
{
    // Clear color and depth buffer.
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Call renderer modules.
    bboxRenderer->drawBoundingBox(mvpMatrix);
    // ....
    // cal mini BB renderer
    //minBboxRenderer->drawBoundingBox(mvpMatrix);
    //hSliceRenderer->drawBoundingBox(mvpMatrix);
    hSliceRenderer->drawImage(mvpMatrix, iz, time);

    hContourRenderer->drawContourLines(mvpMatrix, iz, time);
}


void OpenGLDisplayWidget::mousePressEvent(QMouseEvent *e)
{
    // Save the current position of the mouse pointer for subsequent use
    // in mouseMoveEvent().
    lastMousePosition = QVector2D(e->localPos());
}


void OpenGLDisplayWidget::mouseMoveEvent(QMouseEvent *e)
{
    // If the user holds the left mouse button while moving the mouse, update
    // the rotation angles that specify from which side the grid visualization
    // is viewed.
    if (e->buttons() & Qt::LeftButton)
    {
        // Vector that points from the last stored position of the mouse
        // pointer to the current position.
        QVector2D mousePosDifference = QVector2D(e->localPos()) - lastMousePosition;

        // Update rotation angles in x and y direction. The factor "10" is an
        // arbitrary scaling constant that controls the sensitivity of the
        // mouse.
        rotationAngles.setX(
                    fmod(rotationAngles.x() + mousePosDifference.x()/10.,
                         360.));
        rotationAngles.setY(
                    fmod(rotationAngles.y() + mousePosDifference.y()/10.,
                         360.));

        // Store current position of mouse pointer for next call to this method.
        lastMousePosition = QVector2D(e->localPos());

        // Update model-view-projection matrix with new rotation angles.
        updateMVPMatrix();

        // Redraw OpenGL.
        update();
    }
}


void OpenGLDisplayWidget::wheelEvent(QWheelEvent *e)
{
    // Update distance of the camera to the rendered visualization. The factor
    // "500" is arbitrary and controls that sensitivity of the mouse.
    distanceToCamera += e->delta() / 500.;

    // Update model-view-projection matrix with new distance to camera.
    updateMVPMatrix();

    // Redraw OpenGL.
    update();
}


void OpenGLDisplayWidget::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Up)
    {
        // Do stuff...
        iz++;
        if(iz > 15)
            iz = 15;
    }
    else if (e->key() == Qt::Key_Down)
    {
        // Do stuff...
        iz--;
        if(iz < 0)
            iz = 0;
    }
    // TODO zeit via rechts und links
    else if (e->key() == Qt::Key_Right)
    {
        // Do stuff...
        time++;
    }
    else if (e->key() == Qt::Key_Left)
    {
        // Do stuff...
        time--;
        if(time < 0)
            time = 0;
    }
    else
    {
        return;
    }

    // Redraw OpenGL.
    update();
}


void OpenGLDisplayWidget::updateMVPMatrix()
{
    // Calculate a simple model view transformation from rotation angles
    // and distance to camera.
    // NOTE: Read from bottom to top.

    QMatrix4x4 mvMatrix;
    mvMatrix.translate(0.0, 0.0, distanceToCamera);
    mvMatrix.rotate(rotationAngles.y(), QVector3D(1.0, 0.0, 0.0));
    mvMatrix.rotate(rotationAngles.x(), QVector3D(0.0, 1.0, 0.0));
    mvMatrix.translate(-1.0, -1.0, -1.0);
    mvMatrix.scale(2.0);

    mvpMatrix = projectionMatrix * mvMatrix;
}


// TODO
// hier wird unser zeugs implementiert
void OpenGLDisplayWidget::initVisualizationPipeline()
{
    // Initialize the visualization pipeline:

    // Initialize data source(s).
    // ....
    // initialisierung der FlowDataSource
    std::cout << "init flow in pipe\n";
    tornadoDataSource = new FlowDataSource();
    //tornadoDataSource->printValuesOfOrthogonalSlice(0);

    // Initialize mapper modules.
    // ....
    std::cout << "init mapper in pipe\n";
    hSliceMapper = new HorizontalSliceToImageMapper();
    hSliceMapper->setDataSource(tornadoDataSource);

    hContourMapper = new horizontalSliceToContourMapper();
    hContourMapper->setDataSource(tornadoDataSource);

    // Initialize rendering modules.
    std::cout << "init bb renderer in pipe\n";
    bboxRenderer = new DataVolumeBoundingBoxRenderer();
    // ....
    // initialisierung vom mini BB renderer
    //minBboxRenderer = new HorizontalSliceRenderer();
    std::cout << "init slice renderer in pipe";
    hSliceRenderer = new HorizontalSliceRenderer();
    // setze den Mapper im Horizontal Slince renderer
    std::cout << "set mapper of slice renderer in pipe\n";
    hSliceRenderer->setMapper(hSliceMapper);

    hContourRenderer = new horizontalContourlinesRenderer();
    hContourRenderer->setMapper(hContourMapper);
}
