package ordenamiento;

import java.util.ArrayList;

public class Ordenador {

    // incertionSort
    public static void ordenarPorTiempoPreparacion(ArrayList<Pedido> pedidos){
        int n = pedidos.size();
        if (verificarVacio(pedidos)) {
            System.out.println("error: la lista no tiene ningun elemento");
        }else{
            int j;
            for (int i = 0; i < n; i++) {
                Pedido key = pedidos.get(i);

                for (j = i; (j > 0) && (pedidos.get(j - 1).getTiempoPreparacion() > key.getTiempoPreparacion()); j--) {
                     pedidos.set(j, pedidos.get(j - 1)); // voy moviendo los valores mayores al key unlugar hacia adelante
                                                        // asi hago espacio para insertar la key en su lugar correspondiente
                }
                pedidos.set(j, key); // inserto el key
            }
        }

    }

    // shellSort
    public static void ordenarPedidosPorPrecioTotal(ArrayList<Pedido> pedidos){
        int n = pedidos.size();
        if (verificarVacio(pedidos)) {
            System.out.println("error: no hay elementos en la lista");
        }else{
            for (int gap = n/2; gap > 0; gap /= 2) {
                for (int i = gap; i < n; i++) {
                    Pedido key = pedidos.get(i); // clave para comparar con los anteriores
                    int j; // declaro para guardar el indice asi pongo el key en su lugar
                    for ( j = i; (j >= gap) && (pedidos.get(j - gap).getPrecioTotal() > key.getPrecioTotal()) ; j -= gap) {
                        pedidos.set(j, pedidos.get(j - gap));                        
                    }
                    pedidos.set(j, key); // acomodo la key en su lugar correspondiente
                }
            }
        }

    }

    //quickSort
    public static void ordenarPedidosPorNombre(ArrayList<Pedido> pedidos){
        if (verificarVacio(pedidos)) {
            System.out.println("error: no hay elementos en la lista para ordenar");
        }else{
            quickSort(pedidos, 0, pedidos.size() - 1);
        }

    }

    private static void quickSort(ArrayList<Pedido> pedidos, int inicio, int fin){
        if (inicio < fin) {
            int pivote = particion(pedidos, inicio, fin);

            // aplico el algoritmo de forma recursiva
            quickSort(pedidos, inicio, pivote - 1);
            quickSort(pedidos, pivote + 1, fin);
        }

    }

    // esta funcion acomoda todos los elementos menores al pivote al inicio de la lista
    private static int particion(ArrayList<Pedido> pedidos, int inicio, int fin){
        Pedido pivote = pedidos.get(fin);
        int menor = inicio - 1; // guarda el indice con el ultimo elemento menor de la lista

        for (int i = inicio; i < fin; i++) {
            if (pedidos.get(i).getNombreCliente().compareTo(pivote.getNombreCliente()) < 0) {
                //acomodo el elemento menor encontrado luego del penultimo elemento menor encontrado
                //dejando todos los elementos menores al pivote al inicio de la lista
                Pedido aux = pedidos.get(i);
                pedidos.set(i, pedidos.get(menor + 1));
                pedidos.set(menor + 1, aux);
                menor++;
            }
        }
        
        // acomodo al pivote en su posicion correcta
        pedidos.set(fin, pedidos.get(menor + 1));
        pedidos.set(menor + 1, pivote);

        // retorno el indice donde se encuentra el pivote
        return menor + 1;
    }

    private static boolean verificarVacio(ArrayList<Pedido> pedidos){
        return pedidos.size() == 0;
    }


}