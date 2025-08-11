package arbolesBinarios.practica;

public class BinarySearchTree {
    private TreeNode root; // raiz del arbol

    // constructor
    public BinarySearchTree(){
        root = null;
    }

    // funcion que inserta un nuevo nodo
    public void insert(int value){
        if (isEmpty()) {
            root = new TreeNode(value); // si el arbol esta vacio se crea la raiz
        }else{
            root.insertRec(value); // si tiene raiz se llama la funcion recursiva
        }
    }

    public void insert2(int value){
        root = insertRec2(root, value);
    }

    public TreeNode insertRec2(TreeNode currentNode, int value){
        // si se llega a un nodo nulo se crea un nuevo nodo
        if (currentNode == null) {
            currentNode = new TreeNode(value);
        // si el valor es menor al del nodo actual se llama la funcion recursiva con el subarbol izquierdo
        } else if (value < currentNode.getValue()) {
            currentNode.setLeft(insertRec2(currentNode.getLeft(), value));
        // si el valor es mayor al del nodo actual se llama la funcion recursiva con el subarbol derecho
        } else if (value > currentNode.getValue()) {
            currentNode.setRight(insertRec2(currentNode.getRight(), value));
        } else {
            System.out.println("no se admiten valores repetidos");
        }

        return currentNode;
    }

    public void printInOrder(TreeNode currentNode){
        if (isEmpty()) {
            System.out.println("el arbol esta vacio");
            return;
        }

        // imprimo el subarbol izquierdo
        if (!currentNode.leftEmpty()) {
            printInOrder(currentNode.getLeft());
        }
        
        // imprimo el nodo actual
        System.out.println(currentNode);

        // imprimo el subarbol derecho
        if (!currentNode.rightEmpty()) {
            printInOrder(currentNode.getRight());
        }

    }

    public boolean isEmpty(){
        return root == null;
    }

    // getters y setters
    public TreeNode getRoot() {
        return root;
    }

    public void setRoot(TreeNode root) {
        this.root = root;
    }

}
