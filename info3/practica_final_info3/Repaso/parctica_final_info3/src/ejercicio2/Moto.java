package ejercicio2;

public class Moto extends Vehiculo {

    // constructor
    public Moto(String marca, String modelo){
        super(marca,modelo);
    }

    @Override
    public void frenar(int decremento) {
        velocidad -= decremento + (decremento * 0.05);
        System.out.println("al ser una moto se reduce un %5 " 
            + "adicional la velocidad");
    }
}
