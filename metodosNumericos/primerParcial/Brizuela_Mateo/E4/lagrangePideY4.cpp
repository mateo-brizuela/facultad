#include <stdio.h>
#include <math.h>

#define n 5  // número de puntos para interpolación (índices 0 a n-1)

// Función matemática para calcular y automáticamente a partir de x
double funcionMatematica(double x) {
    return x*x;  // Ejemplo: f(x) = x² (modificar según necesidad)
}

// Prototipos de funciones
void cargarVector(double x[n], double y[n]);
void leerVector(double x[n], double y[n]);
void lagrange(double x[n], double y[n]);
void mostrarPolinomio(double x[n], double y[n]);

int main(int argc, char const *argv[]) {
    double x[n], y[n];  // Vectores para almacenar puntos de interpolación
    
    // Flujo principal del programa
    cargarVector(x, y);   // Cargar puntos desde usuario
    leerVector(x, y);     // Mostrar puntos cargados
    lagrange(x, y);       // Realizar interpolación de Lagrange
    mostrarPolinomio(x, y);  // Mostrar polinomio interpolante
    
    return 0;
}

// Carga los vectores x e y con los puntos de interpolación
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
            // Carga manual de valores y
            printf("Ingrese y%d: ", i);
            scanf("%lf", &y[i]);
        } else {
            // Carga automática usando función matemática
            y[i] = funcionMatematica(x[i]);
            printf("y%d calculado automaticamente: %.6f\n", i, y[i]);
        }
    }
}

// Muestra los puntos de interpolación en formato tabla
void leerVector(double x[n], double y[n]) {
    printf("\n=== PUNTOS DE INTERPOLACION ===\n");
    printf("x\t|\ty\n");
    printf("-----------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f\t|\t%.2f | indice: %d \n", x[i], y[i], i);
    }
    printf("\n");
}

// Realiza la interpolación de Lagrange para puntos dados
void lagrange(double x[n], double y[n]) {
    double suma = 0.0;     // Acumulador del polinomio evaluado
    double xr = 0.0;       // Punto donde evaluar el polinomio
    char continuar;         // Control para múltiples evaluaciones
    double coeficientes[n]; // Almacena los coeficientes L_k(xr)
    
    // Validación: verificar que todos los nodos x sean distintos
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (x[i] == x[j]) {
                printf("Error: nodos repetidos x[%d] = x[%d] = %.2f\n", i, j, x[i]);
                return;
            }
        }
    }
    
    // Bucle para múltiples evaluaciones del polinomio
    do {
        printf("Ingrese el valor x a interpolar: ");
        scanf("%lf", &xr);
        
        printf("\n=== CALCULO PARA x = %.2f ===\n", xr);
        suma = 0.0;  // Reiniciar acumulador para nueva evaluación
        
        // Calcular cada término del polinomio de Lagrange
        for (int k = 0; k < n; k++) {
            double prod = 1.0;  // Inicializar producto para L_k(x)
            
            // Calcular L_k(x) = Π (x - x_i) / (x_k - x_i) para i ≠ k
            for (int i = 0; i < n; i++) {
                if (i != k) {
                    prod *= (xr - x[i]) / (x[k] - x[i]);
                }
            }
            
            coeficientes[k] = prod;        // Guardar coeficiente
            suma += y[k] * prod;           // Acumular término al polinomio
            
            // Mostrar detalle de cada término
            printf("Termino %d: y[%d] * L_%d(%.2f) = %.6f * %.6f = %.6f\n", 
                   k, k, k, xr, y[k], prod, y[k] * prod);
        }
        
        // Mostrar resultados de la aproximación en ambas notaciones
        printf("\n=== RESULTADOS DE APROXIMACION ===\n");
        printf("Grado del polinomio: %d\n",n-1);
        printf("Punto a interpolar xr = %.2f\n", xr);
        printf("Aproximacion P_n(xr) [decimal]:    %.10f\n", suma);
        printf("Aproximacion P_n(xr) [cientifica]: %.10e\n", suma);
        
        // Preguntar por nueva evaluación
        printf("\n¿Evaluar otro punto? (s/n): ");
        scanf(" %c", &continuar);  // Espacio antes de %c para ignorar saltos de línea
        
    } while (continuar == 's' || continuar == 'S');
    
    // Mostrar coeficientes finales en ambas notaciones
    printf("\n=== COEFICIENTES DE LAGRANGE (para ultimo xr) ===\n");
    
    printf("Coeficientes (notacion decimal):\n");
    for (int k = 0; k < n; k++) {
        printf("L_%d = %.10f\n", k, coeficientes[k]);
    }
    
    printf("\nCoeficientes (notacion cientifica):\n");
    for (int k = 0; k < n; k++) {
        printf("L_%d = %.10e\n", k, coeficientes[k]);
    }
}

// Muestra el polinomio de Lagrange en forma simbólica
void mostrarPolinomio(double x[n], double y[n]) {
    printf("\n=== POLINOMIO INTERPOLANTE DE LAGRANGE ===\n");
    
    // Forma desarrollada (fácil lectura)
    printf("Forma desarrollada:\n");
    printf("P(x) = ");
    for (int k = 0; k < n; k++) {
        printf("%.6f", y[k]);
        printf(" * [");
        for (int i = 0; i < n; i++) {
            if (i != k) {
                printf("(x - %.2f)", x[i]);
                if (i < n-1) printf(" * ");
            }
        }
        printf("] / [");
        for (int i = 0; i < n; i++) {
            if (i != k) {
                printf("(%.2f - %.2f)", x[k], x[i]);
                if (i < n-1) printf(" * ");
            }
        }
        printf("]");
        if (k < n-1) printf(" +\n       ");
    }
    
    // Forma compacta para graficadoras
    printf("\n\nForma para graficadora:\n");
    printf("P(x) = ");
    for (int k = 0; k < n; k++) {
        printf("%.6f", y[k]);
        for (int i = 0; i < n; i++) {
            if (i != k) {
                printf("*((x-%.2f)/(%.2f-%.2f))", x[i], x[k], x[i]);
            }
        }
        if (k < n-1) printf(" + ");
    }
    printf("\n");
}