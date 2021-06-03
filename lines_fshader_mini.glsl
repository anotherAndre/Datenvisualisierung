#version 330

// Fragment Shader
// ~ Bestimmt die Farben der einzelnen Pixel

// out deklariert die ausgegebene variable
layout(location = 0) out vec4 fragColor;

void main()
{
    // Set the color "red", RGB = (1, 0, 0) to the fragment.
    // (1, 1, 0) ist geld
    fragColor = vec4(1.0f, 0, 0, 1);
}

