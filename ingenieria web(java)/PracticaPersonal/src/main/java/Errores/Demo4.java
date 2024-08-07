/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Errores;

import java.util.Scanner;

/**
 *
 * @author mateo
 */
public class Demo4 {
    public static void main(String[] args) {
        int resultado = 0;
        try{
            Scanner consola = new Scanner(System.in);
            Integer intro = consola.nextInt();
            resultado = 10 / intro;
            return;
        }
        
        catch(ArithmeticException ex){
            System.out.println("division entre cero");
        }
        
        catch(Exception ex){
            System.out.println("no es un numero");
        }
        
        finally{
            System.out.println("esto sale siempre: " + resultado);
        }
        
        System.out.println("esto no sale siempre: " + resultado);
    }
}
