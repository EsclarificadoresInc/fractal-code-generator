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
