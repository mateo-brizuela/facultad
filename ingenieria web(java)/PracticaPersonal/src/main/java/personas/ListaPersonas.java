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
public class ListaPersonas {
    public static void main(String[] args) {
        List<Persona> lista = new ArrayList<Persona>();
        lista.add(new Persona(1,"juan",1029,20));
        lista.add(new Persona(2,"luisa",1229,25));
        lista.add(new Persona(3,"mauro",4029,40));
        lista.add(new Persona(4,"julia",5029,17));
        
        for(Persona p : lista){
            System.out.println(p.getNombre());
        }
        //imprimirLista(lista);
    }
    
    public static void imprimirLista(List lista){
        for (int i = 0; i < lista.size(); i++) {
            System.out.println(lista.get(i));
        }
    }
}
