/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package personas;

import java.util.*;

/**
 *
 * @author mateo
 */
public class ListaGenerica {
    public static void main(String[] args) {
        List lista2 = new ArrayList();
        lista2.add(new Persona(1,"mateo",44972137,20));
        lista2.add("hola");
        lista2.add(5);
        
        imprimirLista(lista2);
        
        
    }
    
    public static void imprimirLista(Collection lista){
        for(Object elemento : lista){
            System.out.println(elemento);
        }
    }
}
