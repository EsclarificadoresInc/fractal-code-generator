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
