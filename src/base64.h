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


#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
 * Codifica datos en Base64
 * @param input Datos a codificar
 * @param input_len Longitud de los datos
 * @param output_len Longitud del resultado (salida)
 * @return String codificado en Base64 (debe ser liberado con free())
 */
char* encode_to_base64(const unsigned char* input, size_t input_len, size_t* output_len);

/**
 * Decodifica datos desde Base64
 * @param input String en Base64
 * @param input_len Longitud del string
 * @param output_len Longitud de los datos decodificados (salida)
 * @return Datos decodificados (debe ser liberado con free())
 */
unsigned char* decode_from_base64(const char* input, size_t input_len, size_t* output_len);

#endif // BASE64_H
