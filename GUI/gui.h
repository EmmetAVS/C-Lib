#ifndef GUI_H
#define GUI_H

#include <stdio.h>
#include <stdlib.h>
#include "glfw3.h"
#include "colors.h"
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
void guiColor(Color c) {
    glColor3f(c.red, c.green, c.blue);
}
void setBackground(Color c) {
    glColor3f(c.red, c.green, c.blue);
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -1.0);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, -1.0);
    glEnd();
}
void createBorder(Color c, float s) {

    float w = s / dim.width;
    float h = s / dim.height;

    glColor3f(c.red, c.green, c.blue);
    glBegin(GL_QUADS);

    //Left Top to Left Bottom
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(-1.0f + w, 1.0f);
    glVertex2f(-1.0f + w, -1.0f);

    //Left Top to Right Top
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f-h);
    glVertex2f(1.0f, 1.0f-h);
    glVertex2f(1.0f, 1.0f);

    //Right Top to Right Bottom
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f - w, 1.0f);
    glVertex2f(1.0f - w, -1.0f);

    //Left Bottom to Right Bottom
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f+h);
    glVertex2f(1.0f, -1.0f+h);
    glVertex2f(1.0f, -1.0f);

    glEnd();
}
void closeWindow(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

#endif