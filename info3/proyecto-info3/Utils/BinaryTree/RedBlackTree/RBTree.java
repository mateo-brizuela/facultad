package Utils.BinaryTree.RedBlackTree;

import Utils.BinaryTree.*;

public class RBTree extends SelfEquilTree<RBNode> {

    @Override
    public void insert(RBNode newNode) {
        RBNode currentNode = (RBNode) getRoot();
        boolean found = false;

        if (getRoot() == null) { // caso 1: árbol vacío => se inserta en la raíz
            setRoot(newNode);
            newNode.setColor(Color.BLACK); // propiedad 2: la raíz debe ser negra
        } else { // caso 2: el árbol ya tiene elementos
            while (!found) { // busca el lugar donde va el nodo
                colorBalanceDown(currentNode); // algunas condiciones de color se controlan mientras bajamos
                if (newNode.getData() >= currentNode.getData()) { // es mayor o igual => miro a la derecha
                    if (currentNode.getRight() != null) { // el hijo der no está vacío => sigue buscando
                        currentNode = currentNode.getRight();
                    } else { // el hijo der está vacío => ahí va newNode
                        found = true;
                        currentNode.setRight(newNode);
                    }
                } else { // newNode.getData() < currentNode.getData() // es menor => miro a la izquierda
                    if (currentNode.getLeft() != null) { // hijo izquierdo NO vacío => sigue buscando
                        currentNode = currentNode.getLeft();
                    } else { // hijo izquierdo vacío => ahí va newNode
                        found = true;
                        currentNode.setLeft(newNode);
                    }
                }
            }
            newNode.setParent(currentNode); // la actualización del padre es igual para ambos casos
            solveExtraRedness(newNode); // resuelve si hay dos rojos consecutivos tras insertar
        }
    }

    @Override
    public RBNode delete() {
        throw new UnsupportedOperationException("Metodo 'delete' no implementado.\n");
    }

    // --------- control de propiedades ---------
    // respecto al color
    private void colorBalanceDown(RBNode currentNode) { // mantiene la consistencia de color mientras avanzamos
        if (!currentNode.isRed()) { // el nodo es negro 
            if (!currentNode.rightEmpty() && !currentNode.leftEmpty()) { // el nodo tiene 2 hijos
                if (currentNode.getRight().isRed() && currentNode.getLeft().isRed()) { // ambos hijos son rojos
                    // padre negro con 2 hijos rojos => intercambio de color entre padre e hijos
                    currentNode.setColor(Color.RED);
                    currentNode.getRight().setColor(Color.BLACK);
                    currentNode.getLeft().setColor(Color.BLACK);
                    if (currentNode == getRoot()) { // si es la raíz, debe ser negra
                        currentNode.setColor(Color.BLACK);
                    } else { // si no es la raíz, puede haber dos rojos consecutivos
                        solveExtraRedness(currentNode);
                    }
                }
            }
        }
    }

    private void solveExtraRedness(RBNode currentNode) { // resuelve si hay dos rojos consecutivos
        RBNode parentNode = currentNode.getParent();
        
        /*
        Este problema se puede presentar en 4 formas: 
            hDer y hDer
            hIzq y hIzq
            hDer y hIzq
            hIzq y hDer
        Cada forma se soluciona con una combinacion diferente de rotaciones.
        */

        if (currentNode.isRed() && parentNode.isRed()) { // hay dos rojos consecutivos
            if (currentNode == parentNode.getRight() && parentNode == parentNode.getParent().getRight()) {
                // rotación y cambio de color
                rotateLeftSimple(parentNode);
                parentNode.setColor(Color.BLACK);
                parentNode.getLeft().setColor(Color.RED);
            } else if (currentNode == parentNode.getLeft() && parentNode == parentNode.getParent().getLeft()) {
                rotateRightSimple(parentNode);
                parentNode.setColor(Color.BLACK);
                parentNode.getRight().setColor(Color.RED);
            } else if (currentNode == parentNode.getRight() && parentNode == parentNode.getParent().getLeft()) {
                rotateLeftSimple(currentNode);
                rotateRightSimple(currentNode);
                currentNode.setColor(Color.BLACK);
                currentNode.getRight().setColor(Color.RED);
            } else { // current es hijo izquierdo y parent es hijo derecho
                rotateRightSimple(currentNode);
                rotateLeftSimple(currentNode);
                currentNode.setColor(Color.BLACK);
                currentNode.getLeft().setColor(Color.RED);
            }
        }
    }
}

