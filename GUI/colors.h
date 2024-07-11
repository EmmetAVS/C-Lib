#ifndef COLORS_H
#define COLORS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Color{
    float red;
    float green;
    float blue;
} Color;

Color colorWhite = {255, 255, 255};
Color colorBlack = {0, 0, 0};
Color colorRed = {255, 0, 0};
Color colorGreen = {0, 255, 0};
Color colorBlue = {0, 0, 255};
Color colorYellow = {255, 255, 0};
Color colorTeal = {0, 255, 255};

Color initColor(int r, int g, int b) {
    if (r > 255 || r < 0) {
        perror("Color (R) value cannot be above 255 or below 0");
        exit(1);
    } else if (g > 255 || g < 0) {
        perror("Color (G) value cannot be above 255 or below 0");
        exit(1);
    } else if (b > 255 || b < 0) {
        perror("Color (B) value cannot be above 255 or below 0");
        exit(1);
    }
    float red = ((float) r)/255.0f;
    float green = ((float) g)/255.0f;
    float blue = ((float) b)/255.0f;
    Color c;
    c.red = red;
    c.green = green;
    c.blue = blue;
    return c;
}

#endif