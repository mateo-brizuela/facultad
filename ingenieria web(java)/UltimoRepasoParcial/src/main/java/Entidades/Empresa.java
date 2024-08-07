/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Entidades;

import java.util.*;
import Enumeraciones.Estudios;

/**
 *
 * @author mateo
 */
public class Empresa {
    public static void main(String[] args) {
        List<Empleados> listaEmpleados = new ArrayList<>();
        
        listaEmpleados.add(new Empleados(1,"mateo",10000,Estudios.SECUNDARIOS));
        listaEmpleados.add(new Empleados(2,"julian",1000,Estudios.PRIMARIOS));
        listaEmpleados.add(new Empleados(3,"franscisco",10000,Estudios.TERCIARIOS));
        listaEmpleados.add(new Empleados(4,"pedro",100000,Estudios.UNIVERSITARIOS));
        
        imprimirLista(listaEmpleados);
        
        
    }
    
    public static void imprimirLista(List<Empleados> listaEmpleados){
        for(Empleados e : listaEmpleados){
            System.out.println(e);
        }
    }
}
