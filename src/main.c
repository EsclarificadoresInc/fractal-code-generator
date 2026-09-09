#include "common.h"
#include "base64.h"
#include "fractal.h"
#include "interpreter.h"
#include "persistence.h"
#include "renderer.h"

// ==================== CONFIGURACIÓN ====================

typedef struct {
    double x_min, x_max, y_min, y_max;
    int max_iter;
    int width, height;
} FractalConfig;

// ==================== CÓDIGOS DE EJEMPLO ====================

const char* get_sample_code(int index) {
    static const char* codes[] = {
        // Python
        "def factorial(n):\n"
        "    if n == 0:\n"
        "        return 1\n"
        "    return n * factorial(n-1)\n"
        "print('Factorial(10) =', factorial(10))\n"
        "print('¡Hola desde el fractal!')",
        
        // C
        "#include <stdio.h>\n"
        "int main() {\n"
        "    printf(\"Hello desde el fractal!\\n\");\n"
        "    int suma = 0;\n"
        "    for(int i=1;i<=10;i++) suma += i;\n"
        "    printf(\"Suma: %d\\n\", suma);\n"
        "    return 0;\n"
        "}",
        
        // JavaScript
        "function fibonacci(n) {\n"
        "    if (n <= 1) return n;\n"
        "    return fibonacci(n-1) + fibonacci(n-2);\n"
        "}\n"
        "console.log('Fibonacci(10) =', fibonacci(10));"
    };
    
    return codes[index % 3];
}

// ==================== BUCLE PRINCIPAL ====================

int main(int argc, char** argv) {
    printf(COLOR_CYAN "╔════════════════════════════════════════════════════════════╗\n");
    printf("║     🌀 FRACTAL CODE GENERATOR v%s                  ║\n", VERSION);
    printf("╚════════════════════════════════════════════════════════════╝\n" COLOR_RESET);
    
    // Inicializar GLFW
    if (!glfwInit()) {
        fprintf(stderr, COLOR_RED "Error initializing GLFW\n" COLOR_RESET);
        return -1;
    }
    
    // Configuración
    FractalConfig config = {
        .x_min = -2.0, .x_max = 2.0,
        .y_min = -2.0, .y_max = 2.0,
        .max_iter = MAX_ITER,
        .width = WIDTH,
        .height = HEIGHT
    };
    
    // Alocar memoria
    complex *image = (complex *)malloc(config.width * config.height * sizeof(complex));
    if (!image) {
        fprintf(stderr, COLOR_RED "Error allocating memory\n" COLOR_RESET);
        glfwTerminate();
        return -1;
    }
    
    // Seleccionar código
    int code_index = 0;
    if (argc > 1) {
        code_index = atoi(argv[1]);
    }
    const char* code_string = get_sample_code(code_index);
    char* language = detect_language(code_string);
    
    // Generar fractal
    printf(COLOR_YELLOW "Generando fractal de Mandelbrot...\n" COLOR_RESET);
    generate_mandelbrot(image, config.width, config.height, 
                        config.x_min, config.x_max,
                        config.y_min, config.y_max, 
                        config.max_iter);
    
    // Codificar código
    printf(COLOR_YELLOW "Codificando código en base64...\n" COLOR_RESET);
    size_t code_length;
    char* base64_code = encode_to_base64((const unsigned char*)code_string, 
                                         strlen(code_string), &code_length);
    if (!base64_code) {
        fprintf(stderr, COLOR_RED "Error encoding code\n" COLOR_RESET);
        free(image);
        glfwTerminate();
        return -1;
    }
    
    printf(COLOR_GREEN "Lenguaje detectado: %s\n" COLOR_RESET, language);
    printf(COLOR_CYAN "Código: %s\n" COLOR_RESET, code_string);
    
    // Asignar código a la imagen
    assign_code_to_image(image, base64_code, config.width, config.height);
    
    // Crear ventana
    GLFWwindow *window = init_window(config.width, config.height, 
                                     "🌀 Fractal Code Generator");
    if (!window) {
        free(image);
        free(base64_code);
        glfwTerminate();
        return -1;
    }
    
    // Crear textura
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    update_texture(image, config.width, config.height, texture);
    
    // Controles
    printf(COLOR_YELLOW "\n=== CONTROLES ===\n" COLOR_RESET);
    printf("  E - Extraer e interpretar código\n");
    printf("  S - Guardar fractal con metadatos\n");
    printf("  L - Cargar fractal guardado\n");
    printf("  Z - Zoom in\n");
    printf("  X - Zoom out\n");
    printf("  R - Resetear vista\n");
    printf("  H - Mostrar HUD\n");
    printf("  ESC - Salir\n\n");
    
    double last_key_press = 0;
    int show_hud = 0;
    double center_x, center_y;
    
    // Bucle principal
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        draw_image(image, config.width, config.height);
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        double current_time = glfwGetTime();
        
        // E - Interpretar
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && 
            current_time - last_key_press > 0.5) {
            interpret_fractal(image, config.width, config.height);
            last_key_press = current_time;
        }
        
        // S - Guardar
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && 
            current_time - last_key_press > 0.5) {
            save_fractal_with_metadata("fractal_data.bin", image, 
                                      config.width, config.height,
                                      base64_code, code_string, language,
                                      config.x_min, config.x_max,
                                      config.y_min, config.y_max,
                                      config.max_iter);
            last_key_press = current_time;
        }
        
        // L - Cargar
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && 
            current_time - last_key_press > 0.5) {
            printf(COLOR_YELLOW "Cargando fractal guardado...\n" COLOR_RESET);
            load_fractal_with_code("fractal_data.bin");
            last_key_press = current_time;
        }
        
        // Z - Zoom in
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && 
            current_time - last_key_press > 0.1) {
            center_x = (config.x_min + config.x_max) / 2;
            center_y = (config.y_min + config.y_max) / 2;
            double factor = 0.9;
            config.x_min = center_x + (config.x_min - center_x) * factor;
            config.x_max = center_x + (config.x_max - center_x) * factor;
            config.y_min = center_y + (config.y_min - center_y) * factor;
            config.y_max = center_y + (config.y_max - center_y) * factor;
            config.max_iter = (int)(config.max_iter * 1.05);
            
            generate_mandelbrot(image, config.width, config.height,
                                config.x_min, config.x_max,
                                config.y_min, config.y_max,
                                config.max_iter);
            assign_code_to_image(image, base64_code, config.width, config.height);
            update_texture(image, config.width, config.height, texture);
            
            printf(COLOR_BLUE "Zoom in: %d iteraciones\n" COLOR_RESET, config.max_iter);
            last_key_press = current_time;
        }
        
        // X - Zoom out
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && 
            current_time - last_key_press > 0.1) {
            center_x = (config.x_min + config.x_max) / 2;
            center_y = (config.y_min + config.y_max) / 2;
            double factor = 1.1;
            config.x_min = center_x + (config.x_min - center_x) * factor;
            config.x_max = center_x + (config.x_max - center_x) * factor;
            config.y_min = center_y + (config.y_min - center_y) * factor;
            config.y_max = center_y + (config.y_max - center_y) * factor;
            config.max_iter = (int)(config.max_iter * 0.95);
            if (config.max_iter < 100) config.max_iter = 100;
            
            generate_mandelbrot(image, config.width, config.height,
                                config.x_min, config.x_max,
                                config.y_min, config.y_max,
                                config.max_iter);
            assign_code_to_image(image, base64_code, config.width, config.height);
            update_texture(image, config.width, config.height, texture);
            
            printf(COLOR_BLUE "Zoom out: %d iteraciones\n" COLOR_RESET, config.max_iter);
            last_key_press = current_time;
        }
        
        // R - Reset
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && 
            current_time - last_key_press > 0.5) {
            config.x_min = -2.0; config.x_max = 2.0;
            config.y_min = -2.0; config.y_max = 2.0;
            config.max_iter = MAX_ITER;
            
            generate_mandelbrot(image, config.width, config.height,
                                config.x_min, config.x_max,
                                config.y_min, config.y_max,
                                config.max_iter);
            assign_code_to_image(image, base64_code, config.width, config.height);
            update_texture(image, config.width, config.height, texture);
            
            printf(COLOR_GREEN "Vista reiniciada\n" COLOR_RESET);
            last_key_press = current_time;
        }
        
        // H - HUD
        if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && 
            current_time - last_key_press > 0.5) {
            show_hud = !show_hud;
            if (show_hud) {
                printf(COLOR_CYAN "\n=== HUD ===\n" COLOR_RESET);
                printf("Lenguaje: %s\n", language);
                printf("Iteraciones: %d\n", config.max_iter);
                printf("Zoom: [%f,%f] x [%f,%f]\n", 
                       config.x_min, config.x_max,
                       config.y_min, config.y_max);
                printf("Código: %.50s...\n", code_string);
            } else {
                printf(COLOR_YELLOW "HUD desactivado\n" COLOR_RESET);
            }
            last_key_press = current_time;
        }
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }
    }
    
    // Limpieza
    free(image);
    free(base64_code);
    cleanup_renderer(window);
    glfwTerminate();
    
    printf(COLOR_GREEN "\n¡Gracias por usar Fractal Code Generator!\n" COLOR_RESET);
    return 0;
}
