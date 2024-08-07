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
public class TestHash {
    public static void main(String[] args) {
        Set<Empleados> setEmpleados = new HashSet<>();
        
        setEmpleados.add(new Empleados(1,"mateo",10000,Estudios.SECUNDARIOS));
        setEmpleados.add(new Empleados(2,"julian",1000,Estudios.PRIMARIOS));
        setEmpleados.add(new Empleados(3,"franscisco",10000,Estudios.TERCIARIOS));
        setEmpleados.add(new Empleados(4,"pedro",100000,Estudios.UNIVERSITARIOS));
        
        imprimirLista(setEmpleados);
        
        
    }
    
    public static void imprimirLista(Set<Empleados> setEmpleados){
        for(Empleados e : setEmpleados){
            System.out.println(e);
        }
    }
}


