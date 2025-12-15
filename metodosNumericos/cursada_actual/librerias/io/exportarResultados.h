#ifndef EXPORTAR_RESULTADOS_H
#define EXPORTAR_RESULTADOS_H

// Exporta dos archivos basados en los vectores xi[] y yi[]:
// - <basename>_tabla.txt     : formato tabla legible (índice, x, y)
// - <basename>_geogebra.txt  : formato listo para pegar en GeoGebra {(x0,y0),(x1,y1),...}
// xi, yi: vectores de tamaño n
// basename: nombre base para los archivos (puede incluir ruta relativa)
void exportarDerivadas(const char *basename, const double xi[], const double yi[], int n);

#endif // EXPORTAR_RESULTADOS_H