#pragma once
#include <stdlib.h>

typedef struct Data {
    float *vertices;
    int *indices;
    size_t vertices_size;
    size_t indices_size;
    int stride;
    int uniform_location;
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
} Data;

typedef struct COLOR {
    float red;
    float green;
    float blue;
    float alpha;
} COLOR;

typedef int Indices[];
typedef float* Vertices;