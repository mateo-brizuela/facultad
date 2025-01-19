package Utils.BinaryTree.AVLTree;
import Utils.BinaryTree.*;

public class AVLNode extends TreeNode<AVLNode> {
    private int height; // Altura del nodo en el árbol AVL

    @Override
    public String toString() {
        return (getData() + " ");
    }

    // Constructor que inicializa el nodo con el dato y una altura de 1
    public AVLNode(int data) {
        setData(data);
        height = 1;
    }

    // Obtiene la altura del nodo
    public int getHeight() {
        return height;
    }

    // Establece la altura del nodo
    public void setHeight(int height) {
        this.height = height;
    }

    // Calcula el factor de balance del nodo
    public int getBalanceFactor() {
        // el equilibrio se obtiene de restar la altura del hijo izquierdo menos la altura del derecho
        int leftHeight = getLeft() != null ? ((AVLNode) getLeft()).getHeight() : 0;
        int rightHeight = getRight() != null ? ((AVLNode) getRight()).getHeight() : 0;
        return leftHeight - rightHeight; // Retorna la diferencia de alturas
    }

    // Actualiza la altura del nodo en función de la altura de sus hijos
    public void updateHeight() {
        int leftHeight = getLeft() != null ? ((AVLNode) getLeft()).getHeight() : 0;
        int rightHeight = getRight() != null ? ((AVLNode) getRight()).getHeight() : 0;
        height = 1 + Math.max(leftHeight, rightHeight); // La altura es 1 + el máximo de sus hijos
    }
}
