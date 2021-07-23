#version 330

// Vertex Shader
// lines Vertex Shader ie Berechnen der Linien Knoten?

// Model view projection Matrix
uniform mat4 mvpMatrix;

// input vertex attribute (Position mit etra feld für irgendwas)
in vec4 streamlineVertexPosition;

void main()
{
    // Calculate vertex position in screen space.
    // Lineare transformation auf den Bildraum für OpenGL?
    // Output des Vertex Shaders
    gl_Position = mvpMatrix * streamlineVertexPosition;
}
