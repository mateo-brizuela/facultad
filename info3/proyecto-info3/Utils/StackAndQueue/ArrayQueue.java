package Utils.StackAndQueue;

// Clase genérica que implementa una cola utilizando un arreglo circular
public class ArrayQueue<T> {
    private T[] queue; // Arreglo que almacena los elementos de la cola
    private int front, rear, size; // Índices y tamaño actual de la cola
    private static final int DEFAULT_SIZE = 20; // Tamaño por defecto del arreglo

    // Constructor que recibe el tamaño del arreglo
    @SuppressWarnings("unchecked")
    public ArrayQueue(int size) {
        this.queue = (T[]) new Object[size];
        this.front = 0;
        this.rear = -1;
        this.size = 0;
    }

    // Constructor sin parámetros que usa el tamaño por defecto
    public ArrayQueue() {
        this(DEFAULT_SIZE);
    }

    // Método para agregar un elemento al final de la cola
    public void enqueue(T element) {
        if (size == queue.length) {
            System.out.println("Desbordamiento de cola"); // Mensaje de cola llena
        } else {
            rear = (rear + 1) % queue.length; // Incrementa rear de forma circular
            queue[rear] = element;
            size++; // Aumenta el tamaño de la cola
        }
    }

    // Método para eliminar y retornar el primer elemento de la cola
    public T dequeue() {
        if (isEmpty()) {
            System.out.println("Cola vacía"); // Mensaje de cola vacía
            return null;
        } else {
            T data = queue[front];
            front = (front + 1) % queue.length; // Incrementa front de forma circular
            size--; // Disminuye el tamaño de la cola
            return data;
        }
    }

    // Método para verificar si la cola está vacía
    public boolean isEmpty() {
        return size == 0;
    }

    // Método para vaciar la cola
    public void makeEmpty() {
        front = 0;
        rear = -1;
        size = 0;
    }
}
