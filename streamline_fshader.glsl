#version 330

// Fragment Shader
// ~ Bestimmt die Farben der einzelnen Pixel

// out deklariert die ausgegebene variable
layout(location = 0) out vec4 streamlineFragColor;

void main()
{
    // Set the color "red", RGB = (1, 0, 0) to the fragment.
    // (1, 1, 0) ist geld
    streamlineFragColor = vec4(1.f, 1.f, 0.f, 1.f);
}

