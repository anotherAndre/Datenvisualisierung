#version 330


smooth in vec2 texCoordVS2FS;
uniform sampler2D textureSampler;

layout(location = 0) out vec4 fragColor;

void main()
{
    fragColor = texture2D(textureSampler, texCoordVS2FS.st);
}


//uniform sampler2D textureSampler;
//varying highp vec4 vertexTexCoord;

//void main(void)
//{
//    gl_FragColor = texture2D(textureSampler, vertexTexCoord.st);
//}



// Fragment Shader
// ~ Bestimmt die Farben der einzelnen Pixel

// out deklariert die ausgegebene variable
//layout(location = 0) out vec4 fragColor;

//void main()
//{
//    // Set the color "red", RGB = (1, 0, 0) to the fragment.
//    // (1, 1, 0) ist gelb
//    fragColor = vec4(1.0f, 0, 0, 1);
//}

