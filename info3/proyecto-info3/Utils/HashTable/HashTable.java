package Utils.HashTable;
//PARA EVITAR LAS COLICIONES HEMOS UTILIZADO HASHING ENLAZADO

public class HashTable <K, V> {
//atributos
private HashNode<K, V>[] buckets;//Tabla formada por los elementos
private int numBuckets; // Tamaño del array de buckets
private int size; // Número de elementos en la tabla

//constructor
@SuppressWarnings("unchecked")
public HashTable() {
    numBuckets = 10; //Tamaño de la tabla
    buckets = new HashNode[numBuckets];
    size = 0;
}

//getters para el size del Bucket
public int getBucketsSize() {
    return buckets.length;
}

//Metodos
// Función hash que acepta cadenas y números, devuelve el indice donde va a estar guardado el valor
private int hash(K key) {
    if (key instanceof Integer) {
        // Para enteros, devuelve x % tamañoTabla
        return Math.abs((Integer) key % buckets.length);//nos aseguramos q no de numero negativo
    } else if (key instanceof String) {
        // Para cadenas, utiliza la función de hash proporcionada
        return hash_chain((String) key, buckets.length);
    } else {
        // Si el tipo de clave no es soportado, lanzar excepción
        throw new IllegalArgumentException("Tipo de clave no soportado");
    }
}

// Función hash para cadenas
public static int hash_chain(String key, int tableSize) {
    int hashVal = 0;
    for (int i = 0; i < key.length(); i++) {
        hashVal = (hashVal * 128 + key.charAt(i)) % tableSize;
    }
    return hashVal;
}

// Método para insertar un valor
public void put(K key, V value) {
    int index = hash(key); // Calcula el índice con la función hash

    HashNode<K, V> newNode = new HashNode<>(key, value); // Crear un nuevo nodo

    if (buckets[index] == null) {
        // Si el bucket está vacío, colocar el nuevo nodo
        buckets[index] = newNode;
    } else {
        // Manejar colisiones usando una lista enlazada
        HashNode<K, V> current = buckets[index];

        // Recorrer la lista hasta el final
        while (current.next != null) {
            current = current.next; // Ir al siguiente nodo
        }
        // Agregar el nuevo nodo al final de la lista enlazada
        current.next = newNode;
    }
    size++; // Incrementar el tamaño de la tabla hash
}


 // Método para obtener todos los valores en un bucket
 public void printBucket(int index) {
    HashNode<K, V> current = buckets[index];
    if (current == null) {
        System.out.println(index + ": está vacío.");
        return;
    }

    System.out.print(index + ": ");
    while (current != null) {
        System.out.printf("[Clave: %s, Valor: %s] ", current.key, current.value);
        current = current.next;
    }
    System.out.println();
    }

 // Método para buscar un elemento en la tabla hash por su clave
 public V search_element(K key) {
    int index = hash(key); // Calcula el índice usando la función hash
    HashNode<K, V> current = buckets[index];

    // Buscar en la lista enlazada en el bucket correspondiente
    while (current != null) {
        if (current.key.equals(key)) {
            return current.value; // Retorna el valor si la clave es encontrada
        }
        current = current.next; // Continuar buscando en el siguiente nodo
    }

    return null; // Si no se encuentra la clave, devuelve null
}

//Método para eliminar un elemento en la tabla hash por su clave
public void remove(K key) {
    // Calcular el índice en la tabla
    int index = hash(key);

    // Acceder al bucket correspondiente
    HashNode<K, V> current = buckets[index];
    HashNode<K, V> previous = null;

    // Recorrer la lista enlazada del bucket
    while (current != null) {
        // Si encontramos el nodo con la clave, lo eliminamos
        if (current.key.equals(key)) {
            if (previous == null) {
                // Si el nodo es el primero en la lista (head), lo eliminamos
                buckets[index] = current.next;
            } else {
                // Si el nodo está en medio o al final, lo eliminamos
                previous.next = current.next;
            }
            size--; // Decrementar el tamaño de la tabla
            System.out.println("Elemento con clave '" + key + "' eliminado.");
            return;
        }
        previous = current; // Avanzar al siguiente nodo
        current = current.next;
    }

    // Si no encontramos el nodo, informamos que no se ha encontrado
    System.out.println("Elemento con clave '" + key + "' no encontrado.");
}
}
