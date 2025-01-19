package Utils.HashTable;

public class HashNode <K, V> {
    K key;
    V value;
    HashNode<K, V> next;

public HashNode(K key, V value) {
    this.key = key;
    this.value = value;
    this.next = null; // Inicialmente, el siguiente nodo es null
}

}
