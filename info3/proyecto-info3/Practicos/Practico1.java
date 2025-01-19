package Practicos;

import static Utils.RecursiveFunctions.CalculatePower.power;
import static Utils.RecursiveFunctions.Countdown.doCountdown;
import static Utils.RecursiveFunctions.GetFactorial.factorial;
import static Utils.RecursiveFunctions.OnesInBinary.CountOnes;
import static Utils.RecursiveFunctions.PrintReverseArray.printReverse;
import static Utils.RecursiveFunctions.RecursiveMultiplication.multiplication;
import static Utils.RecursiveFunctions.AddInteger.add;

public class Practico1 {
    public static void main(String[] args) {
        System.out.println("/////////////// Ejercicio 1 ///////////////");
        // Ejercicio 1: Calcular el factorial de un número
        int num = 5;
        int result;
        result = factorial(num);
        System.out.println("factorial de " + num + " es " + result);
        System.out.println("");


        System.out.println("/////////////// Ejercicio 2 ///////////////");
        // Ejercicio 2: Sumar los primeros números hasta un valor dado
        num = 5;
        result = add(num, 1);
        System.out.println("El resultado de sumar los primeros " + num + " números es " + result);
        System.out.println("");

        System.out.println("/////////////// Ejercicio 3 ///////////////");
        // Ejercicio 3: Calcular una potencia de base y exponente dados
        int base = 2;
        int exponent = 4;
        result = power(base, exponent);
        System.out.println("Potencia de base " + base + " y exponente " + exponent + " es " + result);
        System.out.println("");



        System.out.println("/////////////// Ejercicio 4 ///////////////");
        // Ejercicio 4: Realizar un conteo regresivo desde un número dado
        int n = 4;
        System.out.print("Conteo regresivo desde " + n + ": ");
        doCountdown(n);
        System.out.println("");
        System.out.println("");



        System.out.println("/////////////// Ejercicio 5 ///////////////");
        // Ejercicio 5: Multiplicación recursiva de dos números
        int a = 2;
        int b = 4;
        result = multiplication(a, b);
        System.out.println("El producto de " + a + " y " + b + " es " + result);
        System.out.println("");



        System.out.println("/////////////// Ejercicio 6 ///////////////");
        // Ejercicio 6: Imprimir un arreglo en orden inverso
        int[] array = {1, 2, 3, 4, 5};
        System.out.println("Elementos del array en orden inverso:");
        printReverse(array, array.length - 1);
        System.out.println("");
        System.out.println("");

        

        System.out.println("/////////////// Ejercicio 7 ///////////////");
        // Ejercicio 7: Contar el número de unos en la representación binaria de un número
        num = 13;
        int numOfOnes = CountOnes(num);
        System.out.println("El número de unos en la representación binaria de " + num + " es: " + numOfOnes);
        System.out.println("");
    }
}
