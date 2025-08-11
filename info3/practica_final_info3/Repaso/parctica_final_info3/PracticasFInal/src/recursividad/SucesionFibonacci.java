package recursividad;

public class SucesionFibonacci {
    public static int fibonacci(int numero){
        if (numero == 1) {
            return 1;
        }

        if (numero == 0) {
            return 0;
        }

        return fibonacci(numero - 1) + fibonacci(numero - 2);

    }
}
