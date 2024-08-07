/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Entidades;

/**
 *
 * @author mateo
 */
public class Persona {
    private String nombre;
    private String apellido;
    
    // constructor con parametros
    public Persona(String nombre, String apellido){
        this.nombre = nombre;
        this.apellido = apellido;
    }
    
    // contructor vacio
    public Persona(){
        
    }
    
    @Override //sobrescribo el metodo toString()
    public String toString(){
        return "{nombre: " + nombre + " " + apellido+"}";
    }
    
    // getters y setters
    
    public void setNombre(String nombre){
        this.nombre = nombre;
    }
    
    public void setApellido(String apellido){
        this.apellido = apellido;
    }
    
 
    public String getNombre(){
        return nombre;
    }
    
    public String getApellido(){
        return apellido;
    }
}
