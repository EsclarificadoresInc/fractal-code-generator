/*
 * Fractal Code Generator
 * 
 * Copyright (C) 2026 Fractal Code Generator Contributors
 * 
 * This file is part of the Fractal Code Generator project.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later WITH Fractal-Exception
 * 
 * Special Exception:
 * See the LICENSE file for the complete terms and conditions,
 * including the special exceptions for internal use, research,
 * and artistic/educational purposes.
 */

#ifndef COMMON_H
#define COMMON_H
// ... resto del código ...



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
