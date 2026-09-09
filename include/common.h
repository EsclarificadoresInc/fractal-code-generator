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


#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <time.h>
#include <GLFW/glfw3.h>

#define WIDTH 1024
#define HEIGHT 768
#define MAX_ITER 1000
#define VERSION "1.0.0"

typedef struct {
    double real;
    double imag;
} complex;

// Colores para consola
#define COLOR_BLACK   "\033[0;30m"
#define COLOR_RED     "\033[0;31m"
#define COLOR_GREEN   "\033[0;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_BLUE    "\033[0;34m"
#define COLOR_MAGENTA "\033[0;35m"
#define COLOR_CYAN    "\033[0;36m"
#define COLOR_WHITE   "\033[0;37m"
#define COLOR_RESET   "\033[0m"

#endif // COMMON_H
