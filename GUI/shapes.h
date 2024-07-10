#ifndef SHAPES_H
#define SHAPES_H

#include <stdio.h>
#include <stdlib.h>
#include "glfw3.h"
#include "colors.h"
#include "dim.h"

void drawRect(Color c, int x, int y, int w, int h) {

    float fx = (float) x;
    float fy = (float) y;

    //Calculate Bottom Left
    float x1 = -1.0 + (2 * ((fx)/dim.width));
    float y1 = -1.0 + (2 * ((fy)/dim.height));

    //Calculate Top Left
    float x2 = x1;
    float y2 = y1 + (2 * ((h)/dim.height));

    //Calculate Top Right
    float x3 = x1 + (2 * ((w)/dim.width));
    float y3 = y2;

    //Calculate Bottom Right
    float x4 = x3;
    float y4 = y1;

    glColor3f(c.red, c.green, c.blue);
    glBegin(GL_QUADS);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);

    glEnd();
}
void drawSquare(Color c, int x, int y, int s) {
    drawRect(c, x, y, s, s);
}


#endif