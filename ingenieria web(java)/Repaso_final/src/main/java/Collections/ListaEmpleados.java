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
public class ListaEmpleados {
    public static void main(String[] args) {
        List listaEmpleados = new ArrayList();
        
        listaEmpleados.add(new Empleado(1,"mateo brizuela",44972137,1000));
        listaEmpleados.add(new Empleado(2,"mauro brizuela",44972137,1000));
        listaEmpleados.add(new Empleado(3,"lina simonatto",44972137,1000));
        imprimirLista(listaEmpleados);
    }
    
    public static void imprimirLista(List lista){
        for(Object e : lista){
            System.out.println(e);
        }
    }
}
