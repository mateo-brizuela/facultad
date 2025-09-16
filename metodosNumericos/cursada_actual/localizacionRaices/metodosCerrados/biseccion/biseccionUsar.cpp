// Metodo de Biseccion con opcion de tolerancia relativa (%) o por cifras decimales
// - Error absoluto aproximado: |c - cViejo|
// - Error relativo porcentual: |c - cViejo| / |c| * 100

#include <stdio.h>
#include <math.h>   // fabs, pow

double calcularFuncion(double x); // declaracion de la funcion

int main() {
    // Variables
    double a = 0.0, b = 0.0, c = 0.0, cViejo = 0.0;
    double fa = 0.0, fb = 0.0, fc = 0.0;
    double eAbs = 0.0;     // error absoluto: |c - cViejo|
    double eRel = 0.0;     // error relativo porcentual: eAbs/|c| * 100
    int cifrasPrecision = 0;
    double tolerancia = 0.0;
    int i = 0; // iteraciones

    bool manual = false;
    int opcion = 0;

    printf("Bienvenido al programa de calculo por biseccion!\n"
           "Seleccione una opcion: \n"
           "  1) Ingresar los valores por terminal\n"
           "  2) Usar valores por defecto del codigo\n");
    if (scanf("%d", &opcion) != 1) { printf("Entrada invalida.\n"); return 1; }
    manual = (opcion == 1);

    if (manual) {
        printf("Ingrese el valor de a: ");
        if (scanf("%lf", &a) != 1) { printf("Entrada invalida.\n"); return 1; }
        printf("Ingrese el valor de b: ");
        if (scanf("%lf", &b) != 1) { printf("Entrada invalida.\n"); return 1; }
    } else {
        // Defaults de ejemplo (ajustalos a tu problema)
        a = 0.0;
        b = 1.0;
        printf("Usando defaults: a=%.6f, b=%.6f\n", a, b);
    }

    // Asegurar a < b
    if (a > b) { double tmp = a; a = b; b = tmp; }

    // Evaluaciones iniciales
    fa = calcularFuncion(a);
    fb = calcularFuncion(b);

    // Raiz exacta en extremos
    if (fa == 0.0) { 
        printf("Raiz exacta en a: %.10f\n", a);
        printf("Intervalo final: [%.10f, %.10f]\n", a, b);
        printf("Iteraciones: %d\n", i);
        return 0; 
    }
    if (fb == 0.0) { 
        printf("Raiz exacta en b: %.10f\n", b);
        printf("Intervalo final: [%.10f, %.10f]\n", a, b);
        printf("Iteraciones: %d\n", i);
        return 0; 
    }

    // Verificar cambio de signo
    if (fa * fb > 0.0) {
        printf("Error: f(a) y f(b) tienen el mismo signo. No hay raiz garantizada en [a,b].\n");
        return 1;
    }

    // Elegir tipo de tolerancia
    int modoTol = 0;
    printf("\nSeleccione el tipo de tolerancia:\n"
           "  1) Relativa (porcentaje) -> usa e_rel%% = |c - cViejo|/|c| * 100\n"
           "  2) Por cifras decimales  -> usa e_abs  = |c - cViejo|\n");
    if (scanf("%d", &modoTol) != 1 || (modoTol != 1 && modoTol != 2)) {
        printf("Entrada invalida.\n"); 
        return 1;
    }

    if (modoTol == 1) {
        // Tolerancia relativa en porcentaje
        printf("Ingrese la tolerancia relativa en porcentaje (ej: 0.01 para 0.01%%): ");
        if (scanf("%lf", &tolerancia) != 1 || tolerancia <= 0.0) {
            printf("Entrada invalida.\n"); 
            return 1;
        }
    } else {
        // Tolerancia por cifras decimales (p): tol_abs = 0.5 * 10^{-p}
        printf("Ingrese la cantidad de cifras decimales de precision (p>=1): ");
        if (scanf("%d", &cifrasPrecision) != 1 || cifrasPrecision < 1) {
            printf("Entrada invalida.\n"); 
            return 1;
        }
        tolerancia = 0.5 * pow(10.0, -cifrasPrecision); // tolerancia ABSOLUTA
        printf("Tolerancia absoluta calculada: %.12f\n", tolerancia);
    }

    // Bucle de biseccion
    const int MAX_IT = 200;
    bool primera = true;

    do {
        i++;
        c  = 0.5 * (a + b);
        fc = calcularFuncion(c);

        // Calcular errores (a partir de la 2da iteracion)
        if (primera) {
            eAbs = INFINITY;            // forzar al menos una iteracion mas
            eRel = INFINITY;
            primera = false;
        } else {
            eAbs = fabs(c - cViejo);
            if (c != 0.0) eRel = (eAbs / fabs(c)) * 100.0;
            else          eRel = INFINITY; // evitar division por cero
        }
        cViejo = c;

        // ¿raiz exacta?
        if (fc == 0.0) {
            printf("\nEncontraste el valor exacto de la raiz!\n");
            printf("Raiz = %.10f\n", c);
            printf("Intervalo final: [%.10f, %.10f]\n", a, b);
            printf("Iteraciones: %d\n", i);
            printf("Error absoluto ~ %.10f\n", eAbs);
            printf("Error relativo %% ~ %.10f\n", eRel);
            return 0;
        }

        // Elegir subintervalo y actualizar SOLO el extremo correspondiente
        if (fa * fc < 0.0) {
            b  = c;
            fb = fc;
        } else {
            a  = c;
            fa = fc;
        }

        if (i >= MAX_IT) {
            printf("\nSe alcanzo el maximo de iteraciones (%d).\n", MAX_IT);
            break;
        }

        // Criterio de corte segun el modo elegido
        if (modoTol == 1) {
            // relativo porcentual
            if (eRel <= tolerancia) break;
        } else {
            // absoluto por cifras
            if (eAbs <= tolerancia) break;
        }

    } while (1);

    // Resultados finales
    printf("\nResultados:\n");
    printf("Raiz aproximada: %.10f\n", c);
    printf("Intervalo final: [%.10f, %.10f]\n", a, b);
    printf("Iteraciones: %d\n", i);
    printf("Error absoluto (|c - cViejo|): %.10f\n", eAbs);
    printf("Error relativo (%%): %.10f\n", eRel);

    return 0;
}

double calcularFuncion(double x){
    // CAMBIAR ACA LA FUNCION 
    return pow(x,10) -1;
}
