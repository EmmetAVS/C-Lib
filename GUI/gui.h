#ifndef GUI_H
#define GUI_H

#include <stdio.h>
#include <stdlib.h>
#include "basic/glfw3.h"
#include "dim.h"

GLFWwindow* getWindow(int width, int height, char title[], int resizeable) {
    dim.height = (float) height;
    dim.width = (float) width;
    dim.cx = dim.width/2;
    dim.cy = dim.height/2;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(-1);
    }

    if (resizeable == 1) {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    return window;
}
void closeWindow(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

#endif