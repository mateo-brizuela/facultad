package arbolesBinarios.arbolAVL;

public class AVLTreeNode {
    private int value; // valor del nodo
    private AVLTreeNode left;
    private AVLTreeNode right; 
    private int height; // altura del nodo

    // constructor
    public AVLTreeNode(int value){
        this.value = value;
        left = null;
        right = null;
        height = 1;
    }

    // sobrescribo el metodo toString para que imprima el valor del nodo
    @Override
    public String toString(){
        return ""+ value;
    }

    // funciones del nodo
    public boolean rightEmpty(){
        return right == null;
    }

    public boolean leftEmpty(){
        return left == null;
    }

    // getters y setters
    public void setLeft(AVLTreeNode left){
        this.left = left;
    }

    public AVLTreeNode getLeft(){
        return left;
    }

    public void setRight(AVLTreeNode right){
        this.right = right;
    }

    public AVLTreeNode getRight(){
        return right;
    }

    public int getValue(){
        return value;
    }

    public void setValue(int value){
        this.value = value;
    }

    public int getHeight(){
        return height;
    }

    public void setHeight(int height){
        this.height = height;
    }

}
