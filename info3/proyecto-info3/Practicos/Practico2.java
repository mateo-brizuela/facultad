package Practicos;
import Utils.Sorts.*;
import java.util.Scanner;
import java.util.Random;

public class Practico2 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int option;

        // Menú para seleccionar método de ordenamiento
        do {
            System.out.println("Seleccione el método de ordenamiento:");
            System.out.println("1. Insertion Sort");
            System.out.println("2. Shell Sort");
            System.out.println("3. Quick Sort");
            System.out.println("4. Salir");
            System.out.print("Ingrese una opción: ");
            option = scanner.nextInt();

            if (option == 4) {
                System.out.println("Saliendo...");
                break;
            }

            System.out.println("1) Ingresar arreglo por consola");
            System.out.println("2) Generar arreglo aleatoriamente");
            System.out.print("Seleccione una opción: ");
            int arrayOption = scanner.nextInt();

            Integer[] array;
            if (arrayOption == 1) {
                // Opción para ingresar el arreglo manualmente
                System.out.print("Ingrese el tamaño del arreglo: ");
                int size = scanner.nextInt();
                array = new Integer[size];
                System.out.println("Ingrese los elementos del arreglo:");
                for (int i = 0; i < size; i++) {
                    array[i] = scanner.nextInt();
                }
            } else {
                // Genera un arreglo aleatorio de enteros
                System.out.print("Ingrese el tamaño del arreglo: ");
                int size = scanner.nextInt();
                array = generateRandomArray(size);
                System.out.println("Arreglo generado aleatoriamente:");
                displayArray(array);
            }

            // Ejecución del método de ordenamiento seleccionado
            switch (option) {
                case 1:
                    InsertionSort<Integer> insertionSort = new InsertionSort<>(array);
                    insertionSort.sort();
                    System.out.print("Arreglo ordenado con Insertion Sort: ");
                    insertionSort.display();
                    break;

                case 2:
                    ShellSort<Integer> shellSort = new ShellSort<>(array);
                    shellSort.sort();
                    System.out.print("Arreglo ordenado con Shell Sort: ");
                    shellSort.display();
                    break;

                case 3:
                    QuickSort<Integer> quickSort = new QuickSort<>(array);
                    quickSort.sort();
                    System.out.print("Arreglo ordenado con Quick Sort: ");
                    quickSort.display();
                    break;

                default:
                    System.out.println("Opción inválida. Intente nuevamente.");
                    break;
            }
        } while (option != 4);

        scanner.close();
    }

    // Genera un arreglo aleatorio de enteros
    public static Integer[] generateRandomArray(int size) {
        Random random = new Random();
        Integer[] array = new Integer[size];
        for (int i = 0; i < size; i++) {
            array[i] = random.nextInt(100); // Genera números entre 0 y 99
        }
        return array;
    }

    // Método para mostrar el arreglo en pantalla
    public static <T> void displayArray(T[] array) {
        for (T element : array) {
            System.out.print(element + " ");
        }
        System.out.println();
    }
}
