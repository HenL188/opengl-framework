#include "opengl_utils.h"
#include "logger.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow *init_glfw_window(int major_version, int minor_version, int window_width, int window_height, char *window_title)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        log_message("ERROR::FAILED::TO:INITIALIZE::GLFW", nullptr, CRITICAL);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow *window = glfwCreateWindow(window_width, window_height, window_title, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        log_message("ERROR::FAILED::TO:INITIALIZE::WINDOW", nullptr, CRITICAL);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        log_message("ERROR::FAILED::TO:INITIALIZE::GLAD", nullptr, CRITICAL);
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return window;
}

void bind_data(Data *data)
{
    glGenVertexArrays(1, &data->vao);
    glGenBuffers(1, &data->vbo);
    glBindVertexArray(data->vao);

    glBindBuffer(GL_ARRAY_BUFFER, data->vbo);
    glBufferData(GL_ARRAY_BUFFER, data->vertices_size, data->vertices, GL_STATIC_DRAW);

    if (data->indices != nullptr)
    {
        glGenBuffers(1, &data->ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->indices_size, data->indices, GL_STATIC_DRAW);
    }
    switch (data->stride) {
        case 3:
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data->stride * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);
            break;
        case 5:
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data->stride * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, data->stride * sizeof(float), (void *)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            break;
        default:
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data->stride * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);
            break;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

unsigned int generate_texture2d(int texture_filter, int min_filter, int mag_filter) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
    return texture;
}

void load_texture(char *texture_path) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(texture_path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        log_message("ERROR::FAILED::LOAD::TEXTURE", texture_path, ERROR);
    }
    stbi_image_free(data);
}

unsigned int compile_vertex_shader(char *file_name)
{
    const char *vertexShaderSource = read_file(file_name);
    if (vertexShaderSource == nullptr)
    {
        return -1;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    free((void *)vertexShaderSource);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        log_message("ERROR::SHADER::VERTEX::COMPILATION_FAILED", infoLog, ERROR);
    }
    return vertexShader;
}

unsigned int compile_fragment_shader(char *file_name)
{
    const char *fragmentShaderSource = read_file(file_name);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        log_message("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED", infoLog, ERROR);
    }
    return fragmentShader;
}

unsigned int create_shader_program(const unsigned int *vertex_shader, const unsigned int *fragment_shader)
{
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, *vertex_shader);
    glAttachShader(shader_program, *fragment_shader);
    glLinkProgram(shader_program);

    int success;
    char infoLog[512];

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program, 512, nullptr, infoLog);
        log_message("ERROR::PROGRAM::LINKING_FAILED", infoLog, ERROR);
    }

    glDeleteShader(*vertex_shader);
    glDeleteShader(*fragment_shader);
    return shader_program;
}

void clear_background(COLOR *color)
{
    glClearColor(color->red, color->green, color->blue, color->alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void delete_shader_programs(unsigned int shader_program[], int total_programs)
{
    for (int i = 0; i < total_programs; i++)
    {
        glDeleteProgram(shader_program[i]);
    }
}

void delete_data(Data *data, int total_data)
{
    for (int i = 0; i < total_data; ++i) {
        glDeleteVertexArrays(1, &data[i].vao);
        glDeleteBuffers(1, &data[i].vbo);
        glDeleteBuffers(1, &data[i].ebo);
    }
}

void free_all_vertices(float *all_vertices[], int total_vertices) {
    for (int i = 0; i < total_vertices; i++) {
        free(all_vertices[i]);
        all_vertices[i] = nullptr;
    }
}

void delete_data_all(Data *data, int total_data)
{
    for (int i = 0; i < total_data; ++i) {
        glDeleteVertexArrays(1, &data[i].vao);
        glDeleteBuffers(1, &data[i].vbo);
        glDeleteBuffers(1, &data[i].ebo);
        free(data[i].vertices);
        data[i].vertices = nullptr;
    }
}