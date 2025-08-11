package arbolesBinarios.arbolAVL;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        AVLTree arbol = new AVLTree(); // Crear una instancia del árbol AVL
        Scanner sc = new Scanner(System.in); // Crear un escáner para leer la entrada del usuario
        int opcion = 0;

        do {
            // Mostrar el menú de opciones
            System.out.println("Seleccione una opción:");
            System.out.println("0. Salir");
            System.out.println("1. Insertar nodo");
            System.out.println("2. Imprimir árbol en orden");
            System.out.println("3. Imprimir árbol por jerarquía");
            System.out.println("4. Eliminar nodo");
            System.out.println("Ingrese una opción:");
            opcion = sc.nextInt();
            System.out.println();

            // Ejecutar la opción seleccionada
            switch (opcion) {
                case 0:
                    System.out.println("Saliendo...");
                    break;

                case 1:
                    System.out.println("Ingrese el valor del nuevo nodo:");
                    int value = sc.nextInt();
                    arbol.insert(value); // Insertar un nuevo nodo en el árbol
                    break;

                case 2:
                    System.out.println("Árbol en orden:");
                    arbol.printInOrder(); // Imprimir el árbol en orden
                    System.out.println();
                    break;

                case 3:
                    System.out.println("Árbol por jerarquía:");
                    arbol.printTree(); // Imprimir la estructura completa del árbol
                    System.out.println();
                    break;

                case 4:
                    System.out.println("Ingrese el valor del nodo a eliminar:");
                    int valueToRemove = sc.nextInt();
                    arbol.searchToRemove(valueToRemove); // Eliminar el nodo con el valor dado
                    break;

                default:
                    System.out.println("Opción no válida");
                    break;
            }
        } while (opcion != 0); // Repetir hasta que el usuario elija salir
    }
}