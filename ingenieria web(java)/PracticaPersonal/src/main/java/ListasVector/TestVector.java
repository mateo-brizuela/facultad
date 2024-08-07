/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ListasVector;

import java.util.Collection;

/**
 *
 * @author mateo
 */
public class TestVector {
    public static void main(String[] args) {
        //declaro la coleccion de forma generica
        Collection<String> miColeccion = UNombres.obtenerLista();
        
        //leo la coleccion
        for(String nom : miColeccion){
            System.out.println("el nombre es: " + nom);
        }
    }

    
    
    
    
    
}
