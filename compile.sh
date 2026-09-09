#!/bin/bash
# compile.sh - Compilación modular

echo "╔════════════════════════════════════════════════════════════╗"
echo "║     🌀 FRACTAL CODE GENERATOR - COMPILACIÓN MODULAR      ║"
echo "╚════════════════════════════════════════════════════════════╝"

# Colores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# Crear directorios
mkdir -p src include tests/test_codes

# Compilar cada módulo
echo -e "${BLUE}🔨 Compilando módulos...${NC}"

gcc -c src/fractal.c -o fractal.o -fopenmp -O3 -std=c99
gcc -c src/base64.c -o base64.o -O3 -std=c99
gcc -c src/interpreter.c -o interpreter.o -O3 -std=c99
gcc -c src/persistence.c -o persistence.o -O3 -std=c99
gcc -c src/renderer.c -o renderer.o -O3 -std=c99
gcc -c src/main.c -o main.o -O3 -std=c99

# Enlazar
echo -e "${BLUE}🔗 Enlazando...${NC}"
gcc -o fractal_advanced main.o fractal.o base64.o interpreter.o persistence.o renderer.o \
    -lglfw -lGL -lm -fopenmp

# Limpiar objetos
rm -f *.o

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ Compilación exitosa!${NC}"
    echo -e "   📦 Tamaño: $(du -h fractal_advanced | cut -f1)"
    echo -e "${GREEN}🚀 Ejecuta: ./fractal_advanced${NC}"
else
    echo -e "${RED}❌ Error en la compilación${NC}"
    exit 1
fi
