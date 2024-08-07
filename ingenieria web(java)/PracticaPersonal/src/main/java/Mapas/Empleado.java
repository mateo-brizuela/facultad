/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Mapas;

/**
 *
 * @author mateo
 */
public class Empleado extends Persona {
    int legajo;
    int sueldo;
    
    
    public Empleado(int legajo, int dni, String nombre, int edad, int sueldo){
        super(dni,nombre,edad);
        this.legajo = legajo;
        this.sueldo = sueldo;
    }
    
    public Empleado(){
        
    }
    
    @Override
    public String toString(){
        return "legajo: " + legajo + " dni: " + getDni() + " nombre: " + getNombre()
                + " edad: " + getEdad() + " sueldo: " + sueldo+"\n";
    }
    
    public void setLegajo(int legajo){
        this.legajo = legajo;
    }
    
    public void setSueldo(int sueldo){
        this.sueldo = sueldo;
    }
    
    public int getLegajo(){
        return legajo;
    }
    
    public int getSueldo(){
        return sueldo;
    }
}
