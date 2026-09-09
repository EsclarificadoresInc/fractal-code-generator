#ifndef FRACTAL_H
#define FRACTAL_H

#include "../include/common.h"

/**
 * Genera el fractal de Mandelbrot modificado
 */
void generate_mandelbrot(complex *image, int width, int height, 
                         double rango_x_min, double rango_x_max, 
                         double rango_y_min, double rango_y_max, 
                         int max_iter);

/**
 * Asigna código codificado a la imagen fractal
 */
void assign_code_to_image(complex *image, const char* base64_code, 
                          int width, int height);

/**
 * Paleta de colores HSV
 */
int color_map_hsv(int iter, int max_iter);

#endif // FRACTAL_H
