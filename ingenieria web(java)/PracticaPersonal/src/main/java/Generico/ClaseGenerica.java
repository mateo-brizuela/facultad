/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Generico;

/**
 *
 * @author mateo
 */
public class ClaseGenerica <T> {
    private T objeto;
    
    public ClaseGenerica(T objeto){
        this.objeto = objeto;
    }
    
    public void obtenerTipo(){
        System.out.println("el tipo T es: " + objeto.getClass().getSimpleName());
    }
}
