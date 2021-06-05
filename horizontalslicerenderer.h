#ifndef HORIZONTALSLICERENDERER_H
#define HORIZONTALSLICERENDERER_H

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>

#include "horizontalslicetoimagemapper.h"


class HorizontalSliceRenderer
{
public:
    HorizontalSliceRenderer();
    virtual ~HorizontalSliceRenderer();

    // Draw the bounding box to the current OpenGL viewport.
    void drawBoundingBox(QMatrix4x4 mvpMatrix);
    void drawImage(QMatrix4x4 mvpMatrix);
    void setMapper(HorizontalSliceToImageMapper *mapper);

private:
    void initOpenGLShaders();
    void initBoundingBoxGeometry();
    void initHorizontalSlice(int time, int iz);

    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vertexBuffer;

    // Textrure Objekt variable stuff
    QOpenGLTexture texture;

    QOpenGLVertexArrayObject vertexArrayObject;

    HorizontalSliceToImageMapper *hScliceMapper;
};

#endif // HORIZONTALSLICERENDERER_H

