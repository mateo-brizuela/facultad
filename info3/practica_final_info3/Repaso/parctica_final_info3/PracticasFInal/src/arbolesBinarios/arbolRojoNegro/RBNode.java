package arbolesBinarios.arbolRojoNegro;

public class RBNode {
    private RBNode left;
    private RBNode right;
    private RBNode parent;
    private int value;
    private boolean isRed;

    // constructor
    public RBNode(int value) {
        this.value = value;
        this.isRed = true;
        this.left = null;
        this.right = null;
        this.parent = null;
    }

    // sobrescribir el método toString
    @Override
    public String toString() {
        if (isRed) {
            return "r" + value;
        }else{
            return "b" + value;
        }
    }

    //funciones del nodo
    public boolean leftEmpty() {
        return left == null;
    }

    public boolean rightEmpty() {
        return right == null;
    }

    public void makeBlack() {
        isRed = false;
    }

    public void makeRed() {
        isRed = true;
    }

    // getters y setters

    public RBNode getLeft() {
        return left;
    }

    public void setLeft(RBNode left) {
        this.left = left;
    }

    public RBNode getRight() {
        return right;
    }

    public void setRight(RBNode right) {
        this.right = right;
    }

    public RBNode getParent() {
        return parent;
    }

    public void setParent(RBNode parent) {
        this.parent = parent;
    }

    public int getValue() {
        return value;
    }

    public boolean isRed() {
        return isRed;
    }

    public void setRed(boolean red) {
        isRed = red;
    }
}
