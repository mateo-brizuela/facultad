package Utils.StackAndQueue;

// Clase genérica que implementa una pila utilizando un arreglo
public class ArrayStack<T> {
    private T[] stack; // Arreglo que almacena los elementos de la pila
    private int top; // Índice del elemento en la cima de la pila
    private static final int DEFAULT_SIZE = 20; // Tamaño por defecto del arreglo

    // Constructor que recibe el tamaño del arreglo
    @SuppressWarnings("unchecked")
    public ArrayStack(int size) {
        stack = (T[]) new Object[size];
        top = -1; // Inicializa la cima como vacía
    }

    // Constructor sin parámetros que usa el tamaño por defecto
    public ArrayStack() {
        this(DEFAULT_SIZE);
    }

    // Método para agregar un elemento en la cima de la pila
    public void push(T element) {
        if (top < stack.length - 1) {
            stack[++top] = element; // Agrega el elemento y actualiza la cima
        } else {
            System.out.println("Desbordamiento de pila"); // Mensaje de pila llena
        }
    }

    // Método para eliminar y retornar el elemento en la cima
    public T pop() {
        if (top >= 0) {
            return stack[top--]; // Retorna el elemento y reduce la cima
        } else {
            System.out.println("Pila vacía"); // Mensaje de pila vacía
            return null;
        }
    }

    // Método para ver el elemento en la cima sin eliminarlo
    public T top() {
        if (top >= 0) {
            return stack[top];
        } else {
            return null;
        }
    }

    // Método para verificar si la pila está vacía
    public boolean isEmpty() {
        return top == -1;
    }
}
