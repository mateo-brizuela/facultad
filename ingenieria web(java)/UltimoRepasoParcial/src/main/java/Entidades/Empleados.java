/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Entidades;
import Enumeraciones.Estudios;
/**
 *
 * @author mateo
 */
public class Empleados {
    private int legajo;
    private String nombre;
    private int sueldo;
    private Estudios nivelEstudio;
    
    public Empleados(int legajo, String nombre, int sueldo, Estudios nivelEstudio){
        this.legajo = legajo;
        this.nombre = nombre;
        this.sueldo =  sueldo;
        this.nivelEstudio = nivelEstudio;
    }
    
    public String toString(){
        return "empleado: {legajo: "+ legajo +"|nombre: "+ nombre +
                "|sueldo: "+ sueldo +"|nivel de estudios: "+ nivelEstudio +"}";
    }
    
    public int getLegajo(){
        return legajo;
    }
    
    public String getNombre(){
        return nombre;
    }
    
    public int getSueldo(){
        return sueldo;
    }
    
    public Estudios getEstudios(){
        return nivelEstudio;
    }
    
    
}
