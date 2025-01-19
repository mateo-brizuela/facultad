package Utils.BinaryTree.RedBlackTree;

import Utils.BinaryTree.*;

public class RBNode extends TreeNode<RBNode> {
    private Color color; // rojo o negro

    // constructores
    public RBNode(int data){
        setData(data);
        setColor(Color.RED);
    }
    public RBNode(int data, RBNode parent){
        setData(data);
        setColor(Color.RED);
        setParent(parent);
    }

    @Override
    public String toString() {
        return (getData() + " " + getColor());
    }

    public boolean isRed(){ // devuelve 1 si el nodo es rojo
        return(getColor() == Color.RED);
    }

    public void setColor(Color color){
        this.color = color;
    }
    public Color getColor(){
        return color;
    }
}
