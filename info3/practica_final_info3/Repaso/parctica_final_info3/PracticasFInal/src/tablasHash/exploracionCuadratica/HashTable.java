package tablasHash.exploracionCuadratica;

public class HashTable {
    private HashNode[] table;
    private int size;
    private final HashNode EMPTY = null;

    // constructor
    public HashTable(int size){
        this.size = size;
        table = new HashNode[size];
        for (HashNode hashNode : table) {
            hashNode = EMPTY;
        }
    }

    // funciones
    // genera in indice para la tabla hash a travez de la clave
    public int hash(String key){
        int hash = 0;

        for (char c : key.toCharArray()) {
            hash = (hash * 31 + c) % size;
        }
        return hash;
    }

    public void insert (String key, int value){
        int index = hash(key);
        int startIndex = index;
        int i = 0;

        while (table[index] != EMPTY) {
            if (table[index].getKey().equals(key)) {
                System.out.println("no se permiten calves repetidas en la tabla");
                return;
            }

            i++;
            index = ((index + (i * i))) % size; // se hce la exploracion cuadratica de forma circular

            if (index == startIndex) {
                System.out.println("la tabla esta llena");
                return;
            }

        }

        table[index] = new HashNode(key, value);
    }

    public int search(String key){
        int index = hash(key);
        int startIndex = index;
        int i = 0;

        while (table[index] != EMPTY) {
            if (table[index].getKey().equals(key)) {
                System.out.println("clave encontrada");
                return table[index].getValue();
            }

            i++;
            index = (index + (i * i)) % size; // se hce la exploracion cuadratica de forma circular

            if (index == startIndex) {
                System.out.println("no se encontro un nodo con esa clave");
                return -1;
            }

        }
        System.out.println("hay ningun nodo con esa clave");
        return -1;
    }

    public void remove(String key){
        int index = hash(key);
        int startIndex = index;
        int i = 0;

        while (table[index] != EMPTY) {
            if (table[index].getKey().equals(key)){
                table[index] = EMPTY;
                System.out.println("nodo eliminado");
                return;
            }

            i++;
            index = ((index + (i * i))) % size; // se hce la exploracion cuadratica de forma circular

            if (index == startIndex) {
                System.out.println("no se encontro un nodo con esa clave");
            }

        }
        System.out.println(" no hay ningun nodo con esa clave");
    }

    public void printTable(){
        for (int i = 0; i < size; i++) {
            if (table[i] != EMPTY) {
                System.out.println(i + " :" + table[i].getKey() + " ->" + table[i].getValue());
            }else{
                System.out.println(i + "-> " + "[VACIO]");
            }
        }
    }

}
