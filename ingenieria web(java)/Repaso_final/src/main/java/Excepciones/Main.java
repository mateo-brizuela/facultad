/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Excepciones;
import static Excepciones.Aritmetica.division;
import static Excepciones.Aritmetica2.division2;
/**
 *
 * @author mateo
 */
public class Main {
    public static void main(String[] args) {
        int numerador = 0;
        int denominador = 0;
        
        try{
            division(numerador,denominador);
        } catch(OperacionExcepcion o){
            System.out.println("hubo un error");
            System.out.println(o.getMessage());
        }
        
        try{
            division2(numerador,denominador);
        } catch(OperacionUnchecked o){
            System.out.println("hubo un error");
            System.out.println(o.getMessage());
        }
        
    }
}
