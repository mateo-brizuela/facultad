package Practicos;

import Utils.BinaryTree.RedBlackTree.*;

public class Practico8 {
    public static void main(String[] args) {
        int[] secuence = {10,20,30,40,50,60,70};

        // creamos y cargamos un arbol para testear
        RBTree tree = new RBTree();
        for (int data : secuence) {
            tree.insert(new RBNode(data));// insercion de nodos
            tree.printTree(tree.getRoot(), "", false); // impresion del arbol con cada insercion
        }
        // control de propiedades y calculo de la mayor altura negra
        try {
            meetsRequirements(tree.getRoot());
            System.out.println("El arbol resultante cumple con las propiedades de los rojinegros.\n");
            System.out.println("La mayor altura negra (correspondiente a la raiz) es: " + countBlacks(tree.getRoot()));
        } catch (Exception e) {
            System.out.println("ERROR: El arbol NO cumple con las propiedades de los rojinegros. " + e.getMessage());
            e.printStackTrace();
        }
    } 

    private static void meetsRequirements(RBNode node) throws Exception{
        /* 
        Basciamente, el metodo controla el color de forma recursiva y, al finalizar, controla la propiedad de los caminos negros
        */
        if(node.isTerminal()){ // si el nodo es terminal solo tenemos que ver los colores
            rightColors(node);
        }
        else{ // si es cualquier otro nodo, tenemos que ver color y caminos a nodos terminales
            rightColors(node);
            meetsRequirements(node.getLeft());
            meetsRequirements(node.getRight());
            if(node.getParent() == null){ // el metodo countBlacks es recursivo de por si. Esto quiere decir que, con hacer que se ejecute para la raiz, es suficiente
                countBlacks(node);
            }
        }
    }

    private static void rightColors(RBNode current) throws Exception{ // controla que el nodo cumpla con las condiciones de color
        boolean satisfies = true;
        if(current.getParent() == null){ // current es la raiz
            if(current.getColor() != Color.BLACK){ // debe ser negra
                satisfies = false;
            }
        }
        else{ // current es cualquier otro nodo -> revisamos si hay 2 rojos consecutivos
            if(current.isRed() && !current.isTerminal()){ // solo hace falta revisar si el nodo es rojo y NO es terminal (porque mira hacia abajo)
                if(current.getLeft() != null){
                    if(current.getLeft().isRed()){
                        satisfies = false;
                    }
                }
                if(current.getRight() != null){
                    if(current.getRight().isRed()){
                        satisfies = false;
                    }
                }
            }
        }
        if(satisfies == false){
            throw new Exception("Asignacion de colores incorrecta.\n");
        }
    }

    private static int countBlacks(RBNode node) throws Exception{ // metodo recursivo para contar cant. de nodos negros en caminos a terminales
        if(node.isTerminal()){
            if(node.isRed()) return 0;
            else return 1;
        }
        else{ // no es terminal
            int countIzq = 0, countDer = 0;
            // contamos para los hijos
            countIzq = countBlacks(node.getLeft());
            countDer = countBlacks(node.getRight());
            // devolvieron el mismo valor?
            if(countIzq == countDer){
                if(node.isRed()) return (countDer);
                else{
                    if(node.getParent() != null) return (countDer +1); // "si no es la raiz"
                    else return(countDer);
                } 
            }
            else{
                throw new Exception("Caminos con distinta cantidad de nodos negros.\n");
            }
        }
    }
}
