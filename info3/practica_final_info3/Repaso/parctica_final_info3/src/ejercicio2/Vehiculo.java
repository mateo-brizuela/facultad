package ejercicio2;

public class Vehiculo {

    protected String marca;
    protected String modelo;
    protected int velocidad;

    // constructor
    public Vehiculo(String marca, String modelo){
        this.marca = marca;
        this.modelo = modelo;
        velocidad = 0;
    }




    // getters y setters

    public String getMarca() {
        return marca;
    }

    public String getModelo() {
        return modelo;
    }

    public int getVelocidad() {
        return velocidad;
    }

    public void setMarca(String marca) {
        this.marca = marca;
    }

    public void setModelo(String modelo) {
        this.modelo = modelo;
    }

    public void setVelocidad(int velocidad) {
        this.velocidad = velocidad;
    }


    // funciones de la clase

    public void acelerar(int incremento){
        velocidad += incremento;
    }

    public void frenar(int decremento){
        velocidad -= decremento;
    }

    public void mostraEstado(){
        System.out.println(marca + " " + modelo + " velocidad: " + velocidad);
    }


}
