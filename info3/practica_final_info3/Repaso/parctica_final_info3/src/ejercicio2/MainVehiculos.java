package ejercicio2;
import java.util.Scanner;


public class MainVehiculos {
    public static void main(String[] args) {
        Scanner consola = new Scanner(System.in);

        // declaracion de variables
        String entrada1;
        String entrada2;
        int opcion;

        // instancio el auto
        System.out.println("ingrese la marca del auto");
        entrada1 = consola.nextLine();
        System.out.println("ingrese el modelo del auto");
        entrada2 = consola.nextLine();
        Vehiculo auto1 = new Auto(entrada1, entrada2);

        // instancio la moto
        System.out.println("ingrese la marca de la moto");
        entrada1 = consola.nextLine();
        System.out.println("ingrese el modelo de la moto");
        entrada2 = consola.nextLine();
        Vehiculo moto1 = new Moto(entrada1, entrada2);


        do {
            System.out.println("seleccione una opcion");
            System.out.println("0. salir");
            System.out.println("1. acelerar auto");
            System.out.println("2. frenar auto");
            System.out.println("3 mostrar estado auto");
            System.out.println("4. acelerar moto");
            System.out.println("5. frenar moto");
            System.out.println("6. mostrar estado moto");

            opcion = consola.nextInt();

            switch (opcion) {
                case 0:
                    System.out.println("saliendo...");
                    break;

                case 1:
                    System.out.println("ingrese el incremento de velocidad");
                    auto1.acelerar(consola.nextInt());
                    break;

                case 2:
                    System.out.println("ingrese el decremento de velocidad");
                    auto1.frenar(consola.nextInt());
                    break;

                case 3:
                    auto1.mostraEstado();
                    break;

                case 4:
                    System.out.println("ingrese el incremento de velocidad");
                    moto1.acelerar(consola.nextInt());
                    break;
                
                case 5:
                    System.out.println("ingrese el decremento de velocidad");
                    moto1.frenar(consola.nextInt());
                    break;

                case 6:
                    moto1.mostraEstado();
                    break;
            
                default:
                    System.out.println("opcion no valida");
                    break;
            }
        } while (opcion != 0);
        


    }
}
