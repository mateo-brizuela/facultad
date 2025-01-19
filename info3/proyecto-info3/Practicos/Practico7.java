package Practicos;
import Utils.BinaryTree.AVLTree.*;


public class Practico7 {
    public static void main(String[] args) {
        // 1. Generar el primer árbol con la secuencia (10, 100, 20, 80, 40, 70)
        System.out.println("1) se genera un arbol con la siguiente secuencia de valores:");
        System.out.println("10, 100, 20, 80, 40, 70");
        System.out.println("Árbol 1:");
        AVLTree avlTree1 = new AVLTree();
        int[] values1 = {10, 100, 20, 80, 40, 70};
        for (int value : values1) {
            avlTree1.insert(new AVLNode(value));
        }
        avlTree1.printTree(avlTree1.getRoot(), "", false);

        // 2. Generar el segundo árbol con la secuencia (5, 10, 20, 30, 40, 50, 60)
        System.out.println("2) se genera un arbol con la siguiente secuencia de valores:");
        System.out.println("5, 10, 20, 30, 40, 50, 60");
        System.out.println("\nÁrbol 2:");
        AVLTree avlTree2 = new AVLTree();
        int[] values2 = {5, 10, 20, 30, 40, 50, 60};
        for (int value : values2) {
            avlTree2.insert(new AVLNode(value));
        }
        avlTree2.printTree(avlTree2.getRoot(), "", false);

        // 3. Generar el tercer árbol con la secuencia (4, 2, 30, 1, 10, 50, 5, 20, 40), luego eliminar valores
        System.out.println("3) se genera un arbol con la siguiente secuencia de valores:");
        System.out.println("4, 2, 30, 1, 10, 50, 5, 20, 40");
        System.out.println("\nÁrbol 3:");
        AVLTree avlTree3 = new AVLTree();
        int[] values3 = {4, 2, 30, 1, 10, 50, 5, 20, 40};
        for (int value : values3) {
            avlTree3.insert(new AVLNode(value));
        }
        avlTree3.printTree(avlTree3.getRoot(), "", false);

        // Eliminar el dato 1 y mostrar el árbol
        System.out.println("luego se elimina el nodo con valor 1");
        avlTree3.delete(1);
        avlTree3.printTree(avlTree3.getRoot(), "", false);

        // Eliminar el dato 30 y mostrar el árbol
        System.out.println("luego se elimina el nodo con valor 30:");
        avlTree3.delete(30);
        avlTree3.printTree(avlTree3.getRoot(), "", false);

        // 4. Generar el cuarto árbol con una rotación doble
        System.out.println("4) se genera un arbol (con rotación doble):");
        AVLTree avlTree4 = new AVLTree();
        int[] values4 = {30, 10, 20}; // Esta secuencia debería causar una rotación doble
        for (int value : values4) {
            avlTree4.insert(new AVLNode(value));
        }
        avlTree4.printTree(avlTree4.getRoot(), "", false);
    }
}
