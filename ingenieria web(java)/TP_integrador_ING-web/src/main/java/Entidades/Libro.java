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
public class Libro {
    private int idLibro;
    private String titulo;
    private Autor autor;
    
    // constructor 1
    public Libro(int idLibro, String titulo, Autor autor){
        this.idLibro = idLibro;
        this.titulo = titulo;
        this.autor = autor;
    }
    
    // constructor 2
    public Libro(int idLibro, String titulo){
        this.idLibro = idLibro;
        this.titulo = titulo;
    }
    
    //constructor vacio
    public Libro(){
        
    }
    
    //sobrescribo el metodo toString
    public String toString(){
        return "libro: {id: "+ idLibro +"| titulo: "+ titulo +"| autor: "+ autor.getNombre() +
                " "+ autor.getApellido() +"}";
    }
    
    public void setIdLibro(int idLibro){
        this.idLibro = idLibro;
    }
    
    public void setTitulo(String titulo){
        this.titulo = titulo;
    }
    
    // mi idea era mostrar una lista con todos los autores y que el operador
    // elija el autor
    // pero como no se pide la opcion de registrar libros no lo implemento
    public void setIdAutor(Autor autor){
        this.autor = autor;
    }
    
    public int getIdLibro(){
        return idLibro;
    }
    
    public String getTitulo(){
        return titulo;
    }
    
    public Autor getAutor(){
        return autor;
    }
}
