/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Collections;
import java.util.*;
/**
 *
 * @author mateo
 */
public class MapaEmpleados {
    public static void main(String[] args) {
        Map mapaEmpleados = new HashMap();
        
        Empleado e1 = new Empleado(1,"mateo",44124,112);
        Empleado e2 = new Empleado(2,"mauro",44124,112);
        Empleado e3 = new Empleado(3,"lina",44124,112);
        
        mapaEmpleados.put(1, e1);
        mapaEmpleados.put(2, e2);
        mapaEmpleados.put(3, e3);
        leerMapa(mapaEmpleados.keySet());
        leerMapa(mapaEmpleados.values());
        
        System.out.println(mapaEmpleados.get(2));
    }
    
    public static void leerMapa(Collection col){
        for(Object e : col){
            System.out.println(e);
        }
    }
}
