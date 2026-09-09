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
