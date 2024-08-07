/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package enumeraciones;

/**
 *
 * @author mateo
 */
public class TestContinentes {
    public static void main(String[] args) {
        System.out.println("continente numero 4 " + Continentes.AFRICA);
        System.out.println("paises en africa " + Continentes.AFRICA.getPaises());
        
        for (Continentes c : Continentes.values()) {
            System.out.println("continente:" + c + "paises:"+ c.getPaises() );
        }
        System.out.println("");
        
        for (int i = 0; i < Continentes.values().length; i++) {
            
        }
    }
    
    
}
