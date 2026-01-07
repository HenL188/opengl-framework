#include "opengl_shape_utils.h"

Vertices create_rectangle2d(Rectangle2D *rectangle) {
    if (rectangle->texture) {
        // 4 vertices * (3 position + 2 texture) = 20 floats
        float *vertices = malloc(sizeof(float) * 20);
        
        // top-right
        vertices[0] = rectangle->x + rectangle->width;  // x position
        vertices[1] = rectangle->y;          // y position
        vertices[2] = 0.0f;       // z position
        vertices[3] = 1.0f;       // texture x (right)
        vertices[4] = 0.0f;       // terectangle->xture y (top)

        // bottom-right
        vertices[5] = rectangle->x + rectangle->width;
        vertices[6] = rectangle->y + rectangle->height;
        vertices[7] = 0.0f;
        vertices[8] = 1.0f;       // texture x (right)
        vertices[9] = 1.0f;       // texture y (bottom)

        // bottom-left
        vertices[10] = rectangle->x;
        vertices[11] = rectangle->y + rectangle->height;
        vertices[12] = 0.0f;
        vertices[13] = 0.0f;      // texture x (left)
        vertices[14] = 1.0f;      // texture y (bottom)

        // top-left
        vertices[15] = rectangle->x;
        vertices[16] = rectangle->y;
        vertices[17] = 0.0f;
        vertices[18] = 0.0f;      // texture x (left)
        vertices[19] = 0.0f;      // texture y (top)

        return vertices;
    }
    
    // Non-texture version (your original code)
    float *vertices = malloc(sizeof(float) * 12);
    vertices[0] = rectangle->x + rectangle->width;
    vertices[1] = rectangle->y;
    vertices[2] = 0.0f;
    vertices[3] = rectangle->x + rectangle->width;
    vertices[4] = rectangle->y + rectangle->height;
    vertices[5] = 0.0f;
    vertices[6] = rectangle->x;
    vertices[7] = rectangle->y + rectangle->height;
    vertices[8] = 0.0f;
    vertices[9] = rectangle->x;
    vertices[10] = rectangle->y;
    vertices[11] = 0.0f;
    return vertices;
}
   
Vertices create_triangle2d(Triangle2D *triangle) {
    if (triangle->texture) {
        float *vertices = malloc(sizeof(float) * 15);
        vertices[0] = triangle->a.x;
        vertices[1] = triangle->a.y;
        vertices[2] = 0.0f;
        vertices[3] = 0.5f;
        vertices[4] = 0.0f;

        // Second point
        vertices[5] = triangle->b.x;
        vertices[6] = triangle->b.y;
        vertices[7] = 0.0f;
        vertices[8] = 0.0f;
        vertices[9] = 1.0f;

        // Third point
        vertices[10] = triangle->c.x;
        vertices[11] = triangle->c.y;
        vertices[12] = 0.0f;
        vertices[13] = 1.0f;
        vertices[14] = 1.0f;

        return vertices;
    }
    float *vertices = malloc(sizeof(float) * 9);

    // First point
    vertices[0] = triangle->a.x;
    vertices[1] = triangle->a.y;
    vertices[2] = 0.0f;

    // Second point
    vertices[3] = triangle->b.x;
    vertices[4] = triangle->b.y;
    vertices[5] = 0.0f;

    // Third point
    vertices[6] = triangle->c.x;
    vertices[7] = triangle->c.y;
    vertices[8] = 0.0f;

    return vertices;
}

// TODO: Vertices create_rectangle3d(Rectangle3D *rectangle) {};


void draw_rectangle2d(unsigned int *shader_program, Data *data, COLOR *color)
{
    glUseProgram(*shader_program);
    if (color != nullptr) {
        glUniform4f(data->uniform_location, color->red, color->green, color->blue, color->alpha);
    }
    glBindVertexArray(data->vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
void draw_triangle2d(unsigned int *shader_program, Data *data, COLOR *color)
{
    glUseProgram(*shader_program);
    if (color != nullptr) {
        glUniform4f(data->uniform_location, color->red, color->green, color->blue, color->alpha);
    }
    glBindVertexArray(data->vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}