package pilaListaCola.vectores;

public abstract class Estructura {
    protected int [] vector; 

    // constructor
    public Estructura(int capacidad){
        vector = new int[capacidad];
    }

    public void leerVector(){
        for (int i = 0; i < vector.length; i++) {
            if (vector[i] != 0) {
                System.out.println(vector[i]);    
            }
        }
    }
}