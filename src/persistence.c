#include "persistence.h"
#include "base64.h"
#include "interpreter.h"

void save_fractal_with_metadata(const char* filename, complex *image, 
                                int width, int height, 
                                const char* base64_code,
                                const char* original_code,
                                const char* language,
                                double x_min, double x_max,
                                double y_min, double y_max,
                                int max_iter) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        printf(COLOR_RED "Error guardando archivo\n" COLOR_RESET);
        return;
    }
    
    // Cabecera mágica
    uint32_t magic = 0x46524354; // "FRCT"
    fwrite(&magic, sizeof(uint32_t), 1, fp);
    
    // Metadatos
    struct {
        int width, height, max_iter;
        double x_min, x_max, y_min, y_max;
        char language[32];
        time_t timestamp;
    } meta;
    
    meta.width = width;
    meta.height = height;
    meta.max_iter = max_iter;
    meta.x_min = x_min;
    meta.x_max = x_max;
    meta.y_min = y_min;
    meta.y_max = y_max;
    strncpy(meta.language, language, 31);
    meta.timestamp = time(NULL);
    
    fwrite(&meta, sizeof(meta), 1, fp);
    
    // Código original
    size_t orig_len = strlen(original_code);
    fwrite(&orig_len, sizeof(size_t), 1, fp);
    fwrite(original_code, 1, orig_len, fp);
    
    // Código Base64
    size_t b64_len = strlen(base64_code);
    fwrite(&b64_len, sizeof(size_t), 1, fp);
    fwrite(base64_code, 1, b64_len, fp);
    
    // Datos de imagen
    for (int i = 0; i < width * height; i++) {
        uint32_t color = (uint32_t)image[i].real;
        fwrite(&color, sizeof(uint32_t), 1, fp);
    }
    
    fclose(fp);
    printf(COLOR_GREEN "✅ Fractal guardado en %s\n" COLOR_RESET, filename);
}

int load_fractal_with_code(const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        printf(COLOR_RED "Error abriendo archivo\n" COLOR_RESET);
        return -1;
    }
    
    // Verificar cabecera
    uint32_t magic;
    fread(&magic, sizeof(uint32_t), 1, fp);
    if (magic != 0x46524354) {
        printf(COLOR_RED "Formato de archivo inválido\n" COLOR_RESET);
        fclose(fp);
        return -1;
    }
    
    // Leer metadatos
    struct {
        int width, height, max_iter;
        double x_min, x_max, y_min, y_max;
        char language[32];
        time_t timestamp;
    } meta;
    
    fread(&meta, sizeof(meta), 1, fp);
    
    // Leer código original
    size_t orig_len;
    fread(&orig_len, sizeof(size_t), 1, fp);
    char* original_code = (char*)malloc(orig_len + 1);
    fread(original_code, 1, orig_len, fp);
    original_code[orig_len] = '\0';
    
    // Leer código Base64
    size_t b64_len;
    fread(&b64_len, sizeof(size_t), 1, fp);
    char* base64_code = (char*)malloc(b64_len + 1);
    fread(base64_code, 1, b64_len, fp);
    base64_code[b64_len] = '\0';
    
    fclose(fp);
    
    printf(COLOR_CYAN "=== FRACTAL CARGADO ===\n" COLOR_RESET);
    printf("Lenguaje: %s\n", meta.language);
    printf("Código original: %s\n", original_code);
    
    // Decodificar y ejecutar
    size_t decoded_len;
    unsigned char* decoded = decode_from_base64(base64_code, b64_len, &decoded_len);
    if (decoded && decoded_len > 0) {
        printf(COLOR_GREEN "Código decodificado:\n%s\n" COLOR_RESET, decoded);
        execute_code((char*)decoded, meta.language);
        free(decoded);
    }
    
    free(original_code);
    free(base64_code);
    return 0;
}
