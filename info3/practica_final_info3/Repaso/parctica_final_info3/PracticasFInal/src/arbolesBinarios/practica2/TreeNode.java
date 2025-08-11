package arbolesBinarios.practica2;

public class TreeNode {
    private TreeNode left;
    private TreeNode right;
    private TreeNode parent;
    private int value;

    // Constructor por defecto
    public TreeNode(){
        left = null;
        right = null;
        parent = null;
    }

    // Constructor con valor
    public TreeNode(int value){
        this.value = value;
        left = null;
        right = null;
        parent = null;
    }

    // Constructor con valor y padre
    public TreeNode(int value, TreeNode parent){
        this.value = value;
        left = null;
        right = null;
        this.parent = parent;
    }

    // Sobrescribir el método toString
    public String toString(){
        return "" + value;
    }

    // Funciones del nodo
    public boolean rightEmpty(){
        return right == null;
    }

    public boolean leftEmpty(){
        return left == null;
    }

    // Preguntar si el nodo actual es el hijo izquierdo del padre
    public boolean isLeftChild(){
        if (getParent() == null) {
            return false; // En caso de que se pregunte en el nodo raíz
        }
        return this == getParent().getLeft();
    }

    // Getters y setters 
    public void setLeft(TreeNode left){
        this.left = left;
    }

    public TreeNode getLeft(){
        return left;
    }

    public void setRight(TreeNode right){
        this.right = right;
    }

    public TreeNode getRight(){
        return right;
    }

    public void setValue(int value){
        this.value = value;
    }

    public int getValue(){
        return value;
    }

    public void setParent(TreeNode parent){
        this.parent = parent;
    }

    public TreeNode getParent(){
        return parent;
    }
}
