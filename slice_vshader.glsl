#version 330


in vec4 sliceVertexPosition;
in vec2 vertexTexCoord;
uniform mat4 mvpMatrix;

smooth out vec2 texCoordVS2FS;

// simple example aus übungs folien übung 2
void main()
{
    gl_Position = mvpMatrix * vec4(sliceVertexPosition.xyz, 1);
    texCoordVS2FS = vertexTexCoord;
}


// Vertex Shader
// lines Vertex Shader ie Berechnen der Linien Knoten?

// Model view projection Matrix
//uniform mat4 mvpMatrix;

//// input vertex attribute (Position mit etra feld für irgendwas)
//in vec4 sliceVertexPosition;
////in vec4 vertexPosition;


//attribute highp vec4 qt_Vertex;
//attribute highp vec4 qt_MultiTexCoord0;
//varying highp vec4 vertexTexCoord;

//void main(void)
//{
//    gl_Position = mvpMatrix * sliceVertexPosition;
//    //vertexTexCoord = qt_MultiTexCoord0;
//}



//void main()
//{
//    // Calculate vertex position in screen space.
//    // Lineare transformation auf den Bildraum für OpenGL?
//    // Output des Vertex Shaders
//    gl_Position = mvpMatrix * sliceVertexPosition ;
//}
