package ordenamiento.practicaVectores;

import static ordenamiento.practicaVectores.Ordenador.insertionSort;
import static ordenamiento.practicaVectores.Ordenador.shellSort;
import static ordenamiento.practicaVectores.Ordenador.quickSort;
import java.util.*;

public class MainOrdenador {
    public static void main(String[] args) {
        Scanner consola = new Scanner(System.in);
        System.out.println("ingrese el tamaño del vector");
        int n = consola.nextInt();
        int[] vector = new int[n];
        int opcion = 0;

        System.out.println("seleccione una opcion");
        System.out.println("1) llenar el vector manualmente");
        System.out.println("2) llenar el vector con numeros aleatorios");
        opcion = consola.nextInt();

        switch (opcion) {
            case 1:
                llenarVector(vector);
                break;

            case 2:
                llenarVectorAleatorio(vector);
                break;

            default:
                break;
        }


        System.out.println("seleccione un metodo de ordenamiento");
        System.out.println("1) insertion sort");
        System.out.println("2) sehll sort");
        System.out.println("3) quick sort");
        opcion = consola.nextInt();

        switch (opcion) {
            case 1:
                insertionSort(vector);
                break;

            case 2:
                shellSort(vector);
                break;

            case 3:
                quickSort(vector, 0, vector.length - 1);
                break;

            default:
                break;
        }

        System.out.println("vector original");
        mostrarVector(vector);
        System.out.println("vector ordenado");
        mostrarVector(vector);

    }

    public static void llenarVector(int[] vector) {
        Scanner consola = new Scanner(System.in);
        for (int i = 0; i < vector.length; i++) {
            System.out.println("ingrese el valor de la posicion " + i);
            vector[i] = consola.nextInt();
        }
    }

    public static void llenarVectorAleatorio(int[] vector) {
        Random random = new Random();
        for (int i = 0; i < vector.length; i++) {
            vector[i] = random.nextInt(100); // numeros aleatorios entre 0 y 100
        }
        System.out.println("vector llenado con numeros aleatorios");
    }

    public static void mostrarVector(int[] vector) {
        System.err.print("[");
        for (int i = 0; i < vector.length; i++) {
            System.out.print(vector[i] + "; ");
        }
        System.out.println("]");
    }
}
