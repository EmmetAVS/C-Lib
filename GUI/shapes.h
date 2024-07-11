#ifndef SHAPES_H
#define SHAPES_H

#include <stdio.h>
#include <stdlib.h>
#include "glfw3.h"
#include "colors.h"
#include "dim.h"
#include <math.h>

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
void drawCircle(Color c, int x, int y, float r, int s) {
    float fx = (float) x;
    float fy = (float) y;
    float pi = 3.14159265358979323846;

    x += r/2;
    y += r/2;

    glColor3f(c.red, c.green, c.blue);

    glBegin(GL_TRIANGLES);
    for (float i = 0; i <= s-1; i++) {
        float a = (360.0/( (float) s)) * i;

        float x1 = r * cos((a*pi)/180);
        float y1 = r * sin((a*pi)/180);

        float x2 = r * cos(((a+120)*pi)/180);
        float y2 = r * sin(((a+120)*pi)/180);

        float x3 = r * cos(((a+240)*pi)/180);
        float y3 = r * sin(((a+240)*pi)/180);

        glVertex2f(-1.0 + (2*((x + x1)/dim.width)), -1.0 + (2*((y + y1)/dim.height)));
        glVertex2f(-1.0 + (2*((x + x2)/dim.width)), -1.0 + (2*((y + y2)/dim.height)));
        glVertex2f(-1.0 + (2*((x + x3)/dim.width)), -1.0 + (2*((y + y3)/dim.height)));
    }
    glEnd();
}

#endif