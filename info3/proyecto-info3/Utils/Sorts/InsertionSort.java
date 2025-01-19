package Utils.Sorts;

import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

// esta clase es generica y utiliza los parametros de tipo T
// junto con la interfaz xomparable que asegura que los elementos de T se
// pueden comparar entre si
public class InsertionSort<T extends Comparable<T>> {
    private T[] array; // aqui se almacena el arreglo a ordenar

    // Constructor que recibe el arreglo a ordenar
    public InsertionSort(T[] array) {
        this.array = array;
    }

    // Método de ordenamiento Insertion Sort
    public void sort() {
        // recorre el arreglo desde el segundo elemento hasta el final
        for (int i = 1; i < array.length; i++) {
            // se guarda el elemento que se quiere insertar en su posicion correcta
            T key = array[i];
            int j = i - 1;
            // va desplazando todos los elementos antes de key a la derecha para insertar key
            while (j >= 0 && array[j].compareTo(key) > 0) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = key;
        }
    }

    // Método para mostrar el arreglo en pantalla
    public void display() {
        // un foreach que imprime cada elemento del arreglo con espacios al medio
        for (T element : array) {
            System.out.print(element + " ");
        }
        System.out.println();
    }
}
