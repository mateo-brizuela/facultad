package Utils.BinaryTree.SearchTree;
import Utils.BinaryTree.*;

public class SearchNode extends TreeNode<SearchNode> {
    
    // ------------------ Constructor ------------------
    public SearchNode(int data) {
        setData(data); // Almacena el valor en el atributo 'data' de TreeNode
        setLeft(null); // Inicializa left en null (opcional)
        setRight(null); // Inicializa right en null (opcional)
    }

    // ------------------ Métodos ------------------
    @Override
    public String toString() {
        return "" + getData();
    }
}
