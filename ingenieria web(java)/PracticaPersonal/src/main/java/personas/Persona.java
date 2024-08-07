package personas;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author mateo
 */
public class Persona {
    private int id;
    private String nombre;
    private int dni;
    private int edad;
    
    public Persona(int id, String nombre, int dni, int edad){
        this.id = id;
        this.nombre = nombre;
        this.dni = dni;
        this.edad = edad;
    }
    
    public Persona(){
        
    }
    
    public String toString(){
        return "id: " + id +"\n"+"nombre: " + nombre + "\n" + "dni: " + dni + 
               "\n"+ "edad: " + edad;
    }
    
    public boolean equals(Persona o){
        Persona otro = (Persona)o;
        return (id==otro.id)&&(nombre.equals(otro.nombre))&&(dni==otro.dni)&&(edad==otro.edad);
    }
    
    public void setId(int id){
        this.id = id;
    }
    
    public void setNombre(String nombre){
        this.nombre = nombre;
    }
    
    public void setDni(int dni){
        this.dni = dni;
    }
    
    public void setEdad(int edad){
        this.edad = edad;
    }
    
    public int getId(){
        return id;
    }
    
    public String getNombre(){
        return nombre;
    }
    
    public int getDni(){
        return dni;
    }
    
    public int getEdad(){
        return edad;
    }
    
    
}
