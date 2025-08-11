package arbolesBinarios.arbolAVL;

public class AVLTree {
    private AVLTreeNode root;

    // Constructor
    public AVLTree() {
        root = null;
    }

    // Obtener la altura de un nodo
    private int height(AVLTreeNode node) {
        return node == null ? 0 : node.getHeight();
    }

    // Actualizar la altura de un nodo
    private void updateHeight(AVLTreeNode node) {
        node.setHeight(1 + Math.max(height(node.getLeft()), height(node.getRight())));
    }

    // Obtener el factor de balanceo de un nodo
    private int getBalance(AVLTreeNode node) {
        return node == null ? 0 : height(node.getLeft()) - height(node.getRight());
    }

    // Rotación a la derecha
    private AVLTreeNode rightRotate(AVLTreeNode y) {
        AVLTreeNode x = y.getLeft();
        AVLTreeNode T2 = x.getRight();

        // Realizar rotación
        x.setRight(y);
        y.setLeft(T2);

        // Actualizar alturas
        updateHeight(y);
        updateHeight(x);

        return x; // Nueva raíz del subárbol
    }

    // Rotación a la izquierda
    private AVLTreeNode leftRotate(AVLTreeNode x) {
        AVLTreeNode y = x.getRight();
        AVLTreeNode T2 = y.getLeft();

        // Realizar rotación
        y.setLeft(x);
        x.setRight(T2);

        // Actualizar alturas
        updateHeight(x);
        updateHeight(y);

        return y; // Nueva raíz del subárbol
    }

    // Insertar un nodo en el árbol AVL
    public void insert(int value) {
        root = insertRec(root, value);
    }

    private AVLTreeNode insertRec(AVLTreeNode node, int value) {
        // 1. Realizar la inserción normal en BST
        if (node == null) {
            return new AVLTreeNode(value);
        }

        if (value < node.getValue()) {
            node.setLeft(insertRec(node.getLeft(), value));
        } else if (value > node.getValue()) {
            node.setRight(insertRec(node.getRight(), value));
        } else {
            return node; // No se permiten valores duplicados
        }

        // 2. Actualizar la altura de este nodo ancestro
        updateHeight(node);

        // 3. Obtener el factor de balanceo de este nodo ancestro para verificar si se desbalanceó
        int balance = getBalance(node);

        // Si el nodo se desbalanceó, hay 4 casos

        // Caso Izquierda Izquierda
        if (balance > 1 && value < node.getLeft().getValue()) {
            return rightRotate(node);
        }

        // Caso Derecha Derecha
        if (balance < -1 && value > node.getRight().getValue()) {
            return leftRotate(node);
        }

        // Caso Izquierda Derecha
        if (balance > 1 && value > node.getLeft().getValue()) {
            node.setLeft(leftRotate(node.getLeft()));
            return rightRotate(node);
        }

        // Caso Derecha Izquierda
        if (balance < -1 && value < node.getRight().getValue()) {
            node.setRight(rightRotate(node.getRight()));
            return leftRotate(node);
        }

        // Retornar el nodo (sin cambios)
        return node;
    }

    // Buscar y eliminar un nodo con un valor dado
    public void searchToRemove(int value) {
        root = RemoveRec(root, value);
    }

    private AVLTreeNode RemoveRec(AVLTreeNode node, int value) {
        // 1. Realizar la eliminación normal en BST
        if (node == null) {
            return node;
        }

        if (value < node.getValue()) {
            node.setLeft(RemoveRec(node.getLeft(), value));
        } else if (value > node.getValue()) {
            node.setRight(RemoveRec(node.getRight(), value));
        } else {
            // caso 1: nodo sin hijos 
            if (node.leftEmpty() && node.rightEmpty()) {
                node = null;
                // caso 2: nodo con un hijo
            }else if (node.leftEmpty() || node.rightEmpty()) {
                if (node.leftEmpty()) {
                    node = node.getRight();
                } else {
                    node = node.getLeft();
                }
                // caso 3: nodo con 2 hijos
            } else {
                AVLTreeNode sucessor = findMin(node.getRight());
                // se copia el valor del sucesor en el nodo actual
                node.setValue(sucessor.getValue());
                // se elimina el nodo sucesor
                node.setRight(RemoveRec(node.getRight(), sucessor.getValue()));
                
            }

        }

        // Si el árbol tenía solo un nodo, retornar
        if (node == null) {
            return node;
        }

        // 2. Actualizar la altura de este nodo ancestro
        updateHeight(node);

        // 3. Obtener el factor de balanceo de este nodo ancestro para verificar si se desbalanceó
        int balance = getBalance(node);

        // Si el nodo se desbalanceó, hay 4 casos

        // Caso Izquierda Izquierda
        if (balance > 1 && getBalance(node.getLeft()) >= 0) {
            return rightRotate(node);
        }

        // Caso Izquierda Derecha
        if (balance > 1 && getBalance(node.getLeft()) < 0) {
            node.setLeft(leftRotate(node.getLeft()));
            return rightRotate(node);
        }

        // Caso Derecha Derecha
        if (balance < -1 && getBalance(node.getRight()) <= 0) {
            return leftRotate(node);
        }

        // Caso Derecha Izquierda
        if (balance < -1 && getBalance(node.getRight()) > 0) {
            node.setRight(rightRotate(node.getRight()));
            return leftRotate(node);
        }

        return node;
    }

    // Encontrar el nodo con el valor mínimo en un subárbol
    public AVLTreeNode findMin(AVLTreeNode node) {
        if (node.leftEmpty()) {
            return node;
        } else {
            return findMin(node.getLeft());
        }
    }

    // Imprimir el árbol en orden
    public void printInOrder() {
        printInOrderRec(root);
    }

    private void printInOrderRec(AVLTreeNode node) {
        if (node != null) {
            printInOrderRec(node.getLeft());
            System.out.print(node.getValue() + " ");
            printInOrderRec(node.getRight());
        }
    }

    // Imprimir la estructura del árbol
    public void printTree(AVLTreeNode node, String prefix, boolean isLeft) {
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
