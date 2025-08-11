package ordenamiento;
import java.util.*;
import static ordenamiento.Ordenador.ordenarPorTiempoPreparacion;
import static ordenamiento.Ordenador.ordenarPedidosPorPrecioTotal;
import static ordenamiento.Ordenador.ordenarPedidosPorNombre;

public class MainPizzeria {
    public static void main(String[] args) {
        Scanner consola = new Scanner(System.in);
        ArrayList<Pedido> pedidos = new ArrayList<Pedido>();
        int opcion;

        // variables temporales
        String nombreCliente;
        int tiempoPreparacion;
        int precioTotal;
        int numeroPedido;
        int opcion2; // e una opcion para seleccionar enmenus dentro del menu
        boolean encontrado; // se utiliza para saber si se encontro el pedido buscado en algun proceso

        // cargo elementos a la lista por codigo, para probar las funiones mas rapido
        Pedido pedido1 = new Pedido(60, 100, generarNumeroPedido(pedidos), "Mateo");
        Pedido pedido2 = new Pedido(45, 120, generarNumeroPedido(pedidos), "Lucia");
        Pedido pedido3 = new Pedido(50, 200, generarNumeroPedido(pedidos), "Mauro");
        Pedido pedido4 = new Pedido(20, 80, generarNumeroPedido(pedidos), "Lina");
        Pedido pedido5 = new Pedido(15, 145, generarNumeroPedido(pedidos), "Julia");

        pedidos.add(pedido1);
        pedidos.add(pedido2);
        pedidos.add(pedido3);
        pedidos.add(pedido4);
        pedidos.add(pedido5);

        do{
            System.out.println("seleccione una opcion");
            System.out.println("0) salir");
            System.out.println("1) agregar pedido");
            System.out.println("2) eliminar pedido");
            System.out.println("3) actualizar pedido");
            System.out.println("4) mostrar pedidos");
            System.out.println("5) ordenar pedidos por tiempo de preparacion");
            System.out.println("6) ordenar pedidos por precio total");
            System.out.println("7) ordenar pedidos por nombre del cliente(alfabeticamente)");
            opcion = consola.nextInt();
            consola.nextLine(); // limpiar el buffer

            switch(opcion){
                case 1:
                    System.out.println("ingrese el nombre del cliente");
                    nombreCliente = consola.nextLine();
                    System.out.println("ingrese el precio total");
                    precioTotal = consola.nextInt();
                    System.out.println("ingrese el tiempo de preparacion");
                    tiempoPreparacion = consola.nextInt();
                    Pedido nuevoPedido = new Pedido(tiempoPreparacion, precioTotal, generarNumeroPedido(pedidos), nombreCliente);
                    pedidos.add(nuevoPedido); // se ingresa el nuevo pedidoa la lista
                    break;

                case 2:
                    encontrado = false;
                    System.out.println("ingrese el numero del pedido a eliminar");
                    numeroPedido = consola.nextInt();

                    for (Pedido pedido : pedidos) {
                        if (pedido.getNumeroPedido() == numeroPedido) {
                            encontrado = true;
                            pedidos.remove(pedido);
                            System.out.println("se elimino el pedido");
                        }
                    }

                    if (!encontrado) {
                        System.out.println("no se encontro un pedido con ese numero");
                    }
                    break;

                
                case 3:
                    encontrado = false;
                    System.out.println("ingrese el numero de pedido a modificar");
                    numeroPedido = consola.nextInt();

                    for (Pedido pedido : pedidos) {
                        if (pedido.getNumeroPedido() == numeroPedido) {
                            encontrado = true;
                            System.out.println("pedido encontrado");
                            System.out.println("seleccione la variable a modificar");
                            System.out.println("1) tiempo de preparacion");
                            System.out.println("2) precio total");
                            opcion2 = consola.nextInt();

                            switch (opcion2) {
                                case 1:
                                    System.out.println("ingrese el nuevo tiempo de preparacion");
                                    pedido.setTiempoPreparacion(consola.nextInt());
                                    break;

                                case 2:
                                    System.out.println("ingrese el nuevo precio total");
                                    pedido.setPrecioTotal(consola.nextInt());
                                    break;
                            
                                default:
                                    break;
                            }
                        }
                    }

                    if (!encontrado) {
                        System.out.println("no se encontro un pedido con ese numero");
                    }
                    break;

                case 4:
                    mostrarPedidos(pedidos);
                    break;

                case 5:
                    ordenarPorTiempoPreparacion(pedidos);
                    break;

                case 6:
                    ordenarPedidosPorPrecioTotal(pedidos);
                    break;

                case 7:
                    ordenarPedidosPorNombre(pedidos);
                    break;
                    
                
                

            }            
        } while (opcion != 0);
    }

    public static void mostrarPedidos(ArrayList<Pedido> pedidos){
        for (Pedido pedido : pedidos) {
            System.out.println(pedido);
        }
    }

    public static int generarNumeroPedido(ArrayList<Pedido> pedidos){
        return pedidos.size() + 1;
    }
}
