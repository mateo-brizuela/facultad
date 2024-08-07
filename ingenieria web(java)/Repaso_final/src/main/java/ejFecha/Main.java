/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ejFecha;

/**
 *
 * @author mateo
 */
public class Main {
    public static void main(String[] args) {
        Fecha fecha1 = new Fecha(16,9,2003);
        Fecha fecha3 = new Fecha("16/9/2003");
        Fecha fecha2 = new Fecha();
        fecha2.setDia(16);
        fecha2.setMes(9);
        fecha2.setAnio(2003);
        
        
        
        
        if (fecha1.equals(fecha2)) {
            System.out.println("las fechas son iguales");
        }else{
            System.out.println("las fechas son distintas");
        }
        
        System.out.println("la fecha 1 es : " + fecha1);
        
        fecha1.addDias(360);
        
        System.out.println("la fecha 1 es : " + fecha1);
        
        System.out.println("la fecha 3 es: "+ fecha3);
        
        FechaDetallada fecha4 = new FechaDetallada(16,9,2003);
        
        System.out.println("la fecha 4 es: "+ fecha4);
    }
}
