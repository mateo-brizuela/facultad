package recursividad;

public class FactorialNumero {
    public static int CalcularFactorial(int numero){
        if (numero <= 1) {
            return 1;
        }
        return numero * CalcularFactorial(numero -1);
    }

}
