package modelosFinal;

public class ContarVocales {
    public static int contar(String palabra, int contador, int caracterActual){
        if (caracterActual >= palabra.length()) {
            return contador; // fuera del rango
        }

        switch (palabra.charAt(caracterActual)) {
            case 'a':
                contador++;
                break;

            case 'e':
                contador++;
                break;
            
            case 'i':
                contador++;
                break;

            case 'o':
                contador++;
                break;

            case 'u':
                contador++;
                break;
        
            default:
                break;
        }

        return contar(palabra, contador, ++caracterActual);
    }
}
