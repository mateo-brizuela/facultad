package arbolesBinarios.ArbolAVLPractica;

public class AVLNode {
    private AVLNode left;
    private AVLNode right;
    private AVLNode parent; // padre del nodo
    private int height; // altura del nodo
    private int value; // valor del nodo

    // constructor
    public AVLNode(int value){
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
    public void setLeft(AVLNode left){
        this.left = left;
    }

    public AVLNode getLeft(){
        return left;
    }

    public void setRight(AVLNode right){
        this.right = right;
    }

    public AVLNode getRight(){
        return right;
    }

    public void setValue(int value){
        this.value = value;
    }

    public int getValue(){
        return value;
    }

    public void setHeight(int height){
        this.height = height;
    }

    public int getHeight(){
        return height;
    }
}
