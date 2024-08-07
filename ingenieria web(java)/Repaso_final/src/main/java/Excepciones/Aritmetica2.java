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
public class Aritmetica2 {
    public static int division2(int numerador, int denominador){
        if (denominador == 0) {
            throw new OperacionUnchecked("division entre cero");
        }
        return numerador / denominador;
    }
}
