package pilaListaCola;

public class ColaPedidos {
    private Pedido front;
    private Pedido back;

    // constructor vacio
    public ColaPedidos(){
        front = null;
        back = null;
    }

    public void enqueue(Pedido nuevoPedido){
        if (isEmpty()) {
            front = back = nuevoPedido;
        } else{
            back.setNext(nuevoPedido); // agrego el nuevo nodo
            back = back.getNext();  // lo pongo como el back
        }
    }

    public void dequeue(){
        if (isEmpty()) {
            System.out.println("no hay elementos en la cola");  
            return;
        }

        front = front.getNext(); // elimino el el primer elemento ingresado en la lista
    }

    public void mostrarPedidos(){
        Pedido aux = front;
        while (aux != null) {
            System.out.println(aux);
            aux = aux.getNext();
        }
    }

    public Pedido top(){
        return front;
    }

    public boolean isEmpty(){
        return front == null;
    }
    
}
