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
