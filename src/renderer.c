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



#include "renderer.h"
#include "../include/common.h"

// ==================== INICIALIZACIÓN DE VENTANA ====================

GLFWwindow* init_window(int width, int height, const char* title) {
    // Configurar GLFW
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4); // Antialiasing
    
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        fprintf(stderr, COLOR_RED "Error creating GLFW window\n" COLOR_RESET);
        return NULL;
    }
    
    glfwMakeContextCurrent(window);
    
    // Configurar proyección ortográfica 2D
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, width, height);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    printf(COLOR_GREEN "✅ Ventana creada: %dx%d\n" COLOR_RESET, width, height);
    
    return window;
}

// ==================== ACTUALIZACIÓN DE TEXTURA ====================

void update_texture(complex *image, int width, int height, GLuint texture) {
    unsigned char *pixels = (unsigned char *)malloc(width * height * 4);
    if (!pixels) {
        fprintf(stderr, COLOR_RED "Error allocating pixels\n" COLOR_RESET);
        return;
    }
    
    // Convertir datos del fractal a píxeles RGBA
    for (int py = 0; py < height; py++) {
        for (int px = 0; px < width; px++) {
            int color_value = (int)image[py * width + px].real;
            
            // Extraer componentes RGB del color empaquetado
            int r = (color_value >> 16) & 0xFF;
            int g = (color_value >> 8) & 0xFF;
            int b = color_value & 0xFF;
            
            int index = (py * width + px) * 4;
            pixels[index + 0] = (unsigned char)r;
            pixels[index + 1] = (unsigned char)g;
            pixels[index + 2] = (unsigned char)b;
            pixels[index + 3] = 255; // Alpha completo
        }
    }
    
    // Subir datos a la GPU
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, 
                 GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    
    // Configurar filtros de textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    free(pixels);
}

// ==================== DIBUJADO DE IMAGEN ====================

void draw_image(complex *image, int width, int height) {
    (void)image;
    (void)width;
    (void)height;
    // Limpiar buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Dibujar un quad con la textura
    glBegin(GL_QUADS);
    
    // Esquina inferior izquierda
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.0f, -1.0f);
    
    // Esquina inferior derecha
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    
    // Esquina superior derecha
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    
    // Esquina superior izquierda
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    
    glEnd();
}

// ==================== DIBUJADO DE HUD (OVERLAY) ====================

void draw_hud(complex *image, int width, int height, 
              const char* language, int max_iter,
              double x_min, double x_max,
              double y_min, double y_max) {
    (void)image;
    (void)width;
    (void)height;
    (void)language;
    // Esta función dibujaría texto en pantalla usando OpenGL
    // Por ahora solo mostramos en consola
    // Para un HUD gráfico real, necesitarías una biblioteca de fuentes
    
    // Mostrar información en consola (versión simplificada)
    static double last_hud_update = 0;
    double current_time = glfwGetTime();
    
    if (current_time - last_hud_update > 2.0) {
        printf(COLOR_CYAN "📊 HUD: Iter=%d | Zoom: [%.3f,%.3f]x[%.3f,%.3f]\n" COLOR_RESET,
               max_iter, x_min, x_max, y_min, y_max);
        last_hud_update = current_time;
    }
}

// ==================== DIBUJADO DE CUADRÍCULA (DEBUG) ====================

void draw_grid(int width, int height, int divisions) {
    (void)width;
    (void)height;
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.3f, 0.3f, 0.3f);
    
    float step_x = 2.0f / divisions;
    float step_y = 2.0f / divisions;
    
    glBegin(GL_LINES);
    for (int i = -divisions; i <= divisions; i++) {
        float pos_x = i * step_x;
        float pos_y = i * step_y;
        
        // Líneas verticales
        glVertex2f(pos_x, -1.0f);
        glVertex2f(pos_x, 1.0f);
        
        // Líneas horizontales
        glVertex2f(-1.0f, pos_y);
        glVertex2f(1.0f, pos_y);
    }
    glEnd();
    
    glEnable(GL_TEXTURE_2D);
}

// ==================== CAPTURA DE PANTALLA ====================

void save_screenshot(const char* filename, int width, int height) {
    unsigned char* pixels = (unsigned char*)malloc(width * height * 3);
    if (!pixels) return;
    
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    
    // Guardar como PPM (formato simple)
    FILE* fp = fopen(filename, "wb");
    if (fp) {
        fprintf(fp, "P6\n%d %d\n255\n", width, height);
        fwrite(pixels, 1, width * height * 3, fp);
        fclose(fp);
        printf(COLOR_GREEN "📸 Screenshot guardado: %s\n" COLOR_RESET, filename);
    }
    
    free(pixels);
}

// ==================== CONFIGURACIÓN DE ANTI-ALIASING ====================

void set_antialiasing(int samples) {
    glfwWindowHint(GLFW_SAMPLES, samples);
    glEnable(GL_MULTISAMPLE);
    printf(COLOR_CYAN "🔍 Anti-aliasing: %dx\n" COLOR_RESET, samples);
}

// ==================== CONFIGURACIÓN DE FULLSCREEN ====================

void toggle_fullscreen(GLFWwindow* window) {
    static int windowed_width = WIDTH;
    static int windowed_height = HEIGHT;
    static int is_fullscreen = 0;
    
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    
    if (is_fullscreen) {
        glfwSetWindowMonitor(window, NULL, 0, 0, 
                            windowed_width, windowed_height, mode->refreshRate);
        is_fullscreen = 0;
    } else {
        // Guardar tamaño actual
        glfwGetWindowSize(window, &windowed_width, &windowed_height);
        glfwSetWindowMonitor(window, monitor, 0, 0, 
                            mode->width, mode->height, mode->refreshRate);
        is_fullscreen = 1;
    }
}

// ==================== LIMPIEZA DE RECURSOS ====================

void cleanup_renderer(GLFWwindow* window) {
    if (window) {
        glfwDestroyWindow(window);
        printf(COLOR_GREEN "🧹 Ventana destruida\n" COLOR_RESET);
    }
}

// ==================== MANEJO DE ERRORES DE GLFW ====================

void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, COLOR_RED "GLFW Error %d: %s\n" COLOR_RESET, error, description);
}

// ==================== MANEJO DE REDIMENSIONADO ====================

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void)window;
    glViewport(0, 0, width, height);
    printf(COLOR_CYAN "📐 Ventana redimensionada: %dx%d\n" COLOR_RESET, width, height);
}
