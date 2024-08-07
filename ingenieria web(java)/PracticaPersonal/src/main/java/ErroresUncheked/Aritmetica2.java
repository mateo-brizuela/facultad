/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ErroresUncheked;

/**
 *
 * @author mateo
 */
public class Aritmetica2 {
    public static int division(int numerador, int denominador){
        if (denominador == 0) {
            throw new OperacionExcepcion2("division entre cero");
        }
        return numerador / denominador;
    }
}
