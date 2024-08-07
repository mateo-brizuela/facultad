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
public class FechaDetallada extends Fecha {
    
    private static String meses[]= {
        "enero",
        "febrero",
        "marzo",
        "abril",
        "mayo",
        "junio",
        "julio",
        "agosto",
        "septiembre",
        "octubre",
        "noviembre",
        "diciembre"
    };
    
    public FechaDetallada(){
        super();
    }
    
    public FechaDetallada(int dia, int mes, int anio){
        super(dia,mes,anio);
    }
    
    public FechaDetallada(String s){
        super(s);
    }
    
    public String toString(){
        return getDia() + " de " + meses[getMes() - 1] + " de " + getAnio();
    }
    
}
