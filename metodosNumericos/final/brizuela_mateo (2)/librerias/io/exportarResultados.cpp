#include "exportarResultados.h"
#include <stdio.h>
#include <stdlib.h>
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

void exportarDerivadas(const char *basename, const double xi[], const double yi[], int n) {
    if (basename == NULL) {
        printf("exportarDerivadas: basename es NULL\n");
        return;
    }
    if (n <= 0) {
        printf("exportarDerivadas: n debe ser > 0\n");
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

    char path[1024];

    // Tabla legible
    snprintf(path, sizeof(path), "%s/%s_tabla.txt", outdir, basename);
    FILE *f_tabla = fopen(path, "w");
    if (!f_tabla) {
        printf("No se pudo abrir '%s'\n", path);
    } else {
        fprintf(f_tabla, "Idx\t        x_i\t\t       y_i\n");
        fprintf(f_tabla, "-----------------------------------------------\n");
        for (int i = 0; i < n; ++i)
            fprintf(f_tabla, "%3d\t%12.6f\t%12.6f\n", i, xi[i], yi[i]);
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