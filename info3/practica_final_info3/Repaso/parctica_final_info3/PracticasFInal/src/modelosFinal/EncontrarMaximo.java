package modelosFinal;

public class EncontrarMaximo {
    public static int max(int[] vector, int indice, int max){
        // caso base, que el indice consultado este fuera de rango
        if (indice >= vector.length) {
            return max;
        }

        if (max < vector[indice]) {
            max = vector[indice];
        }

        max = max(vector,++indice,max);

        return max;
    }
}
