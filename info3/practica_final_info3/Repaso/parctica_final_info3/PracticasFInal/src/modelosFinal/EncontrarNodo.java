package modelosFinal;

public class EncontrarNodo {
    
    public static NodoLista searchList(NodoLista currentNode, int value){
        // caso base, se llego al final de la lista y no se encontro nada
        if (currentNode == null) {
            return null;
        }

        if (currentNode.getValue() == value) {
            return currentNode;
        }else{
            return searchList(currentNode.getNext(), value);
        }
    }

    public static void reemplazar(NodoLista topOfStack, int nuevo, int viejo){
        NodoLista currentNode = topOfStack;

        while (currentNode != null) {
            if (currentNode.getValue() == viejo) {
                currentNode.setvalue(nuevo);
                System.out.println("se reemplazo el dato del nodo");
                return;
            }else{
                currentNode = currentNode.getNext();
            }
        }
        System.out.println("no se encontro el nodo");
    }
}
