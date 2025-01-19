package Utils.Sorts;

import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

 // es una clase generica que usa la interfaz Comparable
public class ShellSort<T extends Comparable<T>> {
    private T[] array;  // aqui se guarda el arreglo a ordenar

    // Constructor que recibe el arreglo a ordenar
    public ShellSort(T[] array) {
        this.array = array;
    }

    // Método de ordenamiento Shell Sort
    public void sort() {

        int n = array.length;   
        // la distancia gap para comparar entre elementos se divide por 2 en cada iteracion
        for (int gap = n / 2; gap > 0; gap /= 2) {
            // se recorre el arreglo desde el indice gap hasta el final
            // guardando el elemento key, para acomodarlo en su posicion correcta
            for (int i = gap; i < n; i++) {
                T key = array[i];
                int j = i; // j se inicializa en i, y se usara para mover key a su posicion correcta
                
                // compara key con sus elementos anteriores en el arreglo a una distancia de gap
                while (j >= gap && array[j - gap].compareTo(key) > 0) {
                    array[j] = array[j - gap]; 
                    j -= gap;
                }
                array[j] = key; // finaliza colocando a key en su posicion correcta con el gap de ese momento
            }
        }
    }

    // Método para mostrar el arreglo en pantalla
    public void display() {
        for (T element : array) {
            System.out.print(element + " ");
        }
        System.out.println();
    }
}
