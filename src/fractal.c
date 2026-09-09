#include "fractal.h"
#include <omp.h>

double magnitude(complex z) {
    return sqrt(z.real * z.real + z.imag * z.imag);
}

complex add(complex z1, complex z2) {
    return (complex){z1.real + z2.real, z1.imag + z2.imag};
}

complex add_real(complex z, double c) {
    return (complex){z.real + c, z.imag};
}

complex multiply(complex z1, complex z2) {
    return (complex){z1.real * z2.real - z1.imag * z2.imag, 
                     z1.real * z2.imag + z1.imag * z2.real};
}

int color_map_hsv(int iter, int max_iter) {
    if (iter == max_iter) return 0;
    
    double t = (double)iter / max_iter;
    double hue = fmod(t * 6.0, 1.0);
    double sat = 0.8 + 0.2 * sin(t * 10.0);
    double val = 0.7 + 0.3 * sin(t * 7.0 + 1.0);
    
    double c = val * sat;
    double x = c * (1 - fabs(fmod(hue * 6, 2) - 1));
    double m = val - c;
    
    double r, g, b;
    int h = (int)(hue * 6);
    switch (h) {
        case 0: r = c; g = x; b = 0; break;
        case 1: r = x; g = c; b = 0; break;
        case 2: r = 0; g = c; b = x; break;
        case 3: r = 0; g = x; b = c; break;
        case 4: r = x; g = 0; b = c; break;
        default: r = c; g = 0; b = x; break;
    }
    
    int red = (int)((r + m) * 255);
    int green = (int)((g + m) * 255);
    int blue = (int)((b + m) * 255);
    
    return (red << 16) | (green << 8) | blue;
}

void generate_mandelbrot(complex *image, int width, int height, 
                         double rango_x_min, double rango_x_max, 
                         double rango_y_min, double rango_y_max, 
                         int max_iter) {
    #pragma omp parallel for
    for (int py = 0; py < height; py++) {
        for (int px = 0; px < width; px++) {
            double x0 = rango_x_min + (px / (double)width) * (rango_x_max - rango_x_min);
            double y0 = rango_y_min + (py / (double)height) * (rango_y_max - rango_y_min);
            complex c = {x0, y0};
            complex z = {0, 0};
            int iter = 0;

            while (magnitude(z) < 2 && iter < max_iter) {
                complex z_squared = multiply(z, z);
                complex z_modified = add(z_squared, add_real(c, sin(z.real) + cos(z.imag)));
                z = z_modified;
                iter++;
            }

            int color = color_map_hsv(iter, max_iter);
            image[py * width + px] = (complex){(double)color, 0};
        }
    }
}

void assign_code_to_image(complex *image, const char* base64_code, 
                          int width, int height) {
    size_t code_length = strlen(base64_code);
    printf(COLOR_YELLOW "Asignando código de longitud %zu a la imagen...\n" COLOR_RESET, code_length);
    
    int x = width / 2;
    int y = height / 2;
    int dx = 0, dy = -1;
    size_t total_pixels = (size_t)width * (size_t)height;
    size_t code_index = 0;
    
    for (size_t i = 0; i < total_pixels && code_index < code_length; i++) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            image[y * width + x].real = (double)base64_code[code_index];
            code_index++;
        }
        
        if (x == y || (x < 0 && x == -y) || (x > 0 && x == 1 - y)) {
            int temp = dx;
            dx = -dy;
            dy = temp;
        }
        x += dx;
        y += dy;
    }
    
    printf(COLOR_GREEN "Código asignado: %zu caracteres\n" COLOR_RESET, code_index);
}
