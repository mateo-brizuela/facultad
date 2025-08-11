package monticuloBinario;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        BinaryHeap heap = new BinaryHeap(); // Crear una instancia del montículo binario con capacidad inicial de 10
        Scanner sc = new Scanner(System.in); // Crear un escáner para leer la entrada del usuario
        int opcion = 0;

        do {
            // Mostrar el menú de opciones
            System.out.println("Seleccione una opción:");
            System.out.println("0. Salir");
            System.out.println("1. Insertar elemento");
            System.out.println("2. Extraer el mínimo");
            System.out.println("3. Leer el montículo");
            System.out.println("Ingrese una opción:");
            opcion = sc.nextInt();
            System.out.println();

            // Ejecutar la opción seleccionada
            switch (opcion) {
                case 0:
                    System.out.println("Saliendo...");
                    break;

                case 1:
                    System.out.println("Ingrese el valor del nuevo elemento:");
                    int value = sc.nextInt();
                    heap.insert(value); // Insertar un nuevo elemento en el montículo
                    break;

                case 2:
                    try {
                        int min = heap.extractMin(); // Extraer el mínimo del montículo
                        System.out.println("El mínimo extraído es: " + min);
                    } catch (RuntimeException e) {
                        System.out.println(e.getMessage());
                    }
                    break;

                case 3:
                    System.out.println("Montículo:");
                    heap.printHeap(); // Leer el montículo
                    System.out.println();
                    break;

                default:
                    System.out.println("Opción no válida");
                    break;
            }
        } while (opcion != 0); // Repetir hasta que el usuario elija salir
    }
}