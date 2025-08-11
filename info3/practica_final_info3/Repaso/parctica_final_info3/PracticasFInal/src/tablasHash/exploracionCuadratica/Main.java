package tablasHash.exploracionCuadratica;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        HashTable hashTable = new HashTable(10); // Crear una instancia de la tabla hash con capacidad inicial de 10
        Scanner sc = new Scanner(System.in); // Crear un escáner para leer la entrada del usuario
        int opcion = 0;

        do {
            // Mostrar el menú de opciones
            System.out.println("Seleccione una opción:");
            System.out.println("0. Salir");
            System.out.println("1. Insertar clave y valor");
            System.out.println("2. Buscar valor por clave");
            System.out.println("3. Eliminar clave");
            System.out.println("4. Mostrar toda la tabla");
            System.out.println("Ingrese una opción:");
            opcion = sc.nextInt();
            sc.nextLine(); // Limpiar el buffer
            System.out.println();

            // Ejecutar la opción seleccionada
            switch (opcion) {
                case 0:
                    System.out.println("Saliendo...");
                    break;

                case 1:
                    System.out.println("Ingrese la clave:");
                    String key = sc.nextLine();
                    System.out.println("Ingrese el valor:");
                    int value = sc.nextInt();
                    hashTable.insert(key, value); // Insertar clave y valor en la tabla hash
                    break;

                case 2:
                    System.out.println("Ingrese la clave a buscar:");
                    String keyToSearch = sc.nextLine();
                    int searchResult = hashTable.search(keyToSearch); // Buscar valor por clave en la tabla hash
                    if (searchResult != -1) {
                        System.out.println("Valor encontrado: " + searchResult);
                    } else {
                        System.out.println("Clave no encontrada");
                    }
                    break;

                case 3:
                    System.out.println("Ingrese la clave a eliminar:");
                    String keyToDelete = sc.nextLine();
                    hashTable.remove(keyToDelete); // Eliminar clave de la tabla hash
                    break;

                case 4:
                    System.out.println("Tabla hash:");
                    hashTable.printTable(); // Mostrar toda la tabla hash
                    System.out.println();
                    break;

                default:
                    System.out.println("Opción no válida");
                    break;
            }
        } while (opcion != 0); // Repetir hasta que el usuario elija salir
    }
}