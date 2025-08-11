package ejercicio5;
import java.util.*;

public class Division {
    public static void dividir(double a, double b) throws NumeroNegativoExeption {
        if (b == 0) {
            throw new ArithmeticException("No se puede dividir por cero");
        }
        if (a < 0 || b < 0) {
            throw new NumeroNegativoExeption("No se puede dividir por un numero negativo");
        }
        double resultado = a / b;
        System.out.println(resultado);

    }

    public static void main(String[] args) {
        Scanner consola = new Scanner(System.in);
        double a, b;
        boolean error = false;

        while (!error) {
            try {
                System.out.println("ingrese el numerador");
            } catch (InputMismatchException e) {
    
                System.out.println("Debe ingresar un numero");
                error = true;
            }  catch (NumeroNegativoExeption e) {
                System.out.println("no se permite ingresar numeros negativos");
                e.printStackTrace(System.out);
                error = true;
            } 

        }
        error = false;

        while (!error) {
            System.out.println("ingrese el denominador");
            
        }

        System.out.println("ingrese el numerador");
        a = consola.nextDouble();

        
    }
}
