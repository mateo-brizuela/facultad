/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Funcionalidades;

/**
 *
 * @author mateo
 */

// esta clase simplemente genera ids unicos, por cada vez que se intancia un objeto
// de cualquier tipo
public class GeneradorId {
    private static int contadorId = 0;
    
    public static int generarId(){
        contadorId ++;
        return contadorId;
    }
}
