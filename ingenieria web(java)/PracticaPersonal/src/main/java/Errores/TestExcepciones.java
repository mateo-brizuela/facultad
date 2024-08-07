/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Errores;
import static Errores.Aritmetica.division;
/**
 *
 * @author mateo
 */
public class TestExcepciones {
    public static void main(String[] args) {
        int resultado = 0;
        
        try{
            resultado = division(10,0);
        } catch(Exception e){
            System.out.println("hubo un error: ");
            e.printStackTrace();
            System.out.println(e.getMessage());
        }
        
        System.out.println("resultado = " + resultado);
    }
}
