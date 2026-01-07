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

typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;

typedef struct Triangle2D {
    Vector2 a;
    Vector2 b;
    Vector2 c;
    bool texture;
} Triangle2D;

typedef struct Rectangle2D {
    float x;
    float y;
    float width;
    float height;
    bool texture;
} Rectangle2D;

typedef struct Triangle3D {
    Vector3 a;
    Vector3 b;
    Vector3 c;
    bool texture;
} Triangle3D;

typedef struct Rectangle3D {
    float x;
    float y;
    float z;
    float width;
    float height;
    bool texture;
} Rectangle3D;

Vertices create_rectangle2d(Rectangle2D *rectangle);
Vertices create_triangle2d(Triangle2D *triangle);
// TODO: Vertices create_rectangle3d(Rectangle3D *rectangle);
// TODO: Vertices create_triangle3d(Triangle3D *triangle);
void draw_rectangle2d(unsigned int *shader_program, Data *data, COLOR *color);
void draw_triangle2d(unsigned int *shader_program, Data *data, COLOR *color);