package practicos;
import java.util.*;
import static recursividad.FactorialNumero.CalcularFactorial;
import static recursividad.SumaNumerosNaturales.sumarNaturales;
import static recursividad.SucesionFibonacci.fibonacci;
import static recursividad.InvertirCadena.invertiString;
import static recursividad.CalcularPotencia.potencia;

public class practico1 {
    public static void main(String[] args) {
        Scanner consola = new Scanner(System.in);
        int numero;

        // funcion factorial
        System.out.println("Ingrese un numero para calcular su factorial: ");
        numero = consola.nextInt();
        System.out.println("El factorial de " + numero + " es: " + CalcularFactorial(numero));


        // sumar n numeros naturales
        System.out.println("Ingrese un numero para sumar los primeros n numeros naturales: ");
        numero = consola.nextInt();
        System.out.println("La suma de los primeros " + numero + " numeros naturales es: " + sumarNaturales(numero));

        // sucesion fibonacci
        System.out.println("Ingrese un numero para calcular la sucesion de fibonacci: ");
        numero = consola.nextInt();
        consola.nextLine();
        System.out.println("El numero de la sucesion de fibonacci en la posicion " + numero + " es: " + fibonacci(numero));

        // invertir cadena de caracteres
        System.out.println("Ingrese una cadena de caracteres para invertirla: ");
        String cadena = consola.nextLine();
        System.out.println("La cadena invertida es: " + invertiString(cadena));

        // calcular potencia
        System.out.println("Ingrese la base para calcular la potencia: ");
        int base = consola.nextInt();
        System.out.println("Ingrese el exponente para calcular la potencia: ");
        int exponente = consola.nextInt();
        System.out.println("El resultado de elevar " + base + " a la " + exponente + " es: " + potencia(base, exponente));




    }
}
