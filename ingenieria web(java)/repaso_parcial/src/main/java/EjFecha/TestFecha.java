/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package EjFecha;

/**
 *
 * @author mateo
 */
public class TestFecha {
    public static void main(String[] args) {
        Fecha fecha1 = new Fecha();
        
        fecha1.setDia(1);
        fecha1.setMes(2);
        fecha1.setAnio(2024);
        System.out.println(fecha1);
        
        fecha1.addDias(360);
        System.out.println(fecha1);
        
        /*
        Fecha fecha2 = new Fecha(2,3,2024);
        System.out.println(fecha2);
        
        if (fecha1.equals(fecha2)) {
            System.out.println("son iguales");
        }else{
            System.out.println("son diferentes");
        }
        
        Fecha fecha3 = new Fecha("16/09/2003");
        System.out.println(fecha3);

        */
    }
}
