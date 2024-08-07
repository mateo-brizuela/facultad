/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Transacciones;
import Entidades.Libro;
import Entidades.Socio;
import java.util.Scanner;
/**
 *
 * @author mateo
 */
public class Prestamo {
    //declaro los atributos del prestamo
    private int idPrestamo;
    private Libro libro;
    private Socio socio;
    private String fechaDevolucion;
    
    //constructor
    public Prestamo(int idPrestamo, Libro libro, Socio socio, String fechaDevolucion){
        this.idPrestamo = idPrestamo;
        this.libro = libro;
        this.socio = socio;
        this.fechaDevolucion = fechaDevolucion;
    }
    
    //constructor vacio
    public Prestamo(){
        
    }
    
    
    @Override //sobrescrivo el metodo toString()
    public String toString(){
        return "\n////////// prestamo numero " + idPrestamo +" //////////"
                +"\n"+ libro +"\n"+ socio +"\nfecha de devolucion: "+ fechaDevolucion +"\n";  
    }
    
    //funcion estatica
    //es para que el operador ingrese la fecha de una forma segura
    // evitando posibles errores
    public static String preguntarFecha(){
        //declaracion de variables
        Scanner consola = new Scanner(System.in);
        int anio = 0;
        int dia = 0;
        int mes = 0;
        String anioTexto;
        String mesTexto;
        String diaTexto;
        
        //pregunto al operador por el anio mes y dia
        while(true){
            System.out.println("ingrese el anio de devolucion");
            try{
                anio = Integer.parseInt(consola.nextLine());
                break;
            } catch(Exception ex){
                System.out.println("entrada no valida");
                System.out.println("por favor, ingrese un numero entero");
            }
        }
        
        while(true){
            System.out.println("ingrese el mes de devolucion");
            try{
                mes = Integer.parseInt(consola.nextLine());
                while((mes < 1) || (mes > 12)){
                    System.out.println("profavor ingrese un mes entre el 1 y el 12");
                    mes = Integer.parseInt(consola.nextLine());
                }
                break;
            } catch(Exception ex){
                System.out.println("entrada no valida");
                System.out.println("por favor, ingrese un numero entero");
            }
        }
        
        while(true){
            System.out.println("ingrese el dia de devolucion");
            try{
                dia = Integer.parseInt(consola.nextLine());
                while((dia < 1) || (dia > 30)){
                    System.out.println("profavor ingrese un dia entre el 1 y el 30");
                    dia = Integer.parseInt(consola.nextLine());
                }
                break;
            } catch(Exception ex){
                System.out.println("entrada no valida");
                System.out.println("por favor, ingrese un numero entero");
            }
        }
        
        // casteo las fechas a formato de texto pra generar el string
        anioTexto = String.valueOf(anio);
        mesTexto = String.valueOf(mes);
        diaTexto = String.valueOf(dia);
        
        //devuelvo la fecha
        return diaTexto +"/"+ mesTexto +"/"+ anioTexto;
        
        
    }
    
    
    // getters y setters
    
    public void setIdPrestamo(int idPrestamo){
        this.idPrestamo = idPrestamo;
    }
    
    public void setLibro(Libro libro){
        this.libro = libro;
    }
    
    public void setSocio(Socio socio){
        this.socio = socio;
    }
    
    public void setFecha(String fechaDevolucion){
        this.fechaDevolucion = fechaDevolucion;
    }
    
    public int getIdPRestamo(){
        return idPrestamo;
    }
    
    public String getFechaDevolucion(){
        return fechaDevolucion;
    }
    
    public Libro getlibro(){
        return libro;
    }
    
    public Socio getSocio(){
        return socio;
    }
}
