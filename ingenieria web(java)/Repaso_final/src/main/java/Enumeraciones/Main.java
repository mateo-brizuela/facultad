/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Enumeraciones;
import Enumeraciones.MensajeDelDia;

/**
 *
 * @author mateo
 */
public class Main {
    public static void main(String[] args) {
        //System.out.println("el mejor dia de la semana es: " + MensajeDelDia.LUNES);
        //System.out.println(MensajeDelDia.LUNES.getMensaje());
        
        //System.out.println("el mejor dia de la semana es: " + MensajeDelDia.VIERNES);
        //System.out.println(MensajeDelDia.VIERNES.getMensaje());
        
        leerMensajes();
    }
    
    public static void leerMensajes(){
        for (MensajeDelDia m : MensajeDelDia.values()) {
            System.out.println("del dia "+ m +" "+ m.getMensaje());
        }
    }
}
