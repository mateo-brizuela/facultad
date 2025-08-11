package ejercicio4;
import java.util.*;

public class MainGenerics {
    public static void main(String[] args) {
        Repositorio<String> nombres = new Repositorio<>();
        Repositorio<Integer> numeros = new Repositorio<>();
        Scanner consola = new Scanner(System.in);
        int opcion;


        do {
            System.out.println("seleccione una opcion");
            System.out.println("0. Salir");
            System.out.println("1. Agregar nombre");
            System.out.println("2. eliminar nobre por indice");
            System.out.println("3. obtener nombre por indice");
            System.out.println("4. mostrar todos los nombres");
            System.out.println("5. Agregar numero");
            System.out.println("6. eliminar numero por indice");
            System.out.println("7. obtener numero por indice");
            System.out.println("8. mostrar todos los numeros");
            opcion = consola.nextInt();
            consola.nextLine(); // tomo el enter

            switch (opcion) {

                case 0:
                    System.out.println("Saliendo...");
                    break;

                case 1:
                    System.out.println("Ingrese un nombre");
                    nombres.agregar(consola.nextLine());
                    System.out.println("Nombre agregado");
                    break;
                
                case 2:
                    System.out.println("Ingrese el indice del nombre a eliminar");
                    nombres.eliminarIndice(consola.nextInt());
                    consola.nextLine(); // tomo el enter
                    System.out.println("Nombre eliminado");
                    break;

                case 3:
                    System.out.println("Ingrese el indice del nombre a obtener");
                    System.out.println(nombres.obtenerIndice(consola.nextInt()));
                    consola.nextLine(); // tomo el enter
                    break;

                case 4:
                    nombres.mostrar();
                    break;

                case 5:
                    System.out.println("Ingrese un numero");
                    numeros.agregar(consola.nextInt());
                    consola.nextLine(); // tomo el enter
                    System.out.println("Numero agregado");
                    break;

                case 6:
                    System.out.println("Ingrese el indice del numero a eliminar");
                    numeros.eliminarIndice(consola.nextInt());
                    consola.nextLine(); // tomo el enter
                    System.out.println("Numero eliminado");
                    break;

                case 7:

                    System.out.println("Ingrese el indice del numero a obtener");
                    System.out.println(numeros.obtenerIndice(consola.nextInt()));
                    consola.nextLine(); // tomo el enter
                    break;

                case 8:

                    numeros.mostrar();
                    break;
            
                default:
                    System.out.println("Opcion no valida");
                    break;
            }
            System.out.println("");
        } while (opcion != 0);
    }
}
