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


#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "common.h"

/**
 * Detecta el lenguaje de programación del código
 * @param code Código fuente
 * @return String con el nombre del lenguaje detectado
 */
char* detect_language(const char* code);

/**
 * Ejecuta código en el lenguaje especificado
 * @param code Código fuente a ejecutar
 * @param language Lenguaje del código
 */
void execute_code(const char* code, const char* language);

/**
 * Extrae código codificado de la imagen fractal
 * @param image Imagen fractal
 * @param width Ancho de la imagen
 * @param height Alto de la imagen
 * @param code_len Longitud del código extraído (salida)
 * @return Código extraído (debe ser liberado con free())
 */
char* extract_code_from_image(complex *image, int width, int height, size_t* code_len);

/**
 * Interpreta el fractal completo (extrae, decodifica y ejecuta)
 * @param image Imagen fractal
 * @param width Ancho de la imagen
 * @param height Alto de la imagen
 */
void interpret_fractal(complex *image, int width, int height);

#endif // INTERPRETER_H
