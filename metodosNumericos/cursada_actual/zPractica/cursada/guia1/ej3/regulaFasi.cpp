// Metodo de falsa posicion con opcion de tolerancia relativa (%) o por cifras decimales
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

    printf("Bienvenido al programa de calculo por falsa posicion!\n"
           "Seleccione una opcion: \n"
           "  1) Ingresar los valores por terminal\n"
           "  2) Usar valores por defecto del codigo\n");
    // Permite alternar entre entradas manuales y un caso de ejemplo
    scanf("%d", &opcion);
    manual = (opcion == 1);

    if (manual) {
        printf("Ingrese el valor de a: ");
        scanf("%lf", &a);
        printf("Ingrese el valor de b: ");
        scanf("%lf", &b);
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
        printf("Raiz exacta en a (decimal): %.10f\n", a);
        printf("Raiz exacta en a (cientifica): %.10e\n", a);
        printf("Intervalo final (decimal): [%.10f, %.10f]\n", a, b);
        printf("Intervalo final (cientifica): [%.10e, %.10e]\n", a, b);
        printf("Iteraciones: %d\n", i);
        return 0; 
    }
    if (fb == 0.0) { 
        printf("Raiz exacta en b (decimal): %.10f\n", b);
        printf("Raiz exacta en b (cientifica): %.10e\n", b);
        printf("Intervalo final (decimal): [%.10f, %.10f]\n", a, b);
        printf("Intervalo final (cientifica): [%.10e, %.10e]\n", a, b);
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
    // Define el criterio de corte que se aplicara en el bucle iterativo
    scanf("%d", &modoTol);

    if (modoTol == 1) {
        // Tolerancia relativa en porcentaje
        printf("Ingrese la tolerancia relativa en porcentaje (ej: 0.01 para 0.01%%): ");
        scanf("%lf", &tolerancia);
    } else {
        // Tolerancia por cifras decimales (p): tol_abs = 0.5 * 10^{-p}
        printf("Ingrese la cantidad de cifras decimales de precision (p>=1): ");
        scanf("%d", &cifrasPrecision);
        tolerancia = 0.5 * pow(10.0, -cifrasPrecision); // tolerancia ABSOLUTA
        printf("Tolerancia absoluta calculada: %.12f\n", tolerancia);
    }

    // Iteraciones del metodo de falsa posicion (regula falsi)
    const int MAX_IT = 200;
    bool primera = true;

    do {
        i++;
        c  = (a*fb-b*fa)/(fb-fa); 
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
            printf("Raiz (decimal): %.10f\n", c);
            printf("Raiz (cientifica): %.10e\n", c);
            printf("Intervalo final (decimal): [%.10f, %.10f]\n", a, b);
            printf("Intervalo final (cientifica): [%.10e, %.10e]\n", a, b);
            printf("Iteraciones: %d\n", i);
            printf("Error absoluto (decimal) ~ %.10f\n", eAbs);
            printf("Error absoluto (cientifica) ~ %.10e\n", eAbs);
            printf("Error relativo %% (decimal) ~ %.10f\n", eRel);
            printf("Error relativo %% (cientifica) ~ %.10e\n", eRel);
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
    printf("Raiz aproximada (decimal): %.10f\n", c);
    printf("Raiz aproximada (cientifica): %.10e\n", c);
    printf("Intervalo final (decimal): [%.10f, %.10f]\n", a, b);
    printf("Intervalo final (cientifica): [%.10e, %.10e]\n", a, b);
    printf("Iteraciones: %d\n", i);
    printf("Error absoluto (|c - cViejo|) decimal: %.10f\n", eAbs);
    printf("Error absoluto (|c - cViejo|) cientifica: %.10e\n", eAbs);
    printf("Error relativo (%%) decimal: %.10f\n", eRel);
    printf("Error relativo (%%) cientifica: %.10e\n", eRel);

    return 0;
}

double calcularFuncion(double x){
    return ((9.81/14)*x) * (1 - exp(((-14)/x) * 7)) - 35;
}
