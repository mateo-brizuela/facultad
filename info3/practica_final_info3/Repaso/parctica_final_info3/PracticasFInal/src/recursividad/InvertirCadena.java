package recursividad;

public class InvertirCadena {
    public static String invertiString(String cadena){
        // caso base 
        if (cadena.length() <= 1) {
            return cadena;
        }

        return invertiString(cadena.substring(1)) + cadena.charAt(0);
    }
}
