package ejercicio2;

public class Auto extends Vehiculo {

    // constructor
    public Auto(String marca, String modelo){
        super(marca, modelo);
    }

    @Override
    public void acelerar(int incremento) {
        velocidad += incremento + (incremento * 0.1);
        System.out.println("al ser un auto aumenta un 10% mas la velocidad");
    }

}
