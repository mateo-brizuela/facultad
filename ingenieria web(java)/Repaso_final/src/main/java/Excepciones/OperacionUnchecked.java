/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Excepciones;

/**
 *
 * @author mateo
 */
public class OperacionUnchecked extends RuntimeException {
    public OperacionUnchecked(String mensaje){
        super(mensaje);
    }
}
