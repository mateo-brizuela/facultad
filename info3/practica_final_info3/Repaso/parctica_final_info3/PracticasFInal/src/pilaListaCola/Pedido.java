package pilaListaCola;

public class Pedido {
    private String nombreCliente;
    private int tiempoPreparacion;
    private int numeroPedido;
    private int precioTotal;
    private Pedido next; // guarda el siguiente pedido de la cola o la pila

    // constructor
    public Pedido(int tiempoPreparacion, int precioTotal, int numeroPedido, String nombreCliente) {
        this.tiempoPreparacion = tiempoPreparacion;
        this.precioTotal = precioTotal;
        this.numeroPedido = numeroPedido;
        this.nombreCliente = nombreCliente;
        next = null;
    }


    // metodo toString
    public String toString() {
        return "Pedido [nombreCliente=" + nombreCliente + ", precioTotal=" + precioTotal + ", tiempoPreparacion="
                + tiempoPreparacion + "]";
    }

    // getters y setters
    public int getTiempoPreparacion() {
        return tiempoPreparacion;
    }

    public void setTiempoPreparacion(int tiempoPreparacion) {
        this.tiempoPreparacion = tiempoPreparacion;
    }

    public int getPrecioTotal() {
        return precioTotal;
    }

    public void setPrecioTotal(int precioTotal) {
        this.precioTotal = precioTotal;
    }

    public String getNombreCliente() {
        return nombreCliente;
    }

    public void setNombreCliente(String nombreCliente) {
        this.nombreCliente = nombreCliente;
    }

    public int getNumeroPedido() {
        return numeroPedido;
    }

    public void setNumeroPedido(int numeroPedido) {
        this.numeroPedido = numeroPedido;
    }

    public Pedido getNext(){
        return next;
    }

    public void setNext(Pedido next){
        this.next = next;
    }
}
