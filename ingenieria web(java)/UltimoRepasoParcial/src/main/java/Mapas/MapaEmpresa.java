/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Mapas;
import Entidades.Empleados;
import Enumeraciones.Estudios;
import java.util.*;
/**
 *
 * @author mateo
 */
public class MapaEmpresa {
    public static void main(String[] args) {
        Map<Empleados,Integer> mapaEmpleados = new HashMap<>();
        
        Empleados empleado1 = new Empleados(1,"mateo",20,Estudios.SECUNDARIOS);
        Empleados empleado2 = new Empleados(2,"juan",20,Estudios.SECUNDARIOS);
        Empleados empleado3 = new Empleados(3,"pedro",20,Estudios.SECUNDARIOS);
        Empleados empleado4 = new Empleados(4,"miguel",20,Estudios.SECUNDARIOS);
        
        mapaEmpleados.put(empleado1, 1);
        mapaEmpleados.put(empleado2, 2);
        mapaEmpleados.put(empleado3, 3);
        mapaEmpleados.put(empleado4, 4);
        
        imprimir(mapaEmpleados.keySet());
        imprimir(mapaEmpleados.values());
        
    }
    
    public static void imprimir(Collection col){
        for(Object elemento : col){
            System.out.println(elemento);
        }
    }
    
    
    
}
