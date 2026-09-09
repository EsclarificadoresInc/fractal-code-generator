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




#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include "common.h"

/**
 * Guarda fractal con todos los metadatos
 * @param filename Nombre del archivo
 * @param image Imagen fractal
 * @param width Ancho
 * @param height Alto
 * @param base64_code Código en Base64
 * @param original_code Código original
 * @param language Lenguaje detectado
 * @param x_min, x_max, y_min, y_max Rango del fractal
 * @param max_iter Iteraciones máximas
 */
void save_fractal_with_metadata(const char* filename, complex *image, 
                                int width, int height, 
                                const char* base64_code,
                                const char* original_code,
                                const char* language,
                                double x_min, double x_max,
                                double y_min, double y_max,
                                int max_iter);

/**
 * Carga fractal y ejecuta el código almacenado
 * @param filename Nombre del archivo
 * @return 0 si éxito, -1 si error
 */
int load_fractal_with_code(const char* filename);

#endif // PERSISTENCE_H
