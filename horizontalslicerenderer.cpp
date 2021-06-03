#include "horizontalslicerenderer.h"

#include <iostream>
#include <QOpenGLFunctions>
#include <QOpenGLContext>

#include "horizontalslicetoimagemapper.h";


HorizontalSliceRenderer::HorizontalSliceRenderer()
    : vertexBuffer(QOpenGLBuffer::VertexBuffer)
{
    initOpenGLShaders();
    initBoundingBoxGeometry();
}


HorizontalSliceRenderer::~HorizontalSliceRenderer()
{
    vertexBuffer.destroy();
}


// setter vom Mapper
void HorizontalSliceRenderer::setMapper(HorizontalSliceToImageMapper *mapper)
{
    hScliceMapper = mapper;
}


// Hier wird der Würfel gezeichnet
void HorizontalSliceRenderer::drawBoundingBox(QMatrix4x4 mvpMatrix)
{
    shaderProgram.link();
    // Tell OpenGL to use the shader program of this class.
    shaderProgram.bind();

    // Bind the vertex array object that links to the bounding box vertices.
    vertexArrayObject.bind();

    // Set the model-view-projection matrix as a uniform value.
    shaderProgram.setUniformValue("mvpMatrix", mvpMatrix);

    // Issue OpenGL draw commands.
    // Dies ist letzendlich für das Zeichnen mit OpenGL zuständig
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    // die Breite der Linien ist 2
    f->glLineWidth(2);
    // Es werden immer 2 aufeinander folgende Punkte als Linie gezeichnet?
    f->glDrawArrays(GL_LINE_STRIP, 0, 16);

    // Release objects until next render cycle.
    vertexArrayObject.release();
    shaderProgram.release();
}


// hier werden shader geladen und initialisiert und dem opengl zugewiesen
void HorizontalSliceRenderer::initOpenGLShaders()
{
    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                               "lines_vshader.glsl"))
    {
        std::cout << "Vertex shader error:\n"
                  << shaderProgram.log().toStdString() << "\n" << std::flush;
        return;
    }

    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                               "lines_fshader_mini.glsl"))
    {
        std::cout << "Fragment shader error:\n"
                  << shaderProgram.log().toStdString() << "\n" << std::flush;
        return;
    }

    if (!shaderProgram.link())
    {
        std::cout << "Shader link error:\n"
                  << shaderProgram.log().toStdString() << "\n" << std::flush;
        return;
    }
}


// initialisiert die zum Zeichnen der Geometrie benötigten Daten auf der GPU
void HorizontalSliceRenderer::initBoundingBoxGeometry()
{
    // Vertices of a unit cube that represents the bounding box.
    const unsigned int numVertices = 16;
    float unitCubeVertices[numVertices][3] = {
        {0.25f, 0.25f, 0.25f}, {0.5f, 0.25f, 0.25f}, {0.5f, 0.5f, 0.25f}, {0.25f, 0.5f, 0.25f},
        {0.25f, 0.25f, 0.25f}, {0.25f, 0.25f, 0.5f}, {0.5f, 0.25f, 0.5f}, {0.5f, 0.25f, 0.25f},
        {0.5f, 0.25f, 0.5f}, {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.25f}, {0.5f, 0.5f, 0.5f},
        {0.25f, 0.5f, 0.5f}, {0.25f, 0.5f, 0.25f}, {0.25f, 0.5f, 0.5f}, {0.25f, 0.25f, 0.5f}};

    // Create vertex buffer and upload vertex data to buffer.
    vertexBuffer.create(); // make sure to destroy in destructor!
    // Binden des Buffers
    vertexBuffer.bind();
    // Allokieren der UnitCube - Punkte
    vertexBuffer.allocate(unitCubeVertices, numVertices * 3 * sizeof(float));
    vertexBuffer.release();

    // Store the information OpenGL needs for rendering the vertex buffer
    // in a "vertex array object". This can easily be bound to the OpenGL
    // pipeline during rendering.
    QOpenGLVertexArrayObject::Binder vaoBinder(&vertexArrayObject);
    if (vertexArrayObject.isCreated())
    {
        vertexBuffer.bind();
        // start, länge eines vertex, neue zeile?
        // analog zu glVertexAttribPointer in GL?
        // "vertexPosition" ~ es wird die repräsentation der positionen beschrieben
        // GL_FLOAT ~ die Werte sind vom typ float
        // 0 ~ Die Daten fangen mit dem ersten Wert im Buffer an
        // 3 ~ tupleSize, wie viele werte enthält ein Vector?
        // 3 * sizeof(float) ~ Zellen je encodierter Position
        shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3, 3*sizeof(float));
        // OpenGL weiß nun wie die Daten interpretiert werden können

        // sollte analog zu glEnableVertexAttribArray in GL sein.
        // "vertexPosition" ~ gibt den `Ort` des Vertex Attributes an
        //
        shaderProgram.enableAttributeArray("vertexPosition");
        vertexBuffer.release();
    }
}
