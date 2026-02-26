#ifndef EXPORTAR_RESULTADOS_H
#define EXPORTAR_RESULTADOS_H

// Exporta dos archivos basados en los vectores xi[] y yi[]:
// - <basename>_tabla.txt     : formato tabla legible (índice, x, y)
// - <basename>_geogebra.txt  : formato listo para pegar en GeoGebra {(x0,y0),(x1,y1),...}
// xi, yi: vectores de tamaño n
// basename: nombre base para los archivos (puede incluir ruta relativa)
void exportarTabla(const char *basename, const double xi[], const double yi[], int n);

// Exporta tabla de comparación con 4 columnas (índice, x, valor1, valor2, error)
// Útil para splines, interpolación, etc. donde se compara valores exactos vs interpolados
// x, y1 (exacto), y2 (interpolado), error: vectores de tamaño n
// basename: nombre base para el archivo (se genera <basename>_comparativa.txt)
void exportarTablaComparativa(const char *basename, const double x[], const double y_exact[], 
                              const double y_interp[], const double error[], int n);

// Exporta vectores x e y a formato CSV importable
// basename: nombre base (se genera outputs/csv/<basename>.csv)
// x, y: vectores de datos
// n: cantidad de puntos
void exportarTablaCSV(const char *basename, const double x[], const double y[], int n);

// Lee tabla CSV y llena los vectores x[] e y[]
// archivo: ruta del archivo CSV a leer
// x, y: vectores donde guardar los datos
// max_puntos: capacidad máxima de los vectores
// Retorna: cantidad de puntos realmente leídos (-1 si error)
int leerTablaCSV(const char *archivo, double x[], double y[], int max_puntos);

#endif // EXPORTAR_RESULTADOS_H