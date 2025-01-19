package Practicos;

import Utils.StackAndQueue.*;
import java.util.Scanner;

public class Practico4 {

    // Ejercicio 1: Implementación de una pila con lista
    public static void testListStack() {
        Stack<String> stack = new Stack<>();
        System.out.println("Implementacion de una pila con lista");
        stack.push("Primero");
        stack.push("Segundo");
        stack.push("Tercero");
        System.out.println("Elemento en la cima de la pila: " + stack.top());
        System.out.println("Eliminar elemento de la cima: " + stack.pop());
        System.out.println("Elemento en la cima después de eliminar: " + stack.top());
    }

    // Ejercicio 2: Pila de Palabras
    public static void wordStack() {
        Scanner scanner = new Scanner(System.in);
        Stack<String> stack = new Stack<>();
        
        System.out.println("Ingrese palabras (escriba 'salir' para terminar):");
        while (true) {
            String word = scanner.nextLine();
            if (word.equalsIgnoreCase("salir")) break;
            stack.push(word);
        }

        System.out.println("Palabras en orden inverso:");
        while (!stack.isEmpty()) {
            System.out.println(stack.pop());
        }
    }

    // Ejercicio 3: Verificación de Paréntesis
    public static boolean areParenthesesBalanced(String expression) {
        Stack<Character> stack = new Stack<>();
        for (char ch : expression.toCharArray()) {
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

    // Ejercicio 4: Conversión de Decimal a Binario
    public static String decimalToBinary(int number) {
        Stack<Integer> stack = new Stack<>();
        while (number > 0) {
            stack.push(number % 2);
            number /= 2;
        }

        StringBuilder binary = new StringBuilder();
        while (!stack.isEmpty()) {
            binary.append(stack.pop());
        }
        return binary.toString();
    }

    // Ejercicio 5: Implementación de una Cola con lista
    public static void testListQueue() {
        Queue<String> queue = new Queue<>();
        queue.enqueue("Uno");
        queue.enqueue("Dos");
        queue.enqueue("Tres");
        System.out.println("Elemento en el frente de la cola: " + queue.front());
        System.out.println("Eliminar elemento del frente: " + queue.dequeue());
        System.out.println("Elemento en el frente después de eliminar: " + queue.front());
    }

    // Ejercicio 6: Cola de Números
    public static void numberQueueSum() {
        Scanner scanner = new Scanner(System.in);
        Queue<Integer> queue = new Queue<>();
        System.out.println("Ingrese números enteros (escriba -1 para terminar):");
        
        while (true) {
            int number = scanner.nextInt();
            if (number == -1) break;
            queue.enqueue(number);
        }

        int sum = 0;
        while (!queue.isEmpty()) {
            sum += queue.dequeue();
        }
        System.out.println("La suma de todos los números es: " + sum);
    }

    // Ejercicio 7: Ordenamiento de Cola
    public static void sortQueueAscending(Queue<Integer> queue) {
        Stack<Integer> stack = new Stack<>();
        
        while (!queue.isEmpty()) {
            int temp = queue.dequeue();
            while (!stack.isEmpty() && stack.top() > temp) {
                queue.enqueue(stack.pop());
            }
            stack.push(temp);
        }

        while (!stack.isEmpty()) {
            queue.enqueue(stack.pop());
        }
    }

    // Ejercicio 8: Verificación de Palíndromos con Cola
    public static boolean isPalindrome(String phrase) {
        phrase = phrase.replaceAll("[\\W_]", "").toLowerCase();
        Queue<Character> queue = new Queue<>();
        Stack<Character> stack = new Stack<>();

        for (char ch : phrase.toCharArray()) {
            queue.enqueue(ch);
            stack.push(ch);
        }

        while (!queue.isEmpty()) {
            if (queue.dequeue() != stack.pop()) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        // Ejemplo de Ejercicio 1
        System.out.println("Prueba de pila con lista:");
        testListStack();

        // Ejemplo de Ejercicio 2
        System.out.println("\nPila de Palabras:");
        wordStack();

        // Ejemplo de Ejercicio 3
        System.out.println("\nVerificación de Paréntesis:");
        String expression = "((3+2)*5)";
        System.out.println("Expresión: " + expression + " -> " +
                           (areParenthesesBalanced(expression) ? "Paréntesis balanceados" : "Paréntesis desbalanceados"));

        // Ejemplo de Ejercicio 4
        System.out.println("\nConversión de Decimal a Binario:");
        int number = 13;
        System.out.println("Número decimal: " + number + " -> Binario: " + decimalToBinary(number));

        // Ejemplo de Ejercicio 5
        System.out.println("\nPrueba de cola con lista:");
        testListQueue();

        // Ejemplo de Ejercicio 6
        System.out.println("\nCola de Números:");
        numberQueueSum();

        // Ejemplo de Ejercicio 7
        System.out.println("\nOrdenamiento de Cola:");
        Queue<Integer> queue = new Queue<>();
        queue.enqueue(3);
        queue.enqueue(1);
        queue.enqueue(4);
        queue.enqueue(2);
        System.out.println("Cola antes de ordenar:");
        displayQueue(queue);

        sortQueueAscending(queue);
        System.out.println("Cola después de ordenar en orden ascendente:");
        displayQueue(queue);

        // Ejemplo de Ejercicio 8
        System.out.println("\nVerificación de Palíndromos con Cola:");
        String phrase = "Anita lava la tina";
        System.out.println("Frase: \"" + phrase + "\" -> " +
                           (isPalindrome(phrase) ? "Es un palíndromo" : "No es un palíndromo"));
        phrase = "Hola Mundo";
        System.out.println("Nueva frase: " + phrase + "\"-> " +
                           (isPalindrome(phrase) ? "Es un palíndromo" : "No es un palíndromo"));
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
