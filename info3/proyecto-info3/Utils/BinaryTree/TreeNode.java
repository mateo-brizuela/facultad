package Utils.BinaryTree;

public class TreeNode<T extends TreeNode<T>> {
    // ------------------ Atributos ------------------
    private int data; // dato guardado en el nodo
    // conexiones entre nodos
    private T parent; // nodo padre
    private T right; // nodo hijo derecho
    private T left; // nodo hijo izquierdo

    // ------------------ Metodos ------------------
    public boolean rightEmpty(){ // devuelve 1 si no tiene hijo der.
        return(getRight() == null);
    }
    public boolean leftEmpty(){ // devuelve 1 si no tiene hijo izq.
        return(getLeft() == null);
    }
    public boolean isTerminal(){ // devuelve 1 si el nodo es terminal
        return(getRight() == null && getLeft() == null);
    }

    // setters y getters
    public void setData(int data){
        this.data = data;
    }
    public void setParent(T parent){
        this.parent = parent;
    }
    public void setRight(T right){
        this.right = right;
    }
    public void setLeft(T left){
        this.left = left;
    }

    public int getData(){
        return data;
    }
    public T getParent(){
        return parent;
    }
    public T getRight(){
        return right;
    }
    public T getLeft(){
        return left;
    }
}
