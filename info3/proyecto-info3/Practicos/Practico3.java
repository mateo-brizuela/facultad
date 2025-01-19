package Practicos;

import Utils.StackAndQueue.*;

public class Practico3 {

    // Ejercicio 1: Implementación de una pila usando un arreglo
    public static void testArrayStack() {
        ArrayStack<Integer> stack = new ArrayStack<>();
        stack.push(10);
        stack.push(20);
        System.out.println("Elemento en la cima de la pila: " + stack.top());
        System.out.println("Eliminar elemento de la cima de la pila: " + stack.pop());
        System.out.println("Elemento en la cima después de eliminar: " + stack.top());
    }

    // Ejercicio 2: Verificación de palíndromos con pila
    public static boolean isPalindrome(String input) {
        input = input.replaceAll("\\s+", "").toLowerCase();
        Stack<Character> stack = new Stack<>();
        int len = input.length();
        
        // Empuja la primera mitad de caracteres
        for (int i = 0; i < len / 2; i++) {
            stack.push(input.charAt(i));
        }

        // Compara la segunda mitad con los caracteres en la pila
        for (int i = (len + 1) / 2; i < len; i++) {
            if (stack.pop() != input.charAt(i)) {
                return false;
            }
        }
        return true;
    }

    // Ejercicio 3: Verificación de paréntesis balanceados
    public static boolean areParenthesesBalanced(String expr) {
        Stack<Character> stack = new Stack<>();
        for (char ch : expr.toCharArray()) {
            if (ch == '(') {
                stack.push(ch);
            } else if (ch == ')') {
                if (stack.isEmpty() || stack.pop() != '(') {
                    return false;
                }
            }
        }
        return stack.isEmpty();
    }

    // Ejercicio 4: Implementación de una cola usando un arreglo
    public static void testArrayQueue() {
        ArrayQueue<String> queue = new ArrayQueue<>();
        queue.enqueue("A");
        queue.enqueue("B");
        System.out.println("Elemento eliminado de la cola: " + queue.dequeue());
        System.out.println("Elemento eliminado de la cola: " + queue.dequeue());
        System.out.println("¿La cola está vacía?: " + queue.isEmpty());
    }

    // Ejercicio 5: Ordenamiento de cola en orden ascendente
    public static void sortQueueAscending(Queue<Integer> queue) {
        Queue<Integer> auxQueue = new Queue<>();
        while (!queue.isEmpty()) {
            int min = queue.dequeue();
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int current = queue.dequeue();
                if (current < min) {
                    queue.enqueue(min);
                    min = current;
                } else {
                    queue.enqueue(current);
                }
            }
            auxQueue.enqueue(min);
        }

        // Mueve los elementos ordenados de nuevo a la cola original
        while (!auxQueue.isEmpty()) {
            queue.enqueue(auxQueue.dequeue());
        }
    }

    public static void main(String[] args) {
        // Ejemplos de ejecución para cada ejercicio
        System.out.println("Prueba de pila con arreglo:");
        testArrayStack();

        // Verificación de palíndromos con ejemplos y resultado en pantalla
        System.out.println("\nVerificación de palíndromos:");
        String word1 = "anilina";
        String word2 = "Hola mundo";
        System.out.println("¿'" + word1 + "' es un palíndromo?: " + isPalindrome(word1));
        System.out.println("¿'" + word2 + "' es un palíndromo?: " + isPalindrome(word2));

        // Verificación de paréntesis balanceados con ejemplos y resultado en pantalla
        System.out.println("\nVerificación de paréntesis balanceados:");
        String expr1 = "(1+(2*3)+((8)/4))";
        String expr2 = "(1+(2*3)+(8)/4))";
        System.out.println("¿'" + expr1 + "' tiene paréntesis balanceados?: " + areParenthesesBalanced(expr1));
        System.out.println("¿'" + expr2 + "' tiene paréntesis balanceados?: " + areParenthesesBalanced(expr2));

        System.out.println("\nPrueba de cola con arreglo:");
        testArrayQueue();

        // Ordenamiento de una cola con valores de ejemplo y mostrando el resultado
        System.out.println("\nOrdenamiento de Cola:");
        Queue<Integer> queue = new Queue<>();
        queue.enqueue(3);
        queue.enqueue(1);
        queue.enqueue(4);
        queue.enqueue(2);
        System.out.print("Cola antes de ordenar: ");
        displayQueue(queue);

        sortQueueAscending(queue);
        System.out.print("Cola después de ordenar en orden ascendente: ");
        displayQueue(queue);
    }

    // Método auxiliar para mostrar los elementos de la cola
    public static void displayQueue(Queue<Integer> queue) {
        Queue<Integer> tempQueue = new Queue<>();
        while (!queue.isEmpty()) {
            int value = queue.dequeue();
            System.out.print(value + " ");
            tempQueue.enqueue(value);
        }
        System.out.println();

        // Restaurar los elementos a la cola original
        while (!tempQueue.isEmpty()) {
            queue.enqueue(tempQueue.dequeue());
        }
    }
}
