package arbolesBinarios.arbolRojoNegro;

public class RBTree {
    private RBNode root;

    // Constructor
    public RBTree() {
        root = null;
    }

    // Insertar un nodo en el árbol Rojo-Negro
    public void insert(int value) {
        RBNode node = new RBNode(value);

        // Declaro dos variables RBNode para recorrer el árbol siempre teniendo en cuenta el nodo padre
        RBNode backNode = null;
        RBNode currentNode = root;

        // Recorro el árbol para encontrar la posición correcta del nuevo nodo
        while (currentNode != null) {
            backNode = currentNode;
            if (value < currentNode.getValue()) {
                currentNode = currentNode.getLeft();
            } else if (value > currentNode.getValue()) {
                currentNode = currentNode.getRight();
            } else {
                System.out.println("No se permiten valores duplicados");
                return;
            }
        }

        node.setParent(backNode); // Establezco el padre del nuevo nodo
        if (backNode == null) { // Caso de que el nuevo nodo tenga que ser la raíz
            root = node;
        } else if (value < backNode.getValue()) {
            backNode.setLeft(node);
        } else {
            backNode.setRight(node);
        }

        // Se arregla el árbol si alguna de sus propiedades fue violada
        if (node.getParent() == null) {
            node.makeBlack();
            return;
        }

        if (node.getParent().getParent() == null) {
            return;
        }

        fixInsert(node);
    }

    // Balancear la inserción en el árbol Rojo-Negro
    public void fixInsert(RBNode node) {
        while (node.getParent() != null && node.getParent().isRed()) { // El bucle se repite mientras el padre sea un nodo rojo
            RBNode grandfather = node.getParent().getParent();
            if (node.getParent() == grandfather.getLeft()) { // Caso subárbol izquierdo
                RBNode uncle = grandfather.getRight(); // Encuentro al tío
                // Caso 1: recoloración
                if (uncle != null && uncle.isRed()) {
                    node.getParent().makeBlack();
                    uncle.makeBlack();
                    grandfather.makeRed();
                    node = grandfather; // Paso el caso al abuelo
                } else {
                    // Caso 2: rotación derecha
                    if (node == node.getParent().getRight()) {
                        node = node.getParent();
                        leftRotate(node);
                    }
                    // Caso 3: rotación izquierda
                    node.getParent().makeBlack();
                    grandfather.makeRed();
                    rightRotate(grandfather); // Hago una rotación derecha desde el abuelo
                }
            } else { // Caso subárbol derecho
                RBNode uncle = grandfather.getLeft(); // Encuentro al tío
                // Caso 1: recoloración
                if (uncle != null && uncle.isRed()) {
                    node.getParent().makeBlack();
                    uncle.makeBlack();
                    grandfather.makeRed();
                    node = grandfather; // Paso el caso al abuelo
                } else {
                    // Caso 2: rotación derecha
                    if (node == node.getParent().getLeft()) {
                        node = node.getParent();
                        rightRotate(node);
                    }
                    // Caso 3: rotación izquierda
                    node.getParent().makeBlack();
                    grandfather.makeRed();
                    leftRotate(grandfather); // Hago la rotación izquierda
                }
            }
        }
        root.makeBlack(); // La raíz siempre es negra
    }

    // Rotación a la izquierda
    public void leftRotate(RBNode node) {
        RBNode newFather = node.getRight();
        node.setRight(newFather.getLeft());

        if (newFather.getLeft() != null) {
            newFather.getLeft().setParent(node);
        }

        newFather.setParent(node.getParent());
        // Caso que el nodo antiguo sea la raíz
        if (node.getParent() == null) {
            root = newFather;
        // Caso de que el nodo antiguo sea hijo izquierdo
        } else if (node == node.getParent().getLeft()) {
            node.getParent().setLeft(newFather);
        // Caso de que el nodo antiguo sea hijo derecho
        } else {
            node.getParent().setRight(newFather);
        }

        newFather.setLeft(node);
        node.setParent(newFather);
    }

    // Rotación a la derecha
    public void rightRotate(RBNode node) {
        RBNode newFather = node.getLeft();
        node.setLeft(newFather.getRight());

        if (newFather.getRight() != null) {
            newFather.getRight().setParent(node);
        }

        newFather.setParent(node.getParent());
        // Caso que el nodo antiguo sea la raíz
        if (node.getParent() == null) {
            root = newFather;
        // Caso de que el nodo antiguo sea hijo izquierdo
        } else if (node == node.getParent().getLeft()) {
            node.getParent().setLeft(newFather);
        // Caso de que el nodo antiguo sea hijo derecho
        } else {
            node.getParent().setRight(newFather);
        }

        newFather.setRight(node);
        node.setParent(newFather);
    }

    // Imprimir el árbol en orden
    public void printInOrder(RBNode currentNode) {
        if (currentNode == null) {
            return;
        }

        if (!currentNode.leftEmpty()) {
            printInOrder(currentNode.getLeft());
        }

        System.out.println(currentNode);

        if (!currentNode.rightEmpty()) {
            printInOrder(currentNode.getRight());
        }
    }

    // Imprimir la estructura del árbol
    public void printTree() {
        printTree(root, "", true);
    }

    public void printTree(RBNode node, String prefix, boolean isLeft) {
        if (node != null) {
            System.out.println(prefix + (isLeft ? "├── " : "└── ") + node);
            printTree(node.getLeft(), prefix + (isLeft ? "│   " : "    "), true);
            printTree(node.getRight(), prefix + (isLeft ? "│   " : "    "), false);
        }
    }

    // Getters y setters
    public RBNode getRoot() {
        return root;
    }

    public void setRoot(RBNode root) {
        this.root = root;
    }
}
