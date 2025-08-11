package arbolesBinarios.arbolRojoNegro.ia;

class RBTree {
    private RBNode root;

    public RBTree() {
        root = null;
    }

    // Método público para insertar un valor
    public void insert(int value) {
        RBNode nuevo = insertBST(root, value);
        if (root == null) {
            root = nuevo; // Si el árbol estaba vacío, el nuevo nodo es la raíz
        }
        if (nuevo != null) { // Solo balancear si se insertó un nuevo nodo
            balanceInsertion(nuevo);
        }
    }

    // Inserción normal de BST
    private RBNode insertBST(RBNode currentNode, int value) {
        if (currentNode == null) {
            return new RBNode(value);
        }

        if (value < currentNode.value) {
            RBNode temp = insertBST(currentNode.left, value);
            if (temp != null) {
                currentNode.left = temp;
                temp.parent = currentNode;
            }
        } else if (value > currentNode.value) {
            RBNode temp = insertBST(currentNode.right, value);
            if (temp != null) {
                currentNode.right = temp;
                temp.parent = currentNode;
            }
        }
        return currentNode;
    }

    // Balanceo del árbol después de la inserción
    private void balanceInsertion(RBNode node) {
        while (node.parent != null && node.parent.isRed) { // Mientras el padre sea rojo
            RBNode grandfather = node.parent.parent;

            if (node.parent == grandfather.left) { // Caso en subárbol izquierdo
                RBNode uncle = grandfather.right;
                if (uncle != null && uncle.isRed) { // Caso 1: Recoloración
                    node.parent.makeBlack();
                    uncle.makeBlack();
                    grandfather.makeRed();
                    node = grandfather;
                } else { 
                    if (node == node.parent.right) { // Caso 2: Rotación izquierda
                        node = node.parent;
                        leftRotate(node);
                    }
                    // Caso 3: Rotación derecha
                    node.parent.makeBlack();
                    grandfather.makeRed();
                    rightRotate(grandfather);
                }
            } else { // Caso en subárbol derecho (simétrico)
                RBNode uncle = grandfather.left;
                if (uncle != null && uncle.isRed) { // Caso 1: Recoloración
                    node.parent.makeBlack();
                    uncle.makeBlack();
                    grandfather.makeRed();
                    node = grandfather;
                } else { 
                    if (node == node.parent.left) { // Caso 2: Rotación derecha
                        node = node.parent;
                        rightRotate(node);
                    }
                    // Caso 3: Rotación izquierda
                    node.parent.makeBlack();
                    grandfather.makeRed();
                    leftRotate(grandfather);
                }
            }
        }
        root.makeBlack(); // La raíz siempre debe ser negra
    }

    // Rotación a la izquierda
    private void leftRotate(RBNode node) {
        RBNode temp = node.right;
        node.right = temp.left;
        if (temp.left != null) {
            temp.left.parent = node;
        }
        temp.parent = node.parent;
        if (node.parent == null) {
            root = temp;
        } else if (node == node.parent.left) {
            node.parent.left = temp;
        } else {
            node.parent.right = temp;
        }
        temp.left = node;
        node.parent = temp;
    }

    // Rotación a la derecha
    private void rightRotate(RBNode node) {
        RBNode temp = node.left;
        node.left = temp.right;
        if (temp.right != null) {
            temp.right.parent = node;
        }
        temp.parent = node.parent;
        if (node.parent == null) {
            root = temp;
        } else if (node == node.parent.right) {
            node.parent.right = temp;
        } else {
            node.parent.left = temp;
        }
        temp.right = node;
        node.parent = temp;
    }

    // Método para imprimir el árbol en orden
    public void printInOrder() {
        printInOrder(root);
        System.out.println();
    }

    public void printInOrder(RBNode node) {
        if (node != null) {
            printInOrder(node.left);
            System.out.print(node + " ");
            printInOrder(node.right);
        }
    }

    // Método para visualizar la estructura del árbol
    public void printTree() {
        printTree(root, "", true);
    }

    public void printTree(RBNode node, String prefix, boolean isLeft) {
        if (node != null) {
            System.out.println(prefix + (isLeft ? "├── " : "└── ") + node);
            printTree(node.left, prefix + (isLeft ? "│   " : "    "), true);
            printTree(node.right, prefix + (isLeft ? "│   " : "    "), false);
        }
    }

    // getter y setter de la raíz

    public void setRoot(RBNode root) {
        this.root = root;
    }

    public RBNode getRoot() {
        return root;
    }
}
