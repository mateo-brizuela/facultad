/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ErroresUncheked;
import static ErroresUncheked.Aritmetica2.division;
/**
 *
 * @author mateo
 */
public class TestExcepcion2 {
    public static void main(String[] args) {
        int resultado = 0;
        resultado = division(10,0);
        System.out.println("resultado = " + resultado);
    }
}
