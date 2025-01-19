package Utils.BinaryTree;

public abstract class BinaryTree<T extends TreeNode<T>> {
    private T root;

    public abstract void insert(T node); // particular de cada arbol
    public abstract T delete(); // particular de cada arbol

    // ------------ Metodos comunes ------------
    // Método para imprimir el árbol de forma visual 
    public void printTree(T node, String prefix, boolean isLeft) { // primer llamado: tree.printTree(root, "", false); 
        if (node != null) {
            System.out.println(prefix + (isLeft ? "├── " : "└── ") + node); // para que funciones se debe sobreescribir el metodo toString del nodo empleado
            printTree(node.getLeft(), prefix + (isLeft ? "│   " : "    "), true);
            printTree(node.getRight(), prefix + (isLeft ? "│   " : "    "), false);
        }
    }

    public T findMin(T node) {
        if(node != null){
            while (node.getLeft() != null) {
                node = node.getLeft();
            }
        }
        return node;
    }

    public T searchNode(int data){
        T currentNode = root;
        boolean found = false;

        while(currentNode != null && found == false){
            if(currentNode.getData() == data){
                found = true;
            }
            else{
                if(data > currentNode.getData()){
                    currentNode = currentNode.getRight();
                }
                else{ // data < currentNode.getData()
                    currentNode = currentNode.getLeft();
                }
            }
        }
        if(found == false){
            // ToDo: implementar con excepciones
            System.out.println("ERROR: el valor ingresado no se encuentra en el arbol.\n");
        }

        return(currentNode);
    }
    
    // getters y setters
    public T getRoot(){
        return root;
    }
    public void setRoot(T root){
        this.root = root;
    }
}
