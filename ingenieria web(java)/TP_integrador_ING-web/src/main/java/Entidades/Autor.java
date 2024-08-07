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
public class Autor extends Persona {
    private int idAutor;
    
    // constructor
    public Autor(int idAutor, String nombre, String apellido){
        super(nombre,apellido);
        this.idAutor = idAutor;
    }
    
    // constructor vacio
    public Autor(){
        
    }
    
    @Override // reescribo el metodo toString
    public String toString(){
        return "autor: {id: "+ idAutor +"|nombre: "+ getNombre() + " "+ 
                getApellido() +"}";
    }
    
    // getters y setters
    public void setIdAutor(int idAutor){
        this.idAutor = idAutor;
    }
    
    public int getIdAutor(){
        return idAutor;
    }
    
}
