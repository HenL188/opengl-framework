#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "utils_file.h"
#include "opengl_data.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);
GLFWwindow* init_glfw_window(int major_version, int minor_version, int window_width, int window_height, char* window_title);
void bind_data(Data *data);
unsigned int generate_texture2d(int texture_filter, int min_filter, int mag_filter);
void load_texture(char *texture_path);
unsigned int compile_vertex_shader(char *file_name);
unsigned int compile_fragment_shader(char *file_name);
unsigned int create_shader_program(const unsigned int *vertex_shader, const unsigned int *fragment_shader);
void clear_background(COLOR *color);
void delete_shader_programs(unsigned int shader_program[], int total_programs);
void delete_data(Data *data, int total_data);
void free_all_vertices(float *all_vertices[], int total_vertices);
void delete_data_all(Data *data, int total_data);