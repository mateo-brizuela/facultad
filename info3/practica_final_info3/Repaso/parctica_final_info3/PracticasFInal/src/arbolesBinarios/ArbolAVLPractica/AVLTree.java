package arbolesBinarios.ArbolAVLPractica;

public class AVLTree {
    private AVLNode root;

    // Constructor
    public AVLTree() {
        root = null;
    }

    // funcines del arbol

    private int getBalance(AVLNode node){
        return height(node.getLeft()) - height(node.getRight());
    }

    // obtiene la altura de un nodo
    public int height(AVLNode node){
        return (node == null) ? 0 : node.getHeight();
    }

    // actualiza la altura de un nodo
    public void updateHeight(AVLNode node){
        node.setHeight(1 + Math.max(height(node.getLeft()), height(node.getRight())));
    }

    public void insert(int value){
        root = insertRec(root, value);
    }

    // rotaciones

    private AVLNode rightRotate(AVLNode father){
        AVLNode newFather = father.getLeft();
        father.setLeft(newFather.getRight()); // asigno el subarbol temporal al padre antiguo
        newFather.setRight(father);

        // actualizar alturas 
        updateHeight(father);
        updateHeight(newFather);

        // se retorna el nuevo nodo raiz o nodo padre
        return newFather;
    }

    private AVLNode leftRotate(AVLNode father){
        AVLNode newFather = father.getRight();
        father.setRight(newFather.getLeft()); // cuelgo el subarbol temporal  al padre antiguo
        newFather.setLeft(father);

        // actualizo las alturas
        updateHeight(father);
        updateHeight(newFather);

        // retorno el nuevo padre
        return newFather;
    }

    public AVLNode insertRec(AVLNode currentNode, int value){
        // inserto el nuevo nodo normalmente como BST
        if (currentNode == null) {
            return new AVLNode(value); // genero el nuevo nodo cuando encuentro un lugar vacio en el arbol
        }

        // se va asignado recursivamente la nueva estructura del arbol incluyendo el nuevo nodo
        if (value < currentNode.getValue()) {
            currentNode.setLeft(insertRec(currentNode.getLeft(), value));
        }else if (value > currentNode.getValue()) {
            currentNode.setRight(insertRec(currentNode.getRight(), value));
        }else{
            return currentNode; // no se permiten duplicados
        }

        // actualizo la altura desde el nodo ancestro hasta la raiz, si hay un desbalance en el arbol se corrige con rotaciones
        
        // se actualiza la altura del nodo ancestro
        updateHeight(currentNode);

        int balance = getBalance(currentNode);

        // Si el nodo se desbalanceó, hay 4 casos

        // Caso Izquierda Izquierda
        if (balance > 1 && getBalance(currentNode.getLeft()) >= 0) {
            return rightRotate(currentNode);
        }

        // Caso Izquierda Derecha
        if (balance > 1 && getBalance(currentNode.getLeft()) < 0) {
            currentNode.setLeft(leftRotate(currentNode.getLeft()));
            return rightRotate(currentNode);
        }

        // Caso Derecha Derecha
        if (balance < -1 && getBalance(currentNode.getRight()) <= 0) {
            return leftRotate(currentNode);
        }

        // Caso Derecha Izquierda
        if (balance < -1 && getBalance(currentNode.getRight()) > 0) {
            currentNode.setRight(rightRotate(currentNode.getRight()));
            return leftRotate(currentNode);
        }

        // Retornar el nodo (sin cambios)
        return currentNode;
        
    }


    public void searchToRemove(int value){
        root = removeRec(root, value);
    }

    public AVLNode removeRec(AVLNode currentNode, int value){
        // se elimina el arbol como BST
        // caso de que el nodo consultado es nulo
        if (currentNode == null) {
            return currentNode;
        }

        if (value < currentNode.getValue()) {
            currentNode.setLeft(removeRec(currentNode.getLeft(), value));
        }else if (value > currentNode.getValue()) {
            currentNode.setRight(removeRec(currentNode.getRight(), value));
        }else{ // nodo enocntrado
            // caso 1: nodos sin hijos
            if (currentNode.leftEmpty() && currentNode.rightEmpty()) {
                currentNode = null; 
                // caso 2: nodo con un hijo
            }else if (currentNode.leftEmpty() || currentNode.rightEmpty()) {
                if (currentNode.leftEmpty()) {
                    currentNode = currentNode.getRight();
                }else{
                    currentNode = currentNode. getLeft();
                }
                // caso nodo con 3 hijos
            }else{
                AVLNode sucessor = findMin(currentNode.getRight());
                currentNode.setValue(sucessor.getValue());
                currentNode.setRight(removeRec(currentNode.getRight(), currentNode.getValue()));
            }
        }

        // caso en el que la eliminacion del nodo haya dado un nodo nulo
        if (currentNode == null) {
            return currentNode;
        }

        // se actualiza la altura del nodo ancestro
        updateHeight(currentNode);

        int balance = getBalance(currentNode);

        // rotaciones en caso de desbalance

        //rotacion simple hacia la derecha
        if (balance > 1 && getBalance(currentNode.getLeft()) >= 0) {
            return rightRotate(currentNode);
        }

        //rotacion doble a la derecha
        if (balance > 1 && getBalance(currentNode.getLeft()) < 0) {
            currentNode.setLeft(leftRotate(currentNode.getLeft()));
            return rightRotate(currentNode);
        }

        // rotacion simple a la izquierda
        if (balance < -1  && getBalance(currentNode.getRight()) <= 0) {
            return leftRotate(currentNode);
        }

        // rotacion doble hacia la izquierda
        if (balance < -1 && getBalance(currentNode.getRight()) > 0) {
            currentNode.setRight(rightRotate(currentNode.getRight()));
            return leftRotate(currentNode);
        }

        // caso que se devuelve el nodo sin cambios 
        return currentNode;
    }


    public AVLNode findMin(AVLNode currentNode){
        if (currentNode == null) {
            return null;
        }

        if (currentNode.leftEmpty()) {
            return currentNode;
        }else{
            return findMin(currentNode.getLeft());
        }
    }


    // funciones de impresion
    public void printInOrder(AVLNode currentNode){
        if (currentNode == null) {
            return;
        }

        printInOrder(currentNode.getLeft());
        System.out.println(currentNode);
        printInOrder(currentNode.getRight());
    }

    public void printInOrder(){
        printInOrder(root);
    }


    // Imprimir la estructura del árbol
    public void printTree(AVLNode node, String prefix, boolean isLeft) {
        if (node != null) {
            System.out.println(prefix + (isLeft ? "├── " : "└── ") + node.getValue());
            printTree(node.getLeft(), prefix + (isLeft ? "│   " : "    "), true);
            printTree(node.getRight(), prefix + (isLeft ? "│   " : "    "), false);
        }
    }

    // Sobrecargar el método printTree para imprimir desde la raíz
    public void printTree() {
        if (root == null) {
            System.out.println("El árbol está vacío");
        } else {
            printTree(root, "", true);
        }
    }
}
