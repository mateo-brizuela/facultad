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
public class Socio extends Persona {
    // declaro atributos
    private int idSocio;
    private int dni;
    private boolean habilitado;
    
    // constructor
    public Socio(int idSocio, int dni, String nombre,
            String apellido, boolean habilitado){
        super(nombre,apellido);
        this.idSocio = idSocio;
        this.dni = dni;
        this.habilitado = habilitado;
    }
    
    // constructor vacio
    public Socio(){
        
    }
    
    
    @Override //reescribo el metodo toString
    public String toString(){
        return "socio: {id: "+ idSocio +"|dni: "+ dni +"|nombre: "+ getNombre() +" "+ getApellido() +"}"; 
    }
    
    // getters y setters
    public void setIdSocio(int idSocio){
        this.idSocio = idSocio;
    }
    
    public void setDni(int dni){
        this.dni = dni;
    }
    
    public void setHabilitado(boolean habilitado){
        this.habilitado = habilitado;
    }
    
    public int getIdSocio(){
        return idSocio;
    }
    
    public int getDni(){
        return dni;
    }
    
    public boolean getHabilitado(){
        return habilitado;
    }
}
