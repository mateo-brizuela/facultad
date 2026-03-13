# Librería de Exportación de Resultados

## Funcionalidades

### 1. Exportar tablas legibles (formato texto formateado)
- `exportarTabla()`: Exporta dos vectores x, y a formato tabla legible + GeoGebra
- `exportarTablaComparativa()`: Exporta tabla con 5 columnas (índice, x, exacto, interpolado, error)

### 2. Exportar/Importar en formato CSV
- `exportarTablaCSV()`: Exporta vectores x, y a CSV importable
- `leerTablaCSV()`: Lee CSV y rellena vectores x, y dinámicamente

## Estructura de directorios generados

```
outputs/
├── tabla/          → Tablas legibles (espacio separado)
├── geogebra/       → Formato para GeoGebra
└── csv/            → Archivos CSV importables (NUEVO)
```

## Ejemplo de uso: Encadenar dos programas

### Programa A: Exporta datos
```cpp
#include "exportarResultados.h"

int main() {
    double x[] = {1, 2, 3, 4, 5};
    double y[] = {1.5, 3, 4.5, 6, 7.5};
    int n = 5;
    
    // Exporta a outputs/csv/mi_tabla.csv
    exportarTablaCSV("mi_tabla", x, y, n);
    return 0;
}
```

### Programa B: Importa y procesa
```cpp
#include "exportarResultados.h"

int main() {
    double *x = NULL;
    double *y = NULL;
    
    // Lee outputs/csv/mi_tabla.csv
    int n = leerTablaCSV("outputs/csv/mi_tabla.csv", &x, &y);
    
    if (n > 0) {
        // Usar los datos x[], y[] en cálculos
        for (int i = 0; i < n; ++i) {
            printf("x[%d] = %f, y[%d] = %f\n", i, x[i], i, y[i]);
        }
    }
    
    // Exportar resultados procesados
    double y_nuevo[5];
    // ... procesar y llenar y_nuevo
    exportarTablaCSV("resultados_procesados", x, y_nuevo, n);
    
    free(x);
    free(y);
    return 0;
}
```

## Formato CSV interno

Encabezado con metadatos:
```csv
# Tabla: nombre_tabla
# Puntos: 10
x,y
1.0,0.841471
1.5,0.997495
2.0,0.909297
...
```

Ventajas:
- ✓ Legible por humanos (abrirlo en editor o Excel)
- ✓ Fácil de parsear para máquinas
- ✓ Encabezado autodescriptivo
- ✓ Compatible con cualquier programa

## Ejemplos de uso

Ver archivos:
- `main_csv_test.cpp` - Test de exportación/importación
- `main_csv_import.cpp` - Ejemplo de programa que importa y procesa datos

## Compilación

```bash
# Test simple
g++ -o main_csv_test main_csv_test.cpp exportarResultados.cpp -lm

# Importación
g++ -o main_csv_import main_csv_import.cpp exportarResultados.cpp -lm
```
