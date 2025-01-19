package Utils.RecursiveFunctions;

public class RecursiveMultiplication {


    public static int multiplication(int a, int b) {
        // Caso base: si b es 0, el producto es 0
        if (b == 0) {
            return 0;
        }
        
        // Si b es negativo, llamamos a la función de manera recursiva con b positivo
        if (b < 0) {
            return -multiplication(a, -b); // Ajuste para el signo
        }
        
        // Suma sucesiva
        return a + multiplication(a, b - 1);
    }
}
