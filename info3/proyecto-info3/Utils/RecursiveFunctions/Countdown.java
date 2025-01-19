package Utils.RecursiveFunctions;

public class Countdown {


    public static void doCountdown(int n) {
        if (n < 1) {
            return; // Caso base: detener la recursión cuando n es menor a 1
        }
        
        System.out.print(n + (n > 1 ? ", " : "")); // Imprime el número y agrega una coma si no es el último
        doCountdown(n - 1); // Llamada recursiva con n reducido en 1
    }
}
