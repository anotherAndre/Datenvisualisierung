#ifndef HORIZONTALCONTOURLINESRENDERER_H
#define HORIZONTALCONTOURLINESRENDERER_H

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>

#include "horizontalslicetocontourmapper.h"

class horizontalContourlinesRenderer
{
public:
    horizontalContourlinesRenderer();
    virtual ~horizontalContourlinesRenderer();

    // Draw the bounding box to the current OpenGL viewport.
    void drawContourLines(QMatrix4x4 mvpMatrix, int iz, int time);
    void setMapper(horizontalSliceToContourMapper *mapper);
private:
    void initOpenGLShaders();
    int initContourLines(int time, int iz);

    QVector<QVector3D> lines;
    horizontalSliceToContourMapper *hScliceMapper;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vertexBuffer;
    QOpenGLVertexArrayObject vertexArrayObject;
};

#endif // HORIZONTALCONTOURLINESRENDERER_H
