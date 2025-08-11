package pilaListaCola;
import java.util.Scanner;

public class Main {
    private static int contadorPedidos = 0; // Variable estática para contar los pedidos

    public static void main(String[] args) {
        Scanner consola = new Scanner(System.in);
        ColaPedidos pendientes = new ColaPedidos();
        PilaPedidos procesados = new PilaPedidos();
        int opcion = 0;

        do {
            menu();
            opcion = solicitarInt(consola);

            switch (opcion) {
                case 1:
                    Pedido nuevoPedido = insertarPedido(consola);
                    pendientes.enqueue(nuevoPedido);
                    break;

                case 2:
                    if (pendientes.isEmpty()) {
                        System.out.println("No hay pedidos pendientes");
                    } else {
                        Pedido pedidoProcesar = pendientes.top();
                        pendientes.dequeue();
                        procesados.push(pedidoProcesar);
                    }
                    break;

                case 3:
                    pendientes.mostrarPedidos();
                    break;

                case 4:
                    procesados.mostrarPedidos();
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

    public static void menu() {
        System.out.println("Seleccione una opción:");
        System.out.println("0) Salir");
        System.out.println("1) Agregar pedido");
        System.out.println("2) Eliminar pedido");
        System.out.println("3) Mostrar pedidos pendientes");
        System.out.println("4) Mostrar pedidos procesados");
    }

    public static int solicitarInt(Scanner consola) {
        System.out.print("Ingrese una opción: ");
        return consola.nextInt();
    }

    public static Pedido insertarPedido(Scanner consola) {
        consola.nextLine(); // Limpiar el buffer
        System.out.println("Ingrese el nombre del cliente: ");
        String nombre = consola.nextLine();
        System.out.println("Ingrese el precio total del pedido: ");
        int precio = consola.nextInt();
        System.out.println("Ingrese el tiempo de preparación del pedido: ");
        int tiempo = consola.nextInt();
        return new Pedido(tiempo, precio, generarNumeroPedido(), nombre);
    }

    public static int generarNumeroPedido() {
        return ++contadorPedidos; // Incrementa y retorna el contador de pedidos
    }
}
