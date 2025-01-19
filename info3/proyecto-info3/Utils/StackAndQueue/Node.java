package Utils.StackAndQueue;

// Clase que define un nodo genérico para ser usado en pila o cola
public class Node<T> {
    private T data; // Dato almacenado en el nodo
    private Node<T> next; // Referencia al siguiente nodo

    // Constructor que recibe el dato a almacenar
    public Node(T data) {
        this.data = data;
        this.next = null;
    }

    // Método para obtener el dato almacenado
    public T getData() {
        return data;
    }

    // Método para obtener el siguiente nodo
    public Node<T> getNext() {
        return next;
    }

    // Método para establecer el siguiente nodo
    public void setNext(Node<T> next) {
        this.next = next;
    }
}
