package pilaListaCola.vectores;

public class Cola extends Estructura {
    private int front; // frente de la cola
    private int end; // final de la cola
    private int size; // cantidad de elementos en la cola

    // constructor
    public Cola(int capacidad){
        super(capacidad);
        front = 0;
        end = -1;
    }

    public void enqueue(int valor){
        if (size == vector.length) {
            System.out.println("la cola esta llena");
            return;
        }

        end = (end + 1) % vector.length; // hago que de forma circular se actualice el final de la cola
        vector[end] = valor;
        size ++;
        System.out.println("se ingreso el valor correctamente");

    }

    public void dequeue(){
        if (vacia()) {
            System.out.println("la cola esta vacia");
            return;
        }
        vector[front] = 0;
        front = (front + 1) % vector.length;
        size--;
        System.out.println("se elimino el elemento correctamente");
    }

    @Override
    public void leerVector(){
        if (vacia()) {
            System.out.println("la cola esta vacia");
            return;
        }

        int j = front;
        for (int i = 0; i < size; i++) {
            System.out.println(vector[j]);
            j = (j + 1) % vector.length; // leo toda la cola de forma circular
        }
    }

    public boolean vacia(){
        return size == 0;
    }
}
