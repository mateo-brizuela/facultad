package Utils.RecursiveFunctions;

public class PrintReverseArray {


    public static void printReverse(int[] array, int index) {
        // Caso base: si el índice es menor que 0, terminamos la recursión
        if (index < 0) {
            return;
        }
        
        // Imprimir el elemento actual
        System.out.print(array[index] + " ");
        
        // Llamada recursiva con el índice anterior
        printReverse(array, index - 1);
    }
}
