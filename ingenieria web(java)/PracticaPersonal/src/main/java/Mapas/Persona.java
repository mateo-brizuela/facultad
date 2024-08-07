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
public class Persona {
    private int dni;
    private String nombre;
    private int edad;
    
    public Persona(int dni, String nombre, int edad){
        this.dni = dni;
        this.nombre = nombre;
        this.edad = edad;
    }
    
    public Persona(){
        
    }
    
    public String toString(){
        return "dni: " + dni+ " nombre: " +nombre+ " edad: " +edad+"\n";
    }
    
    
    
    public void setDni(int dni){
        this.dni = dni;
    }
    
    public void setNombre(String nombre){
        this.nombre = nombre;
    }
    
    public void setEdad(int edad){
        this.edad = edad;
    }
    
    public int getDni(){
        return dni;
    }
    
    public String getNombre(){
        return nombre;
    }
    
    public int getEdad(){
        return edad;
    }
}
