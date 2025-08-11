package modelosFinal;
import static modelosFinal.ContarVocales.contar;
import static modelosFinal.EncontrarMaximo.max;

public class Main {
    public static void main(String[] args) {
        //String palabra =  "mateo";
        //int vocales = contar(palabra, 0, 0);
        //System.out.println(palabra + " tiene : " + vocales +" vocales");

        // encontrar maximo
        int [] vector = {4, 3, 6, 7, 5, 20, 1, 9, 8, 10};
        
        int maximo = max(vector, 0, 0);
        System.out.println("el maximo del vector es: " + maximo);
    }
}
