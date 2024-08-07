/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ejConjuntos;
import EjFecha.Fecha;
import EjFecha.FechaDetallada;
import ejCuentaV1.Cuenta;

/**
 *
 * @author mateo
 */
public class TestConjuntos {
    public static void main(String[] args) {
        Object [] arr = 
        {
            new Fecha(16,9,2003),
            new FechaDetallada(16,9,2003),
            new Cuenta("jorge",10000,38422,"debito"),
            new String("esto es una cadena"),
            new Integer(36)
        };
        MuestraConjunto.mostrar(arr);
    }
}
