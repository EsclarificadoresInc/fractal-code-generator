#include "interpreter.h"
#include "base64.h"

char* detect_language(const char* code) {
    static char language[32];
    snprintf(language, sizeof(language), "unknown");

    if (strstr(code, "package main") || strstr(code, "func main")) {
        snprintf(language, sizeof(language), "go");
    } else if (strstr(code, "fn main") || strstr(code, "println!")) {
        snprintf(language, sizeof(language), "rust");
    } else if (strstr(code, "#include") || strstr(code, "int main") || strstr(code, "printf(")) {
        snprintf(language, sizeof(language), "c");
    } else if (strstr(code, "public class") || strstr(code, "System.out")) {
        snprintf(language, sizeof(language), "java");
    } else if (strstr(code, "function ") || strstr(code, "console.log") || strstr(code, "var ") || strstr(code, "let ")) {
        snprintf(language, sizeof(language), "javascript");
    } else if (strstr(code, "puts ") || strstr(code, "def ") || strstr(code, "end")) {
        snprintf(language, sizeof(language), "ruby");
    } else if (strstr(code, "def ") || strstr(code, "import ") || strstr(code, "print(")) {
        snprintf(language, sizeof(language), "python");
    }

    return language;
}

void execute_code(const char* code, const char* language) {
    printf(COLOR_CYAN "\n=== EJECUTANDO CÓDIGO EN %s ===\n" COLOR_RESET, language);
    printf(COLOR_YELLOW "Código a ejecutar:\n%s\n" COLOR_RESET, code);
    printf("----------------------------------------\n");
    
    if (strcmp(language, "python") == 0) {
        FILE* fp = fopen("temp_code.py", "w");
        if (fp) {
            fprintf(fp, "%s", code);
            fclose(fp);
            system("python3 temp_code.py 2>/dev/null || python temp_code.py");
            remove("temp_code.py");
        }
    } 
    else if (strcmp(language, "javascript") == 0) {
        FILE* fp = fopen("temp_code.js", "w");
        if (fp) {
            fprintf(fp, "%s", code);
            fclose(fp);
            system("node temp_code.js 2>/dev/null");
            remove("temp_code.js");
        }
    }
    else if (strcmp(language, "c") == 0) {
        FILE* fp = fopen("temp_code.c", "w");
        if (fp) {
            fprintf(fp, "%s", code);
            fclose(fp);
            system("gcc temp_code.c -o temp_code 2>/dev/null && ./temp_code 2>/dev/null");
            remove("temp_code.c");
            remove("temp_code");
        }
    }
    else if (strcmp(language, "java") == 0) {
        char class_name[256] = "Main";
        char* class_pos = strstr(code, "public class");
        if (class_pos) {
            char* name_start = class_pos + 13;
            while (*name_start && isspace((unsigned char)*name_start)) name_start++;
            char* name_end = name_start;
            while (*name_end && !isspace((unsigned char)*name_end) && *name_end != '{') name_end++;
            int len = (int)(name_end - name_start);
            if (len > 0 && len < 255) {
                strncpy(class_name, name_start, (size_t)len);
                class_name[len] = '\0';
            }
        }
        
        FILE* fp = fopen("temp_code.java", "w");
        if (fp) {
            fprintf(fp, "%s", code);
            fclose(fp);
            char command[512];
            snprintf(command, sizeof(command), 
                    "javac temp_code.java 2>/dev/null && java %s 2>/dev/null", class_name);
            system(command);
            remove("temp_code.java");
            remove("temp_code.class");
        }
    }
    else if (strcmp(language, "ruby") == 0) {
        FILE* fp = fopen("temp_code.rb", "w");
        if (fp) {
            fprintf(fp, "%s", code);
            fclose(fp);
            system("ruby temp_code.rb 2>/dev/null");
            remove("temp_code.rb");
        }
    }
    else if (strcmp(language, "go") == 0) {
        FILE* fp = fopen("temp_code.go", "w");
        if (fp) {
            fprintf(fp, "%s", code);
            fclose(fp);
            system("go run temp_code.go 2>/dev/null");
            remove("temp_code.go");
        }
    }
    else if (strcmp(language, "rust") == 0) {
        FILE* fp = fopen("temp_code.rs", "w");
        if (fp) {
            fprintf(fp, "%s", code);
            fclose(fp);
            system("rustc temp_code.rs -o temp_code 2>/dev/null && ./temp_code 2>/dev/null");
            remove("temp_code.rs");
            remove("temp_code");
        }
    }
    else {
        printf(COLOR_YELLOW "Lenguaje '%s' no soportado para ejecución automática\n" COLOR_RESET, language);
        printf("Puedes copiar manualmente el código mostrado arriba.\n");
    }
}

char* extract_code_from_image(complex *image, int width, int height, size_t* code_len) {
    int x = width / 2;
    int y = height / 2;
    int dx = 0, dy = -1;
    size_t total_pixels = (size_t)width * (size_t)height;
    
    unsigned char* extracted = (unsigned char*)malloc(total_pixels + 1);
    if (!extracted) return NULL;
    
    size_t extracted_len = 0;
    size_t visited = 0;
    
    while (visited < total_pixels && extracted_len < total_pixels) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            double val = image[y * width + x].real;
            if (val >= 32 && val <= 126) {
                extracted[extracted_len++] = (unsigned char)val;
            }
        }
        
        if (x == y || (x < 0 && x == -y) || (x > 0 && x == 1 - y)) {
            int temp = dx;
            dx = -dy;
            dy = temp;
        }
        x += dx;
        y += dy;
        visited++;
    }
    
    extracted[extracted_len] = '\0';
    *code_len = extracted_len;
    printf(COLOR_CYAN "Extraídos %zu caracteres de la imagen\n" COLOR_RESET, extracted_len);
    
    return (char*)extracted;
}

void interpret_fractal(complex *image, int width, int height) {
    printf(COLOR_MAGENTA "\n=== INTERPRETE DEL FRACTAL ===\n" COLOR_RESET);
    
    size_t extracted_len;
    char* extracted_code = extract_code_from_image(image, width, height, &extracted_len);
    
    if (!extracted_code || extracted_len == 0) {
        printf(COLOR_RED "No se pudo extraer código de la imagen\n" COLOR_RESET);
        return;
    }
    
    printf(COLOR_YELLOW "Código extraído (%zu caracteres):\n%s\n" COLOR_RESET, extracted_len, extracted_code);
    
    size_t decoded_len;
    unsigned char* decoded_code = decode_from_base64(extracted_code, extracted_len, &decoded_len);
    
    if (decoded_code && decoded_len > 0) {
        printf(COLOR_GREEN "\nCódigo decodificado:\n%s\n" COLOR_RESET, decoded_code);
        char* language = detect_language((char*)decoded_code);
        printf(COLOR_CYAN "Lenguaje detectado: %s\n" COLOR_RESET, language);
        execute_code((char*)decoded_code, language);
        free(decoded_code);
    } else {
        printf(COLOR_RED "Error decodificando el código base64\n" COLOR_RESET);
        printf(COLOR_YELLOW "Intentando ejecutar el código extraído directamente...\n" COLOR_RESET);
        char* language = detect_language(extracted_code);
        printf(COLOR_CYAN "Lenguaje detectado: %s\n" COLOR_RESET, language);
        execute_code(extracted_code, language);
    }
    
    free(extracted_code);
}
