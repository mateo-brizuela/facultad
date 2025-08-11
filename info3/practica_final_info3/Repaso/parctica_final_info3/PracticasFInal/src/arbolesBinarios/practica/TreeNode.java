package arbolesBinarios.practica;

public class TreeNode {
    private TreeNode left;
    private TreeNode right;
    private int value;

    //constructor
    public TreeNode(){
        left = null;
        right = null;
    }

    public TreeNode(int value){
        this.value = value;
        left = null;
        right = null;
    }

    // sobrescribo el metodo toString para que imprima el valor del nodo
    @Override
    public String toString(){
        return ""+ value;
    }

    // funciones del nodo

    // funcion recursiva que inserta un nuevo nodoen el lugar correspondiente
    public void insertRec(int newNodeValue){
        // caso que el nuevo tenga que ir a la derecha
        if (value < newNodeValue) {
            if (rightEmpty()) {
                right = new TreeNode(newNodeValue);
            }else{
                right.insertRec(newNodeValue);
            }
            // caso que el nuevo nodo tenga que ir a la izquierda
        } else if (value > newNodeValue) {
            if (leftEmpty()) {
                left = new TreeNode(newNodeValue);
            }else{
                left.insertRec(newNodeValue);
            }
            // caso que el nuevo nodo sea igual al actual
        }else{
            System.out.println("no se admiten valores repetidos");
        }
    }


    public boolean rightEmpty(){
        return right == null;
    }

    public boolean leftEmpty(){
        return left == null;
    }

    // getters y setters 
    public TreeNode getLeft() {
        return left;
    }

    public void setLeft(TreeNode left) {
        this.left = left;
    }

    public TreeNode getRight() {
        return right;
    }

    public void setRight(TreeNode right) {
        this.right = right;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

}
