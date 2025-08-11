package ejercicio1;
import java.util.Scanner;


public class MainRectangulo {
    public static void main(String[] args) {
        Scanner consola = new Scanner(System.in);
        double base;
        double altura;

        System.out.println("ingrese la base del rectangulo");
        base = consola.nextDouble();
        consola.nextLine();

        System.out.println("ingresa la altura del rectangulo");
        altura = consola.nextDouble();
        consola.nextLine();

        Rectangulo rectangulo1 = new Rectangulo(base, altura);

        rectangulo1.calcularArea();
        rectangulo1.calcularPerimetro();

    }
}
