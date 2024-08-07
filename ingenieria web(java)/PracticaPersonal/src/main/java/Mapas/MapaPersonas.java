/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Mapas;

import java.util.*;

/**
 *
 * @author mateo
 */
public class MapaPersonas {
    public static void main(String[] args) {
        Map<Integer,Persona> mapa = new HashMap();
        Empleado e1 = new Empleado(1,44972137,"mateo",20,100000);
        Empleado e2 = new Empleado(2,46972137,"julia",20,100000);
        Persona p1 = new Persona(3528970,"lina",40);
        
        mapa.put(1, e1);
        mapa.put(2, e2);
        mapa.put(3, p1);
        
        System.out.println(mapa.keySet());
        System.out.println(mapa.values());
        
        imprimirKey(mapa.keySet());
        imprimirPersona(mapa.values());
    }
    
    public static void imprimirKey(Collection keys){
        for(Object elemento : keys){
            System.out.println("la key es: " + elemento);
        }
    }
    
    public static void imprimirPersona(Collection personas){
        for(Object p : personas){
            System.out.println("la pesona es: " + p);
        }
    }
}
