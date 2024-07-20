#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include "basic/glad.h"
#include "basic/glfw3.h"
#include "stb_image.h"
#ifndef maxTextures
#define maxTextures 50
#endif

int loadedTextures = 0;

GLuint loadTexture(char path[]) {\
    int width, height, numColCh;
    unsigned char* bytes = stbi_load(path, &width, &height, &numColCh, 0); 

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLenum format;
    if (numColCh == 1)
        format = GL_RED;
    else if (numColCh == 3)
        format = GL_RGB;
    else if (numColCh == 4)
        format = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);

    
    loadedTextures++;
    return texture;
}
#endif