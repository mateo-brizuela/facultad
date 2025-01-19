package Utils.BinaryTree.SearchTree;
import java.util.NoSuchElementException;
import Utils.BinaryTree.BinaryTree;

public class SearchTree extends BinaryTree<SearchNode> {
    // Atributo root heredado de BinaryTree<SearchNode>

    // Constructor
    public SearchTree() {
        setRoot(null);
    }

    // Método para insertar un nodo (no permite duplicados)
    public SearchNode insert(int value, SearchNode node) {
        if (node == null) {
            // Si el árbol está vacío, crea un nuevo nodo con el value
            node = new SearchNode(value);
        } else if (value < node.getData()) {
            node.setLeft(insert(value, node.getLeft()));
        } else if (value > node.getData()) {
            node.setRight(insert(value, node.getRight()));
        }
        return node;
    }

    // Método para insertar un nodo (permite duplicados)
    public SearchNode insert_duplicate(int value, SearchNode node) {
        if (node == null) {
            // Si el árbol está vacío, crea un nuevo nodo con el value
            node = new SearchNode(value);
        } else if (value < node.getData()) {
            // Si el value es menor, se inserta en el subárbol izquierdo
            node.setLeft(insert_duplicate(value, node.getLeft()));
        } else {
            // Si el value es mayor o igual, se inserta en el subárbol derecho (permitiendo duplicados)
            node.setRight(insert_duplicate(value, node.getRight()));
        }
        return node; // Retorna la raíz del árbol modificado
    }

    // Método para recorrer el árbol en inorden (izquierda, raíz, derecha)
    public void inOrden(SearchNode node) {
        if (node != null) {
            inOrden(node.getLeft());
            System.out.print(node.getData() + " ");
            inOrden(node.getRight());
        }
    }

    // Método para calcular la profundidad del árbol
    public int depth(SearchNode node) {
        if (node == null) { // Caso base
            return 0; // Si el árbol está vacío, la profundidad es 0
        } else {
            // Llamado recursivo
            if (depth(node.getLeft()) > depth(node.getRight())) {
                return depth(node.getLeft()) + 1; // Si el izquierdo es más profundo, sumamos 1
            } else {
                return depth(node.getRight()) + 1; // Si el derecho es más profundo o igual, sumamos 1
            }
        }
    }

    // Método para eliminar el nodo mínimo en el subárbol dado
    // El mínimo siempre está a la izquierda del árbol
    SearchNode eliminateMin(SearchNode node) {
    if (node == null) {
        throw new NoSuchElementException("El árbol está vacío.");
    } else if (node.getLeft() != null) {
        node.setLeft(eliminateMin(node.getLeft()));
        return node;
    } else {
        return node.getRight();
    }
}

    // Método para eliminar un nodo específico en el árbol
    public SearchNode dtree(SearchNode node, int value) {
        if (node == null) { // Caso base: si el árbol está vacío
            System.out.println("El valor " + value + " no se encuentra en el árbol.");
            return node;
        }
        // Caso recursivo: busca el nodo a eliminar
        if (value < node.getData()) {
            node.setLeft(dtree(node.getLeft(), value)); // Buscar en el subárbol izquierdo
        } else if (value > node.getData()) {
            node.setRight(dtree(node.getRight(), value)); // Buscar en el subárbol derecho

            // Nodo encontrado
            // Caso 1: Nodo con dos hijos
        } else if (node.getLeft() != null && node.getRight() != null) {
            node.setData(findMin(node.getRight()).getData()); // Reemplaza el valor por el mínimo del subárbol derecho
            node.setRight(eliminateMin(node.getRight())); // Elimina el nodo mínimo del subárbol derecho
        } else {
            // Caso 2: Nodo con uno o ningún hijo
            node = (node.getLeft() != null) ? node.getLeft() : node.getRight(); // Reemplaza el nodo por su único hijo o null
        }
        return node;
    }

    // Métodos abstractos heredados de BinaryTree que deben implementarse
    @Override
    public void insert(SearchNode node) {
        setRoot(insert(node.getData(), getRoot()));
    }

    @Override
    public SearchNode delete() {
        // Implementación específica si es necesaria
        return null;
    }
}
