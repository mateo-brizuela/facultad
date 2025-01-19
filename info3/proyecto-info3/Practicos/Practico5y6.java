package Practicos;
import java.util.*;
import Utils.BinaryTree.SearchTree.SearchTree;

public class Practico5y6 {
    public static void main(String[] args) {
        // Variables
        SearchTree tree = new SearchTree();  // Crear el árbol
        Random rand = new Random();
        int menu_op = 0;
        var console = new Scanner(System.in);
        boolean exit = false;

        // Inicio del menú
        do {
            System.out.println("Se presenta un menú de opciones:\n");
            System.out.println(
                "1- Generar tree con números aleatorios (no permite duplicados)\n" +
                "2- Generar tree con números aleatorios (permite duplicados)\n" +
                "3- Método inOrden (izquierda, raíz, derecha)\n" +
                "4- Cantidad de niveles del árbol\n" +
                "5- Borrar nodo\n" +
                "6- Imprimir árbol binario\n" +
                "7- Salir\n"
            );
            System.out.print("Seleccione una opción: ");
            menu_op = console.nextInt();

            switch (menu_op) {
                case 1:
                tree.setRoot(null);//borramos el arbol anteriormente cargado
                    // Insertar 10 números aleatorios entre 0 y 25 (sin duplicados)
                    System.out.println("\nInsertando números:");
                    for (int i = 0; i < 10; i++) {
                        int number = rand.nextInt(26);  // Genera un número entre 0 y 25
                        System.out.print(number + " ");
                        tree.setRoot(tree.insert(number, tree.getRoot()));  // Insertar el número en el árbol
                    }
                    System.out.println("\n");
                    break;

                case 2:
                tree.setRoot(null); //borramos el arbol anteriormente cargado
                    // Insertar 10 números aleatorios entre 0 y 25 (permitiendo duplicados)
                    System.out.println("\nInsertando números:");
                    for (int i = 0; i < 10; i++) {
                        int number = rand.nextInt(26);  // Genera un número entre 0 y 25
                        System.out.print(number + " ");
                        tree.setRoot(tree.insert_duplicate(number, tree.getRoot()));  // Insertar el número en el árbol
                    }
                    System.out.println("\n");
                    break;

                case 3:
                    // Mostrar los números en orden creciente
                    System.out.println("\n\nNúmeros en el árbol (inorden):");
                    tree.inOrden(tree.getRoot());  // Realizar el recorrido inorden
                    System.out.println("\n");
                    break;

                case 4:
                    System.out.println("\nLa cantidad de niveles del árbol binario es de: " + tree.depth(tree.getRoot()) + "\n");
                    break;

                case 5:
                    int option = 0;
                    System.out.println("\nÁrbol antes de la eliminación (Inorden):");
                    tree.inOrden(tree.getRoot());
                    System.out.println();
                    System.out.print("Ingrese el valor que desea borrar: ");
                    option = console.nextInt();
                    // Eliminar un nodo del árbol
                    tree.setRoot(tree.dtree(tree.getRoot(), option));

                    // Mostrar el árbol después de la eliminación
                    System.out.println("Árbol después de la eliminación (Inorden):");
                    tree.inOrden(tree.getRoot());
                    System.out.println("\n");
                    break;

                case 6:
                    System.out.println("\n\nÁrbol binario:");
                    tree.printTree(tree.getRoot(), "", false);  // Imprimir el árbol
                    System.out.println("\n");
                    break;

                case 7:
                    exit = true;
                    break;

                default:
                    System.out.println("Opción no válida. Intente de nuevo.");
                    break;
            }
        } while (!exit);
        
        console.close();
    }
}
