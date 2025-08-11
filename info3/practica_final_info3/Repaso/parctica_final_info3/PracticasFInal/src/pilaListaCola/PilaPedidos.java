package pilaListaCola;

public class PilaPedidos {
    private Pedido topOfStack; // el tope de la pila

    // constructor vacio
    public PilaPedidos(){
        topOfStack = null;
    }

    public void push(Pedido nuevoPedido){
        if (isEmpty()) {
            topOfStack = nuevoPedido;
        }else{
            nuevoPedido.setNext(topOfStack);
            topOfStack = nuevoPedido;
        }
    }

    public void pop(){
        topOfStack = topOfStack.getNext();
    }

    public Pedido top(){
        return topOfStack;
    }

    public void mostrarPedidos(){
        Pedido aux = topOfStack;
        while (aux != null) {
            System.out.println(aux);
            aux = aux.getNext();
        }
    }

    public void makeEmpty(){
        topOfStack = null;
    }
    
    public boolean isEmpty(){
        return topOfStack == null;
    }
}
