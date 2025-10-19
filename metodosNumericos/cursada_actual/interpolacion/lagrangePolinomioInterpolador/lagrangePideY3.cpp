#include <stdio.h>
#include <math.h>

#define n 4  // cantidad de puntos (hay n elementos: índices 0..n-1)

// Función matemática para calcular y automáticamente
double funcionMatematica(double x) {
    return x*x;  // Ejemplo: f(x) = x^2
}

void cargarVector(double x[n], double y[n]);
void leerVector(double x[n], double y[n]);
void lagrange(double x[n], double y[n]);

int main(int argc, char const *argv[])
{
    double x[n], y[n];
    cargarVector(x, y);
    leerVector(x, y);
    lagrange(x, y);
    return 0;
}

void cargarVector(double x[n], double y[n]) {
    int opcion;
    printf("¿Como desea cargar los valores de y?\n");
    printf("1) Ingresar manualmente\n");
    printf("2) Calcular automaticamente con funcion matematica\n");
    printf("Opcion: ");
    scanf("%d", &opcion);
    
    printf("Cargando los %d puntos (x_i, y_i)\n", n);
    for (int i = 0; i < n; i++) {
        printf("Ingrese x%d: ", i);
        scanf("%lf", &x[i]);
        
        if (opcion == 1) {
            printf("Ingrese y%d: ", i);
            scanf("%lf", &y[i]);
        } else {
            y[i] = funcionMatematica(x[i]);
            printf("y%d calculado automaticamente: %.6f\n", i, y[i]);
        }
    }
}

void leerVector(double x[n], double y[n]) {
    printf("\nx\t|\ty\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f\t|\t%.2f | indice: %d \n", x[i], y[i], i);
    }
    printf("\n");
}

void lagrange(double x[n], double y[n]) {
    double suma = 0.0;
    double xr = 0.0;
    char continuar;
    double coeficientes[n];  // Para almacenar los coeficientes L_i(xr)
    
    // Validar que los x sean distintos
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (x[i] == x[j]) {
                printf("Error: x[%d] = x[%d] = %.2f\n", i, j, x[i]);
                return;
            }
        }
    }
    
    do {
        printf("Ingrese el valor que quiere aproximar por interpolacion: ");
        scanf("%lf", &xr);
        
        printf("\nCalculando Lagrange para x = %.2f\n", xr);
        suma = 0.0;
        
        for (int k = 0; k < n; k++) {
            double prod = 1.0;
            for (int i = 0; i < n; i++) {
                if (i != k) {
                    if (x[k] == x[i]) {
                        printf("Error: x[%d] y x[%d] son iguales\n", k, i);
                        return;
                    }
                    prod = prod * ((xr - x[i]) / (x[k] - x[i]));
                }
            }
            coeficientes[k] = prod;  // Guardar el coeficiente L_k(xr)
            suma = suma + y[k] * prod;
            
            // Mostrar término calculado
            printf("Termino %d: y[%d] * L_%d(%.2f) = %.6f * %.6f = %.6f\n", 
                   k, k, k, xr, y[k], prod, y[k] * prod);
        }
        
        printf("\n=== RESULTADOS ===\n");
        printf("Variable a aproximar xr: %.2f\n", xr);
        printf("Aproximacion P_n(xr): %.6f\n", suma);
        
        // Mostrar coeficientes en notación decimal
        printf("\nCoeficientes de Lagrange (notacion decimal):\n");
        for (int k = 0; k < n; k++) {
            printf("L_%d(%.2f) = %.10f\n", k, xr, coeficientes[k]);
        }
        
        // Mostrar coeficientes en notación científica
        printf("\nCoeficientes de Lagrange (notacion cientifica):\n");
        for (int k = 0; k < n; k++) {
            printf("L_%d(%.2f) = %.10e\n", k, xr, coeficientes[k]);
        }
        
        printf("\n¿Evaluar otro punto? (s/n): ");
        scanf(" %c", &continuar);  // El espacio antes de %c es importante
        
    } while (continuar == 's' || continuar == 'S');
}