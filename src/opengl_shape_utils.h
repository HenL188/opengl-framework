#pragma once
#include <stdlib.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "opengl_data.h"

#define RECTANGLE_VERTICES_TEXTURE 20
#define RECTANGLE_VERTICES 12
#define TRIANGLE_VERTICES_TEXTURE 15
#define TRIANGLE_VERTICES 9

#define TEXTURE_STRIDE 5
#define DEFAULT_STRIDE 3

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

typedef struct Triangle {
    Vector2 a;
    Vector2 b;
    Vector2 c;
    bool texture;
} Triangle;

typedef struct Rectangle {
    float x;
    float y;
    float width;
    float height;
    bool texture;
} Rectangle;

float* create_rectangle2d(Rectangle *rectangle);
float* create_triangle2d(Triangle *triangle);
void draw_rectangle(unsigned int *shader_program, Data *data, COLOR *color);
void draw_triangle(unsigned int *shader_program, Data *data, COLOR *color);