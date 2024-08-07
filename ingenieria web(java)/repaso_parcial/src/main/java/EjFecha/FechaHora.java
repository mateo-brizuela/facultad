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
public class FechaHora extends FechaDetallada {
    private int hora;
    private int minuto;
    private int segundo;
    
    
    public FechaHora(String sFecha, int hora, int minuto, int segundo){
        super(sFecha);
        this.hora = hora;
        this.minuto = minuto;
        this.segundo = segundo;
    }
    
    public String toString(){
        return super.toString() + "("+hora+":"+minuto+":"+segundo+")"; 
    }
}



