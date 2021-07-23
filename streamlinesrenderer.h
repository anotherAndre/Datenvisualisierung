#ifndef STREAMLINESRENDERER_H
#define STREAMLINESRENDERER_H


#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>

#include "streamlinesmapper.h"

class StreamLinesRenderer
{
public:
    StreamLinesRenderer();
    virtual ~StreamLinesRenderer();

    // Draw the bounding box to the current OpenGL viewport.
    void drawStreamLines(QMatrix4x4 mvpMatrix, int time);
    void setMapper(StreamLinesMapper *mapper);
private:
    void initOpenGLShaders();
    int initStreamLines(int time);

    QVector<QVector3D> lines;
    StreamLinesMapper *streamLinesMapper;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vertexBuffer;
    QOpenGLVertexArrayObject vertexArrayObject;
};

#endif // STREAMLINESRENDERER_H


