package Testing;
import Utils.BinaryTree.*;
import Utils.BinaryTree.AVLTree.AVLNode;
import Utils.BinaryTree.AVLTree.AVLTree;

import java.util.Scanner;

public class AVLMain {
    public static void main(String[] args) {
        AVLTree avlTree = new AVLTree(); // Crea una instancia de árbol AVL
        Scanner scanner = new Scanner(System.in); // Scanner para leer la entrada del usuario
        int option;

        do {
            System.out.println("1. Insertar nodo");
            System.out.println("2. Eliminar nodo");
            System.out.println("3. Imprimir árbol");
            System.out.println("4. Salir");
            System.out.print("Seleccione una opción: ");
            option = scanner.nextInt(); // Lee la opción seleccionada

            switch (option) {
                case 1:
                    System.out.print("Ingrese el valor del nodo a insertar: ");
                    int dataToInsert = scanner.nextInt();
                    avlTree.insert(new AVLNode(dataToInsert)); // Inserta un nuevo nodo en el árbol
                    System.out.println("Nodo insertado correctamente.");
                    break;

                case 2:
                    System.out.print("Ingrese el valor del nodo a eliminar: ");
                    int dataToDelete = scanner.nextInt();
                    avlTree.delete(dataToDelete); // Elimina un nodo del árbol
                    System.out.println("Nodo eliminado correctamente.");
                    break;

                case 3:
                    System.out.println("Árbol AVL:");
                    avlTree.printTree(avlTree.getRoot(), "", false); // Imprime el árbol AVL
                    break;

                case 4:
                    System.out.println("Saliendo...");
                    break;

                default:
                    System.out.println("Opción inválida. Intente nuevamente.");
                    break;
            }
        } while (option != 4); // Repite hasta que el usuario seleccione salir

        scanner.close(); // Cierra el scanner al terminar
    }
}
