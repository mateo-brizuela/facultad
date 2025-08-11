package pilaListaCola.vectores;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        int opcion;
        
        // instancio las estructuras de datos
        Pila pila = new Pila(10); // creo una pila de 10 elementos
        Cola cola = new Cola(5);


        do {
            System.out.println("seleccione una opcion");
            System.out.println("0) salir");
            System.out.println("1) ingresar un valor a la pila");
            System.out.println("2) sacar un valor de la pila");
            System.out.println("3) mostrar la pila");
            System.out.println("4) limpiar la pila");
            System.out.println("5) ingresar un valor a la cola");
            System.out.println("6) sacar un valor de la cola");
            System.out.println("7) mostrar la cola");

            opcion =  solicitarEntero();
            System.out.println("");

            switch (opcion) {
                case 1:
                    System.out.println("ingrese el elemento de la pila");
                    pila.push(solicitarEntero());
                    break;

                case 2:
                    pila.pop();
                    break;

                case 3:
                    pila.leerVector();
                    break;

                case 4:
                    break;

                case 5:
                    System.out.println("ingrese el nuevo elemento de la cola");
                    cola.enqueue(solicitarEntero());
                    break;

                case 6:
                    cola.dequeue();
                    break;

                case 7:
                    cola.leerVector();
                    break;
            
                default:
                    break;
            }

        } while (opcion != 0);
        

    }

    public static int solicitarEntero(){
        Scanner consola = new Scanner(System.in);
        return consola.nextInt();
    }
}
