package arbolesBinarios.practica2;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        BinarySearchTree arbol = new BinarySearchTree(); // Crear una instancia del árbol binario de búsqueda
        Scanner sc = new Scanner(System.in); // Crear un escáner para leer la entrada del usuario
        int opcion = 0;

        do {
            // Mostrar el menú de opciones
            System.out.println("Seleccione una opción:");
            System.out.println("0. Salir");
            System.out.println("1. Insertar nodo");
            System.out.println("2. Imprimir árbol en orden");
            System.out.println("3. Imprimir árbol entero");
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
                    arbol.insert(); // Insertar un nuevo nodo en el árbol
                    break;

                case 2:
                    arbol.printInOrder(arbol.getRoot()); // Imprimir el árbol en orden
                    break;

                case 3:
                    arbol.printTree(); // Imprimir la estructura completa del árbol
                    break;

                case 4:
                    arbol.searchToRemove(); // Buscar y eliminar un nodo del árbol
                    break;

                default:
                    System.out.println("Opción no válida");
                    break;
            }
            System.out.println("");
        } while (opcion != 0); // Repetir hasta que el usuario elija salir
    }
}
