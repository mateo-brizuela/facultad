package Utils.BinaryHeap;

public class BinaryHeap{
//atributos
    private static final int default_capacity=100;
    private int CurrentSize;
    private Integer[] array;

//constructor
public BinaryHeap() {
    CurrentSize = 0;
    this.array = new Integer[default_capacity+1];
}

//Metodos   

//Imprimir
public void printHeap() {
    for (int i = 1; i <= CurrentSize; i++) {
        System.out.print(array[i] + " ");
    }
    System.out.println("\n");
}

//Insertar
public void insert(Integer x) {
    if (CurrentSize + 1 == array.length) {
        duplicateArray();
    }

    int hueco = ++CurrentSize; // Incrementa el tamaño y establece la posición del nuevo elemento
    array[0]=x;
//Ajustar la posicion del nuevo elemento en el monticulo
    for(; comparate(x, array[hueco/2])<0; hueco/=2){
        array[hueco] = array[hueco/2];//mueve padre abajo si el nuevo elemento es menor
    }
    array[hueco]=x;
}

//Comparar dos Integer
private int comparate(Integer a, Integer b) {
    // Verifica que ambos enteros no sean nulos
    if (a == null || b == null) {
        throw new IllegalArgumentException("Los enteros no pueden ser nulos");
    }
    // Utiliza el método compareTo de Integer para comparar
    return a.compareTo(b);
}

//Duplicar (funcion por si sobrepasa el maximo)
private void duplicateArray() {
    // Crea un nuevo array con el doble de tamaño
    Integer[] nuevoArray =new Integer [array.length * 2];
    
    // Copia los elementos del array original al nuevo array
    for (int i = 1; i <= CurrentSize; i++) {
        nuevoArray[i] = array[i];
    }
    
    // Asigna el nuevo array al campo del array original
    array = nuevoArray;
    }

//Eliminar menor
public Integer eliminateMin() {
    if (CurrentSize == 0) {
        throw new IllegalStateException("El montículo está vacío.");
    }

    Integer elMinimo = array[1]; // Guarda el mínimo (raíz)
    array[1] = array[CurrentSize--]; // Reemplaza la raíz con el último elemento
    percolateDown(1); // Reestructura el montículo
    return elMinimo; // Devuelve el mínimo extraído
}

//Reorganiza el monticulo de la eliminacion
private void percolateDown (int hueco){
int hijo;
Integer tmp = array[hueco];

for(; hueco*2 <= CurrentSize; hueco = hijo){
    hijo=hueco*2;
    if (hijo != CurrentSize && comparate(array[hijo+1], array[hijo])<0) {
        hijo++;
    }
    if(comparate(array[hijo], tmp)<0){
        array[hueco]=array[hijo];
    }
    else
        break;
    }
array[hueco]=tmp;
}

}