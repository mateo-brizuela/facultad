package monticuloBinario;

import practicos.practico1;

public class BinaryHeap {
    private static final int DEFAULT_CAPACITY = 100;
    private int currentSize;
    private int[] array;

    // Constructor
    public BinaryHeap(){
        currentSize = 0;
        this.array = new int[DEFAULT_CAPACITY + 1]; // se le suma uno porque el primer elemento del arreglo no se usa
    }

    //metodos

    private int leftChild(int i){
        return i * 2;
    }

    private int rightChild(int i){
        return (i*2) + 1;
    }

    private int parent(int i){
        return i / 2;
    }

    private void swap(int i, int j){
        int tmp = array[j];
        array[j] = array[i];
        array[i] = tmp;
    }

    public void insert(int x){
        if ((currentSize + 1) == array.length) {
            duplicateArray();
        }

        array[++currentSize] = x;
        int current = currentSize; // el actual es el ultimo elemento insertado

        // el nuevo elemento insertado va escalando el monticulo hasta su posicion correcta
        while (current > 1 && array[current] < array[parent(current)]) {
            swap(current, parent(current)); // se intercambian los elementos
            current = parent(current); // se actualizan los indices
        }
    }

    // se asume que i es el menor elemento
    public void heapifyDown(int i){
        int smallest = i;

        int left = leftChild(i);
        int right = rightChild(i);

        // si el hijo izquierdo es menor que el smallest se actualiza
        if (left <= currentSize && array[left] < array[smallest]) {
            smallest = left;
        }

        // si el hijo derecho es menor que el hijo izquierdo o el i se actualiza
        if (right <= currentSize && array[right] < array[smallest]) {
            smallest = right;
        }

        // si el elemento menor no es i, se hace un intercambio y se sigue bajando en el monticulo
        if (smallest != i) {
            swap(i, smallest);
            heapifyDown(smallest);
        }
    }

    public int extractMin(){
        if (currentSize < 1) {
            System.out.println("no hay elementos en el moniculo");
            throw new RuntimeException("monticulo vacio!");
        }

        int min = array[1];
        array[1] = array[currentSize--]; // se coloca el ultimo elemento insertado en la raiz
        heapifyDown(1); // se reorganiza el monticulo
        return min;
    }



    //imprimir
    public void printHeap(){
        for (int i = 1; i <= currentSize; i++) {
            System.out.print(array[i] + " ");
        }
        System.out.println();
    }



    // duplica el tamaño del arreglo
    public void duplicateArray(){
        int[] newArray = new int[array.length * 2];

        for (int i = 1; i < currentSize; i++) { // se copian los elementos del arreglo original al nuevo arreglo
            newArray[i] = array[i];  
        }

        array = newArray; // asigna el nuevo arreglo al arreglo original
    }
}
