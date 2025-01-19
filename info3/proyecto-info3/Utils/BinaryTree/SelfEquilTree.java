package Utils.BinaryTree;

public abstract class SelfEquilTree<T extends TreeNode<T>> extends BinaryTree<T>{
    // rotaciones 
    protected void rotateRightSimple(T pivot){ // recibe el nodo que quedara como raiz del subarbol
        T pivotParent = pivot.getParent();
        T rChild = pivot.getRight();

        if(pivotParent == getRoot()){ // caso 1: el padre de pivot es la raiz
            // actualizar la raiz
            setRoot(pivot);
        }
        else{ // caso 2: el padre de pivot es un nodo comun
            // convertir a pivot en el hijo de su abuelo
            if(pivotParent == pivotParent.getParent().getLeft()){ // pivotParent era hijo izq
                pivotParent.getParent().setLeft(pivot);
            }
            else{ // pivotParent era hijo der
                pivotParent.getParent().setRight(pivot);
            }
        }
        pivot.setParent(pivotParent.getParent()); // si pivotParent == root, pivot pasa a ser la nueva raiz y su padre debe quedar en null
        // convertir al hijo der de pivot en el izq de su abuelo
        if(rChild != null){ // hay un rChild? (puede que no)
            rChild.setParent(pivotParent);
        }
        pivotParent.setLeft(rChild);// si rChild == null sirve lo mismo porque tenemos que limpiar el enlace
        // redefinir relacion entre pivot y su padre
        pivot.setRight(pivotParent);
        pivotParent.setParent(pivot);
    }
    protected void rotateLeftSimple(T pivot){ // recibe el nodo que quedara como raiz del subarbol
        T pivotParent = pivot.getParent();
        T lChild = pivot.getLeft();

        if(pivotParent == getRoot()){ // caso 1: el padre de pivot es la raiz
            // actualizar la raiz
            setRoot(pivot);;
        }
        else{ // caso 2: el padre de pivot es un nodo comun
            // convertir a pivot en el hijo de su abuelo
            if(pivotParent == pivotParent.getParent().getLeft()){ // pivotParent era hijo izq
                pivotParent.getParent().setLeft(pivot);
            }
            else{ // pivotParent era hijo der
                pivotParent.getParent().setRight(pivot);
            }
        }
        pivot.setParent(pivotParent.getParent());  
        // convertir al hijo der de pivot en el izq de su abuelo
        if(lChild != null){ // hay un lChild? (puede que no)
            lChild.setParent(pivotParent);
        }
        pivotParent.setRight(lChild); // si lChild == null sirve lo mismo porque tenemos que limpiar el enlace
        // redefinir relacion entre pivot y su padre
        pivot.setLeft(pivotParent);
        pivotParent.setParent(pivot);
    }
}
