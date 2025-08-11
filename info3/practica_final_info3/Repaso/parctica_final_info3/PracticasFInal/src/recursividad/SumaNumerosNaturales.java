package recursividad;

public class SumaNumerosNaturales {
    public static int sumarNaturales(int numero){
        // caso base
        if (numero <= 1) {
            return 1;
        }
        return numero + sumarNaturales(numero - 1);
    }

}
