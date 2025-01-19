package Utils.Sorts;

import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

// clase generica que implementa la interfaz Comparable, esto asegura que losel elementos se
// puedan comparar entre ellos
public class QuickSort<T extends Comparable<T>> {
    private T[] array; // contiene el arreglo a ordenar

    // Constructor que recibe el arreglo a ordenar
    public QuickSort(T[] array) {
        this.array = array;
    }

    // Método de ordenamiento QuickSort
    public void sort() {
        quickSort(0, array.length - 1);
    }

    // Método recursivo de QuickSort
    private void quickSort(int low, int high) {
        // caso base, si low es menor que high el rango tiene como minimo 
        // 2 elementos, por lo que es necesario ordenar
        if (low < high) { 
            int pivotIndex = partition(low, high); // se llama a Partition
            quickSort(low, pivotIndex - 1); 
            quickSort(pivotIndex + 1, high);
        }
    }

    // Partición para QuickSort, este metodo retorna la posicion correcta del pivote
    private int partition(int low, int high) {
        T pivot = array[high]; // se toma como pivote el elemento que esta en el rango derecho
        int i = low - 1; // es el limite izquierdo de los elementos menores o iguales al pivote

        for (int j = low; j < high; j++) {
            // si a lo que apunta j es menor o igual al pivote
            // incrementa i y hace un intercambio entre i y j
            if (array[j].compareTo(pivot) <= 0) { 
                i++;
                swap(i, j);
            }
        }

        // se coloca el pivote en su posicion final(i + 1 porque asegura que todos los elementos a la izquierda...)
        swap(i + 1, high); 
        return i + 1;
    }

    // Método para intercambiar dos elementos del arreglo
    private void swap(int i, int j) {
        T temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    // Método para mostrar el arreglo en pantalla
    public void display() {
        for (T element : array) {
            System.out.print(element + " ");
        }
        System.out.println();
    }
}
