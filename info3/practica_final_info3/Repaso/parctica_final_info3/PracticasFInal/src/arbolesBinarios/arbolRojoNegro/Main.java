package arbolesBinarios.arbolRojoNegro;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        RBTree tree = new RBTree();
        Scanner sc = new Scanner(System.in);
        int option = 0;

        do {
            System.out.println("Seleccione una opción:");
            System.out.println("0. Salir");
            System.out.println("1. Insertar nodo");
            System.out.println("2. Imprimir árbol en orden");
            System.out.println("3. Imprimir árbol entero");
            option = sc.nextInt();

            switch (option) {
                case 0:
                    System.out.println("Saliendo...");
                    break;
                case 1:
                    System.out.println("Ingrese el valor del nodo:");
                    int value = sc.nextInt();
                    tree.insert(value);
                    break;

                case 2:
                    tree.printInOrder(tree.getRoot());
                    break;

                case 3:
                    tree.printTree();
                    break;
            
                default:
                    break;
            }
            System.out.println();
            
        } while (option != 0);
    }
}
