package Utils.StackAndQueue;

 // Clase genérica que implementa una pila utilizando nodos
 public class Stack<T> {
 
     private Node<T> top; // Referencia al nodo en la cima de la pila
 
     public Stack() {
         this.top = null; // Inicializa la pila vacía
     }
 
     // Método para agregar un elemento a la pila
     public void push(T element) {
         Node<T> newNode = new Node<>(element); // Crea un nuevo nodo
         newNode.setNext(top); // Enlaza el nuevo nodo al nodo actual en la cima
         top = newNode; // Actualiza la cima para que apunte al nuevo nodo
     }
 
     // Método para eliminar y retornar el elemento en la cima de la pila
     public T pop() {
         if (top == null) {
             System.out.println("Desbordamiento de pila"); // Mensaje de pila vacía
             return null;
         }
         T data = top.getData(); // Guarda el dato en la cima
         top = top.getNext(); // Actualiza la cima al siguiente nodo
         return data; // Retorna el dato eliminado
     }
 
     // Método para ver el elemento en la cima sin eliminarlo
     public T top() {
         if (top != null) {
             return top.getData();
         }
         return null;
     }
 
     // Método para verificar si la pila está vacía
     public boolean isEmpty() {
         return top == null;
     }
 }
 