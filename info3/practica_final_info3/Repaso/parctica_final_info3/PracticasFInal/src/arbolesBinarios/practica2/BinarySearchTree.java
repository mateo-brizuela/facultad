package arbolesBinarios.practica2;
import java.util.*;

public class BinarySearchTree {
    private TreeNode root; // Raíz del árbol

    // Constructor
    public BinarySearchTree(){
        root = null;
    }

    // Insertar un nuevo nodo con un valor dado
    public void insert(int value){
        root = insertRec(null, root, value);
    }

    // Sobrecargar el método insert para leer el valor del usuario
    public void insert(){
        Scanner sc = new Scanner(System.in);
        System.out.println("Ingrese el valor del nuevo nodo:");
        int value = sc.nextInt();
        insert(value);
    }

    // Método recursivo para insertar un nuevo nodo
    public TreeNode insertRec(TreeNode parent, TreeNode currentNode, int value){
        if (currentNode == null) {
            // Crear un nuevo nodo si se encuentra un espacio vacío
            currentNode = new TreeNode(value, parent);
        } else if (value < currentNode.getValue()) {
            // Insertar en el subárbol izquierdo si el valor es menor
            currentNode.setLeft(insertRec(currentNode, currentNode.getLeft(), value));
        } else if (value > currentNode.getValue()) {
            // Insertar en el subárbol derecho si el valor es mayor
            currentNode.setRight(insertRec(currentNode, currentNode.getRight(), value));
        }
        return currentNode;
    }

    // Buscar y eliminar un nodo con un valor dado
    public void searchToRemove(TreeNode currentNode, int value){
        if (isEmpty()) {
            System.out.println("El árbol está vacío");
            return;
        }

        if (currentNode == null) {
            System.out.println("Nodo no encontrado");
            return;
        }

        // Caso base: nodo a eliminar encontrado
        if (currentNode.getValue() == value) {
            removeNode(currentNode);
        } else if (value < currentNode.getValue()) {
            searchToRemove(currentNode.getLeft(), value);
        } else if (value > currentNode.getValue()) {
            searchToRemove(currentNode.getRight(), value);
        }
    }

    // Sobrecargar el método searchToRemove para leer el valor del usuario
    public void searchToRemove() {
        Scanner sc = new Scanner(System.in);
        System.out.println("Ingrese el valor del nodo a eliminar:");
        int value = sc.nextInt();
        searchToRemove(root, value);
    }

    // Eliminar un nodo del árbol
    public void removeNode(TreeNode currentNode) {
        TreeNode parent = currentNode.getParent();

        // Caso 1: nodo sin hijos
        if (currentNode.rightEmpty() && currentNode.leftEmpty()) {
            if (parent == null) {
                root = null; // Si es la raíz
            } else if (currentNode.isLeftChild()) {
                parent.setLeft(null);
            } else {
                parent.setRight(null);
            }
        // Caso 2: nodo con un hijo
        } else if (currentNode.rightEmpty() || currentNode.leftEmpty()) {
            TreeNode child = currentNode.leftEmpty() ? currentNode.getRight() : currentNode.getLeft();
            if (parent == null) {
                root = child; // Si es la raíz
            } else if (currentNode.isLeftChild()) {
                parent.setLeft(child);
            } else {
                parent.setRight(child);
            }
            child.setParent(parent);
        // Caso 3: nodo con dos hijos
        } else {
            TreeNode successor = findMin(currentNode.getRight());
            currentNode.setValue(successor.getValue());
            removeNode(successor);
        }
    }

    // Encontrar el nodo con el valor mínimo en un subárbol
    public TreeNode findMin(TreeNode currentNode){
        if (currentNode.leftEmpty()){
            return currentNode;
        } else {
            return findMin(currentNode.getLeft());
        }
    }

    // Imprimir la estructura del árbol
    public void printTree(TreeNode node, String prefix, boolean isLeft) {
        if (node != null) {
            System.out.println(prefix + (isLeft ? "├── " : "└── ") + node.getValue());
            printTree(node.getLeft(), prefix + (isLeft ? "│   " : "    "), true);
            printTree(node.getRight(), prefix + (isLeft ? "│   " : "    "), false);
        }
    }

    // Sobrecargar el método printTree para imprimir desde la raíz
    public void printTree() {
        if (isEmpty()) {
            System.out.println("El árbol está vacío");
        } else {
            printTree(root, "", true);
        }
    }

    // Imprimir el árbol en orden
    public void printInOrder(TreeNode currentNode){
        if (isEmpty()) {
            System.out.println("El árbol está vacío");
            return;
        }

        if (!currentNode.leftEmpty()) {
            printInOrder(currentNode.getLeft());
        }

        System.out.println(currentNode);

        if (!currentNode.rightEmpty()) {
            printInOrder(currentNode.getRight());
        }
    }

    // Verificar si el árbol está vacío
    public boolean isEmpty(){
        return root == null;
    }

    // Getters y setters
    public void setRoot(TreeNode root){
        this.root = root;
    }

    public TreeNode getRoot(){
        return root;
    }
}
