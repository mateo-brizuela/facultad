package recursividad;

public class CalcularPotencia {
    public static int potencia(int base, int exponente){
        if (exponente == 1) {
            return base;
        }

        return base * potencia(base, exponente - 1);

    }

}
