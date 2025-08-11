package tablasHash.exploracionLineal;

public class HashTable {
    private HashNode[] table;
    private int size;
    private final HashNode EMPTY = null;

    //constructor 
    // iicializa la tabla hash con elementos null
    public HashTable(int size){
        this.size = size;
        this.table = new HashNode[size];
        for (HashNode hashNode : table) {
            hashNode = null;
        }
    }

    // funcion hash
    private int hashFunction(String key){
        int hash = 0;
        for (char c : key.toCharArray()) {
            hash = (hash * 31 + c) % size;
        }
        return hash; // retorna el indice generado por la funcion hash
    }

    //insertar clave valor sin claves repetidas
    public void insert(String key, int value){
        int index = hashFunction(key); // se genera el indice
        int startIndex = index; // se guarda el indice que se genero inicialmente

        while (table[index] != EMPTY) { // exploracion lineal
            // caso de que la clave sea identica a una generada anteriormente
            if (table[index].getKey().equals(key)) {
                System.out.println("error: no se permiten claves repetidas");
                return;
            }
            index = (index + 1) % size; // va incrementandose de manera circular el indice 

            if (index == startIndex) {
                System.out.println("error:la tabla hash esta llena");
                return;
            }
        }
        table[index] = new HashNode(key, value); // se asigna el nuevo nodo
    }

    // a esta funcion le pasas una clave, y te retorna su valor asociado
    public int search(String key){
        int index = hashFunction(key);
        int startIndex = index;

        while (table[index] != EMPTY) {
            if (table[index].getKey().equals(key)) { // si la calve del indice consultado es igual a la clave
                return table[index].getValue();
            }
            index = (index + 1) % size;

            if (index == startIndex) {
                break;
            }
        }
        return -1; // clave no encontrada
    }

    public void delete(String key){
        int index = hashFunction(key);
        int startIndex = index;

        while (table[index] != EMPTY) {
            if (table[index].getKey().equals(key)) { // si la calve del indice consultado es igual a la clave
                table[index] = EMPTY;
            }
            index = (index + 1) % size;

            if (index == startIndex) {
                System.out.println("no se encontro un nodo con esa clave");
            }
        }
    }

    // muestra la tabla entera
    public void printTable(){
        for (int i = 0; i < size; i++) {
            if (table[i] != EMPTY) {
                System.out.println(i + ": " + table[i].getKey() + " ->" + table[i].getValue());
            }else{
                System.out.println(i + ": [VACIO]");
            }
        }
    }


}
