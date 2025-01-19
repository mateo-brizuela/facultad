package Utils.StackAndQueue;

// Clase genérica que implementa una cola usando nodos
public class Queue<T> {
    private Node<T> front; // Primer nodo de la cola
    private Node<T> rear; // Último nodo de la cola
    private int size;  // Atributo para llevar el tamaño de la cola

    public Queue() {
        this.front = this.rear = null;
        this.size = 0; // Inicializa la cola vacía
    }

    // Método para agregar un elemento al final de la cola
    public void enqueue(T element) {
        Node<T> newNode = new Node<>(element);
        if (rear == null) {
            front = rear = newNode; // Si está vacía, front y rear apuntan al nuevo nodo
        } else {
            rear.setNext(newNode); // Enlaza el último nodo al nuevo nodo
            rear = newNode; // Actualiza el final de la cola
        }
        size++; // Incrementa el tamaño de la cola
    }

    // Método para eliminar y retornar el primer elemento de la cola
    public T dequeue() {
        if (isEmpty()) {
            System.out.println("Desbordamiento de cola"); // Mensaje de cola vacía
            return null;
        }
        T data = front.getData(); // Guarda el dato del frente
        front = front.getNext(); // Actualiza el frente al siguiente nodo
        if (front == null) {
            rear = null; // Si la cola queda vacía, rear también es null
        }
        size--; // Decrementa el tamaño de la cola
        return data; // Retorna el dato eliminado
    }

    // Método para verificar si la cola está vacía
    public boolean isEmpty() {
        return front == null;
    }

    // Método para vaciar la cola
    public void makeEmpty() {
        front = rear = null;
        size = 0;  // Reinicia el tamaño
    }

    // Método para obtener el tamaño actual de la cola
    public int size() {
        return size;
    }

    // Método para ver el primer elemento sin eliminarlo
    public T front() {
        if (isEmpty()) {
            return null;
        }
        return front.getData();
    }
}
