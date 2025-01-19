package Utils.BinaryTree.AVLTree;

import Utils.BinaryTree.*;

public class AVLTree extends BinaryTree<AVLNode> {

    // Método para insertar un nodo en el árbol AVL
    @Override
    public void insert(AVLNode node) {
        setRoot(insertRec(getRoot(), node)); // Inserta el nodo recursivamente y actualiza la raíz
    }

    // Método delete() abstracto de BinaryTree no implementado
    // ademas si no se especifica el valor dispara una exception
    @Override
    public AVLNode delete() {
        throw new UnsupportedOperationException("Use delete(int data) para eliminar un nodo específico.");
    }

    // Método para eliminar un nodo específico dado un valor
    public boolean delete(int data) {
        AVLNode nodeToDelete = searchNode(data); // Busca el nodo
        if (nodeToDelete == null) {
            return false; // Retorna falso si el nodo no existe
        } else {
            setRoot(deleteRec(getRoot(), data)); // Elimina el nodo recursivamente y actualiza la raíz
            return true; // Retorna verdadero si el nodo fue eliminado
        }
    }

    // Método recursivo de eliminación
    private AVLNode deleteRec(AVLNode current, int data) {
        if (current == null) {
            return null; // Nodo no encontrado
        }

        // Compara el valor para encontrar el nodo
        if (data < current.getData()) {
            current.setLeft(deleteRec(current.getLeft(), data)); // Busca en el subárbol izquierdo
        } else if (data > current.getData()) {
            current.setRight(deleteRec(current.getRight(), data)); // Busca en el subárbol derecho
        } else {
            // Caso en que el nodo tiene solo un hijo o ninguno
            if (current.getLeft() == null || current.getRight() == null) {
                return (current.getLeft() != null) ? current.getLeft() : current.getRight();
            }
            // Caso con dos hijos: encuentra el nodo mínimo del subárbol derecho
            AVLNode minLargerNode = findMin(current.getRight());
            current.setData(minLargerNode.getData());
            current.setRight(deleteRec(current.getRight(), minLargerNode.getData())); // Elimina el nodo mínimo
        }

        current.updateHeight(); // Actualiza la altura del nodo
        return balance(current); // Balancea el árbol a partir del nodo actual
    }

    // Método recursivo para insertar un nodo
    private AVLNode insertRec(AVLNode current, AVLNode node) {
        // caso base, el nodo esta en la posicion correcta
        if (current == null) {
            return node; // Inserta el nodo en la posición correcta
        }
        // el nodo debe insertarce en el hijo izquierdo
        if (node.getData() < current.getData()) {
            current.setLeft(insertRec(current.getLeft(), node)); // se llama recursivamente la funcion en el hijo izquierdo
            current.getLeft().setParent(current); // se establece la relacion padre hijo 
        } else if (node.getData() > current.getData()) {
            current.setRight(insertRec(current.getRight(), node));
            current.getRight().setParent(current);
        } else {
            return current; // Si el nodo ya existe, no se inserta
        }

        // se actualiza la altura de todos los nodos desde el nodo incertado hacia la raiz
        current.updateHeight(); // Actualiza la altura después de la inserción
        return balance(current); // Balancea el árbol a partir del nodo actual
    }

    // Balanceo del nodo para mantener las propiedades del árbol AVL
    private AVLNode balance(AVLNode node) {
        int balanceFactor = node.getBalanceFactor();
        if (balanceFactor > 1) { // Caso de desbalance a la izquierda
            if (node.getLeft().getBalanceFactor() < 0) {
                node.setLeft(rotateLeftSimple(node.getLeft())); // Rotación izquierda del hijo izquierdo
            }
            node = rotateRightSimple(node); // Rotación derecha

        } else if (balanceFactor < -1) { // Caso de desbalance a la derecha
            if (node.getRight().getBalanceFactor() > 0) {
                node.setRight(rotateRightSimple(node.getRight())); // Rotación derecha del hijo derecho
            }
            node = rotateLeftSimple(node); // Rotación izquierda
        }
        return node;
    }

    // Rotación simple a la derecha para balancear el árbol
    private AVLNode rotateRightSimple(AVLNode pivotParent) {
        AVLNode pivot = pivotParent.getLeft();
        AVLNode rChild = pivot.getRight();

        if (pivotParent == getRoot()) {
            setRoot(pivot);
            pivot.setParent(null);
        } else {
            AVLNode grandParent = pivotParent.getParent();
            if (grandParent != null) {
                if (pivotParent == grandParent.getLeft()) {
                    grandParent.setLeft(pivot);
                } else {
                    grandParent.setRight(pivot);
                }
            }
            pivot.setParent(grandParent);
        }

        pivotParent.setLeft(rChild);
        if (rChild != null) {
            rChild.setParent(pivotParent);
        }

        pivot.setRight(pivotParent);
        pivotParent.setParent(pivot);

        return pivot;
    }

    // Rotación simple a la izquierda para balancear el árbol
    private AVLNode rotateLeftSimple(AVLNode pivotParent) {
        AVLNode pivot = pivotParent.getRight();
        AVLNode lChild = pivot.getLeft();

        if (pivotParent == getRoot()) {
            setRoot(pivot);
            pivot.setParent(null);
        } else {
            AVLNode grandParent = pivotParent.getParent();
            if (grandParent != null) {
                if (pivotParent == grandParent.getLeft()) {
                    grandParent.setLeft(pivot);
                } else {
                    grandParent.setRight(pivot);
                }
            }
            pivot.setParent(grandParent);
        }

        pivotParent.setRight(lChild);
        if (lChild != null) {
            lChild.setParent(pivotParent);
        }

        pivot.setLeft(pivotParent);
        pivotParent.setParent(pivot);

        return pivot;
    }
}
