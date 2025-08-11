package arbolesBinarios.practica;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner consola = new Scanner(System.in);
        int opcion;

        BinarySearchTree arbol = new BinarySearchTree();

        do {
            System.out.println("Seleccione una opción:");
            System.out.println("0) Salir");
            System.out.println("1) Agregar nodo");
            System.out.println("2) Mostrar arbol");
            System.out.println("3) insertar con insertRec2");
            opcion = consola.nextInt();
            System.out.println("");

            switch (opcion) {
                case 1:
                    System.out.println("Ingrese el valor del nodo:");
                    int valor = consola.nextInt();
                    arbol.insert(valor);
                    System.out.println("");
                    break;

                case 2:
                    arbol.printInOrder(arbol.getRoot());
                    break;

                case 3:
                    System.out.println("Ingrese el valor del nodo:");
                    int valor2 = consola.nextInt();
                    arbol.insert2(valor2);
                    System.out.println("");
                    break;

                case 0:
                    System.out.println("Saliendo...");
                    break;

                default:
                    System.out.println("Opción no válida");
                    break;
            }
        } while (opcion != 0);
    }
}
