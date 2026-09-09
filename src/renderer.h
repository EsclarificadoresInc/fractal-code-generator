#ifndef RENDERER_H
#define RENDERER_H

#include "../include/common.h"

// Inicialización
GLFWwindow* init_window(int width, int height, const char* title);
void cleanup_renderer(GLFWwindow* window);

// Renderizado
void update_texture(complex *image, int width, int height, GLuint texture);
void draw_image(complex *image, int width, int height);
void draw_hud(complex *image, int width, int height, 
              const char* language, int max_iter,
              double x_min, double x_max,
              double y_min, double y_max);
void draw_grid(int width, int height, int divisions);

// Utilidades
void save_screenshot(const char* filename, int width, int height);
void set_antialiasing(int samples);
void toggle_fullscreen(GLFWwindow* window);

// Callbacks
void glfw_error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif // RENDERER_H
