package arbolesBinarios.arbolRojoNegro.ia;

class RBNode {
    int value;
    RBNode left, right, parent;
    boolean isRed; // true = rojo, false = negro

    // Constructor de nodo rojo por defecto
    public RBNode(int value) {
        this.value = value;
        this.isRed = true; // Un nodo nuevo siempre se inserta en rojo
        this.left = null;
        this.right = null;
        this.parent = null;
    }

    // Método para verificar si el nodo es negro
    public boolean isBlack() {
        return !isRed;
    }

    // Convertir el nodo a negro
    public void makeBlack() {
        isRed = false;
    }

    // Convertir el nodo a rojo
    public void makeRed() {
        isRed = true;
    }

    @Override
    public String toString() {
        return (isRed ? "r" : "b") + value;
    }
}
