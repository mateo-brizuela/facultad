package ordenamiento.practicaVectores;

public class Ordenador {

    public static void insertionSort(int [] vector){
        int n = vector.length;
        if (n == 0) {
            System.out.println("error: el vector no tiene ningun elemento");
        }else{
            int j;
            for (int i = 0; i < vector.length; i++) {
                int key = vector[i];
                for (j = i ;(j > 0) && (vector[j-1] >= key); j--) {
                    vector[j] = vector[j - 1];
                }
                vector[j] = key;
            }
        }
    }


    public static void shellSort(int [] vector){
        int n = vector.length;
        if (n == 0) {
            System.out.println("error: el vector no tiene ningun elemento");
        }else{
            for (int gap = n / 2; gap > 0; gap /= 2) {
                for (int i = gap; i < n; i++) {
                    int temp = vector[i];
                    int j;
                    for (j = i; j >= gap && vector[j - gap] > temp; j -= gap) {
                        vector[j] = vector[j - gap];
                    }
                    vector[j] = temp;
                }
            }
        }
    }

    public static void quickSort(int [] vector, int inicio, int fin){
        
        // caso base 
        if (inicio < fin) { // tengo un arreglo de cero o 1 elementos y se considera ordenado
            int pivote = particionar(vector, inicio, fin);
            // se aplica el algoritmo de forma recursiva
            quickSort(vector, inicio, pivote - 1);
            quickSort(vector, pivote + 1, fin);
        }

    }

    // acomoda el pivote en su lugar correspondiente y retorna el indice que lo contiene
    private static int particionar(int[] vector, int inicio, int fin){
        int pivote = vector[fin];
        int menor = inicio -1; // guarda el indice con el ultimo elemento menor encontrado

        // recorre el vector desde el inicio, dejando los elementos menores al pivote a la izquierda
        for (int i = inicio; i < fin; i++) {
            if (vector[i] <= pivote) {
                int temp = vector[i];
                vector[i] = vector[menor + 1];
                vector[menor + 1] = temp;
                menor++; 
            }
        }

        // acomodo el pivote en la posicion correcta
        vector[fin] = vector[menor + 1];
        vector[menor + 1] = pivote;
        return menor + 1;


    }

}
