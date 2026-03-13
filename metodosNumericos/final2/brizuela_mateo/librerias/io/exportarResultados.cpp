#include "exportarResultados.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

static void exportarGeoGebraUna(const char *dir, const char *basename,
                                const double xi[], const double yi[], int n) {
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s_geogebra.txt", dir, basename);
    FILE *f = fopen(path, "w");
    if (!f) {
        printf("No se pudo abrir '%s'\n", path);
        return;
    }
    fprintf(f, "{");
    for (int i = 0; i < n; ++i) {
        fprintf(f, "(%.12g,%.12g)", xi[i], yi[i]);
        if (i < n - 1) fprintf(f, ",");
    }
    fprintf(f, "}\n");
    fclose(f);
    printf("Archivo escrito: %s\n", path);
}

static void exportarGeoGebraPartes(const char *dir, const char *basename,
                                   const double xi[], const double yi[], int n,
                                   int partes) {
    if (partes < 1) { partes = 1; }
    if (partes > n) partes = n; // no más partes que puntos
    int base = n / partes;
    int resto = n % partes;
    int idx = 0;

    for (int p = 0; p < partes; ++p) {
        int cant = base + (p < resto ? 1 : 0);
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s_geogebra_part%d.txt", dir, basename, p + 1);
        FILE *f = fopen(path, "w");
        if (!f) {
            printf("No se pudo abrir '%s'\n", path);
            return;
        }
        fprintf(f, "{");
        for (int k = 0; k < cant; ++k) {
            fprintf(f, "(%.12g,%.12g)", xi[idx], yi[idx]);
            if (k < cant - 1) fprintf(f, ",");
            ++idx;
        }
        fprintf(f, "}\n");
        fclose(f);
        printf("Archivo escrito: %s (puntos %d)\n", path, cant);
    }
}

void exportarTabla(const char *basename, const double xi[], const double yi[], int n) {
    if (basename == NULL) {
        printf("exportarTabla: basename es NULL\n");
        return;
    }
    if (n <= 0) {
        printf("exportarTabla: n debe ser > 0\n");
        return;
    }

    // Directorio principal outputs
    const char *outdir = "outputs";
    if (mkdir(outdir, 0755) != 0) {
        if (errno != EEXIST) {
            printf("No se pudo crear '%s' (errno=%d)\n", outdir, errno);
            return;
        }
    }

    // Crear subdirectorio para tablas
    const char *subtabla = "outputs/tabla";
    if (mkdir(subtabla, 0755) != 0) {
        if (errno != EEXIST) {
            printf("No se pudo crear '%s' (errno=%d)\n", subtabla, errno);
            return;
        }
    }

    char path[1024];

    // Tabla legible (ahora en outputs/tabla)
    snprintf(path, sizeof(path), "%s/%s_tabla.txt", subtabla, basename);
    FILE *f_tabla = fopen(path, "w");
    if (!f_tabla) {
        printf("No se pudo abrir '%s'\n", path);
    } else {
        fprintf(f_tabla, "Idx\t        x_i\t\t       y_i\n");
        fprintf(f_tabla, "-----------------------------------------------\n");
        for (int i = 0; i < n; ++i)
            fprintf(f_tabla, "%3d\t%14.10f\t%14.10f\n", i, xi[i], yi[i]);
        fclose(f_tabla);
        printf("Archivo escrito: %s\n", path);
    }

    // Preguntar cómo exportar para GeoGebra
    printf("Exportar puntos GeoGebra:\n");
    printf("  (1) Un solo archivo\n");
    printf("  (2) Dividir en varios archivos\n");
    printf("Opcion (1/2): ");
    int opcion = 1;
    if (scanf("%d", &opcion) != 1) opcion = 1;

    int partes = 1;
    if (opcion == 2) {
        printf("Cantidad de archivos (partes) deseada (>=1): ");
        if (scanf("%d", &partes) != 1) partes = 1;
        if (partes < 1) partes = 1;
    }

    // Crear subdirectorio para geoGebra
    const char *subgeo = "outputs/geogebra";
    if (mkdir(subgeo, 0755) != 0) {
        if (errno != EEXIST) {
            printf("No se pudo crear '%s' (errno=%d)\n", subgeo, errno);
            return;
        }
    }

    if (opcion == 1) {
        exportarGeoGebraUna(subgeo, basename, xi, yi, n);
    } else {
        exportarGeoGebraPartes(subgeo, basename, xi, yi, n, partes);
    }
}

void exportarTablaComparativa(const char *basename, const double x[], const double y_exact[], 
                              const double y_interp[], const double error[], int n) {
    if (basename == NULL) {
        printf("exportarTablaComparativa: basename es NULL\n");
        return;
    }
    if (n <= 0) {
        printf("exportarTablaComparativa: n debe ser > 0\n");
        return;
    }

    // Crear directorio outputs
    const char *outdir = "outputs";
    if (mkdir(outdir, 0755) != 0) {
        if (errno != EEXIST) {
            printf("No se pudo crear '%s' (errno=%d)\n", outdir, errno);
            return;
        }
    }

    // Crear subdirectorio para tablas
    const char *subtabla = "outputs/tabla";
    if (mkdir(subtabla, 0755) != 0) {
        if (errno != EEXIST) {
            printf("No se pudo crear '%s' (errno=%d)\n", subtabla, errno);
            return;
        }
    }

    // Exportar tabla comparativa
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s_comparativa.txt", subtabla, basename);
    FILE *f = fopen(path, "w");
    if (!f) {
        printf("No se pudo abrir '%s'\n", path);
        return;
    }

    // Encabezado de la tabla
    fprintf(f, " i\t    x_i\t      y_exact\t   y_interp\t   |error|\n");
    fprintf(f, "---------------------------------------------------------------\n");
    
    // Datos
    for (int i = 0; i < n; ++i) {
        fprintf(f, "%2d\t%14.10f\t%14.10f\t%14.10f\t%14.10f\n", 
                i, x[i], y_exact[i], y_interp[i], error[i]);
    }
    
    fclose(f);
    printf("Archivo escrito: %s\n", path);
}

void exportarTablaCSV(const char *basename, const double x[], const double y[], int n) {
    if (basename == NULL) {
        printf("exportarTablaCSV: basename es NULL\n");
        return;
    }
    if (n <= 0) {
        printf("exportarTablaCSV: n debe ser > 0\n");
        return;
    }

    // Crear directorio outputs
    const char *outdir = "outputs";
    if (mkdir(outdir, 0755) != 0) {
        if (errno != EEXIST) {
            printf("No se pudo crear '%s' (errno=%d)\n", outdir, errno);
            return;
        }
    }

    // Crear subdirectorio para CSV
    const char *subcsv = "outputs/csv";
    if (mkdir(subcsv, 0755) != 0) {
        if (errno != EEXIST) {
            printf("No se pudo crear '%s' (errno=%d)\n", subcsv, errno);
            return;
        }
    }

    // Exportar CSV
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s.csv", subcsv, basename);
    FILE *f = fopen(path, "w");
    if (!f) {
        printf("No se pudo abrir '%s'\n", path);
        return;
    }

    // Encabezado con metadatos
    fprintf(f, "# Tabla: %s\n", basename);
    fprintf(f, "# Puntos: %d\n", n);
    fprintf(f, "x,y\n");
    
    // Datos
    for (int i = 0; i < n; ++i) {
        fprintf(f, "%.12g,%.12g\n", x[i], y[i]);
    }
    
    fclose(f);
    printf("Archivo CSV escrito: %s\n", path);
}

int leerTablaCSV(const char *archivo, double x[], double y[], int max_puntos) {
    if (archivo == NULL || x == NULL || y == NULL) {
        printf("leerTablaCSV: punteros nulos\n");
        return -1;
    }

    if (max_puntos <= 0) {
        printf("leerTablaCSV: max_puntos debe ser > 0\n");
        return -1;
    }

    FILE *f = fopen(archivo, "r");
    if (!f) {
        printf("leerTablaCSV: no se pudo abrir '%s'\n", archivo);
        return -1;
    }

    // Leer líneas y parsear datos
    int idx = 0;
    char linea[256];
    
    while (fgets(linea, sizeof(linea), f) && idx < max_puntos) {
        // Saltar comentarios y encabezado
        if (linea[0] == '#' || strstr(linea, "x,y") != NULL) {
            continue;
        }
        
        // Parsear línea: "x_valor,y_valor"
        double x_val, y_val;
        int resultado = sscanf(linea, "%lf,%lf", &x_val, &y_val);
        
        if (resultado == 2) {
            x[idx] = x_val;
            y[idx] = y_val;
            idx++;
        }
    }

    fclose(f);
    printf("Tabla CSV leída: %d puntos desde '%s'\n", idx, archivo);
    
    return idx;
}
