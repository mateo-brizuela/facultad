package pilaListaCola.vectores;
import java.util.*;

public class Pila extends Estructura{ // heredo de la clase abstracta Estructura
    private int top;

    // constructor
    public Pila(int capacidad){
        super(capacidad);
        top = -1; // si es -1 significa que la pila esta vacia
    }

    public void push(int valor){
        if (top == vector.length - 1) {
            System.out.println("la pila esta llena");
            return;
        }
        vector[++top] = valor;
        System.out.println("valor ingresado");

    }

    public void pop(){
        if (vacia(top)) {
            System.out.println("la pila esta vacia");
            return;
        }

        top--;
    }

    public boolean vacia(int top){
        return top == -1;
    }
}
