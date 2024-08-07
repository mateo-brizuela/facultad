/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Enumeraciones;

/**
 *
 * @author mateo
 */
public class TestContinentes {
    public static void main(String[] args) {
        //System.out.println("el mejor continente es: " + Continentes.AMERICA);
        //System.out.println(Continentes.AMERICA + " tiene " + Continentes.AMERICA.getPaises());
        indicarPaises();
        
    }
    
    public static void indicarPaises(){
        for(Continentes c : Continentes.values()){
            System.out.println("el continente "+ c +" tiene "+ c.getPaises() +" paises");
        }
    }
}
