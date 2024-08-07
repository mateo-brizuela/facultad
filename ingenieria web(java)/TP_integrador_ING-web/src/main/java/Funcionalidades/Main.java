/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Funcionalidades;
import Entidades.Socio;
import Entidades.Libro;
import Entidades.Autor;
import Transacciones.Prestamo;
import java.util.*;
import static Funcionalidades.GeneradorId.generarId;
        
/**
 *
 * @author mateo
 */
// esta clase sera la que usara el operador para gestionar la biblioteca
public class Main {
    public static void main(String[] args) {
        int opcion = 0; 
        
        Scanner consola  = new Scanner(System.in);
        
        // inicializacion de clases necesarias
        GestionGenerica<Socio> gestionSocios = new GestionGenerica<>();
        GestionGenerica<Libro> gestionLibros = new GestionGenerica<>();
        GestionGenerica<Autor> gestionAutores = new GestionGenerica<>();
        GestionGenerica<Prestamo> gestionPrestamos = new GestionGenerica<>();
        
        //agrego un socio
        gestionSocios.agregar(new Socio(generarId(),44972137,"Mateo","Brizuela",true));
        gestionSocios.agregar(new Socio(generarId(),6256753,"Carlos","Chicala",true));
        
        //agrego los autores
        Autor autor1 = new Autor(generarId(),"Jose","Hernandes");
        Autor autor2 = new Autor(generarId(),"Julio","Verne");
        Autor autor3 = new Autor(generarId(),"Charles","Dickens");
        Autor autor4 = new Autor(generarId(),"Mark","Twain");
        gestionAutores.agregar(autor1);
        gestionAutores.agregar(autor2);
        gestionAutores.agregar(autor3);
        gestionAutores.agregar(autor4);
        
        // agrego los libros
        gestionLibros.agregar(new Libro(generarId(),"Martin Fierro",autor1));
        gestionLibros.agregar(new Libro(generarId(),"De la Tierra a la Luna",autor2));
        gestionLibros.agregar(new Libro(generarId(),"20.000 Leguas de Viaje Submarino",autor2));
        gestionLibros.agregar(new Libro(generarId(),"Viaje al Centro de la Tierra",autor2));
        gestionLibros.agregar(new Libro(generarId(),"David Copperfield",autor3));
        gestionLibros.agregar(new Libro(generarId(),"Cuento de Navidad",autor3));
        gestionLibros.agregar(new Libro(generarId(),"Tom Sawyer",autor4));
        gestionLibros.agregar(new Libro(generarId(),"Huckleberry Fim",autor4));
        
        while(opcion != 4){
            menu();
            while(true){
                try{
                    opcion = Integer.parseInt(consola.nextLine());
                    break;
                } catch(Exception ex){
                    System.out.println("entrada no valida");
                    System.out.println("por favor, ingrese un numero entero");
                    menu();
                }
            }   
            
            switch(opcion){
                case 1:
                    System.out.println("");
                    cargarPrestamo(gestionLibros,gestionSocios,gestionPrestamos);
                    System.out.println("");
                    break;
                case 2:
                    System.out.println("");
                    listarPrestamos(gestionPrestamos);
                    System.out.println("");
                    break;
                case 3:
                    System.out.println("");
                    listarLibros(gestionLibros);
                    System.out.println("");
                    break;
            }
        }
        
        System.out.println("adios");
        
    }
    
    // funcion estatica que simplemente imprime el menu
    public static void menu(){
        System.out.println("Que quiere hacer");
        System.out.println("1) Cargar prestamo");
        System.out.println("2) Listar todos los prestamos");
        System.out.println("3) Listar todos los libros de la biblioteca");
        System.out.println("4) cerrar programa");
    }
    
    
    // funcion que carga un nuevo prestamo en la lista de prestamos
    public static void cargarPrestamo(GestionGenerica<Libro> gestionLibros,
                                GestionGenerica<Socio> gestionSocios, 
                                GestionGenerica<Prestamo> gestionPrestamos){
        
        //declaracion de objetos y variavles que voy a usar en el programa
        Scanner consola = new Scanner(System.in);
        Libro libroSeleccionado = new Libro();
        List<Libro> listaLibros = gestionLibros.getLista();
        Socio socioSeleccionado = new Socio();
        List<Socio> listaSocios = gestionSocios.getLista();
        Prestamo prestamoGenerado;
        int dniSeleccionado = 0;
        int idSeleccionado = 0;
        boolean encontrado = false;
        
        System.out.println("usted ingreso la opcion cargar prestamo");
        
        while(encontrado == false)
        {
            System.out.println("ingrese el id del libro a prestar");
            gestionLibros.imprimirLista();
            while(true){
                try{
                    idSeleccionado = Integer.parseInt(consola.nextLine());
                    break;
                } catch(Exception ex){
                    System.out.println("entrada no valida");
                    System.out.println("por favor, ingrese un id valido");
                    gestionLibros.imprimirLista();
                }
            }
            
            for(Libro l : listaLibros){
                if (idSeleccionado == l.getIdLibro()) {
                    System.out.println("el id se verifico correctamente");
                    libroSeleccionado = l;
                    encontrado = true;
                }
            }
            
            if (encontrado == false) {
                System.out.println("no se encontro un libro con ese id");
            }   
        }
        
        // cambio el booleano nuevamente a fallse para reutilizarlo
        encontrado = false;
        
        // en mi caso voy a hacer que encuentre el socio por el dni
        // porque es lo mas  similar que puedo hacer al ejercicio...
        // pero yo lo haria con filtros de busqueda segun le convenga al usuario
        // que pueda filtrar segun el id , nombre, apellido, dni, etc
        while(encontrado == false){
            System.out.println("lista de socios:");
            gestionSocios.imprimirLista();
            
            while(true){
                System.out.println("ingrese el dni del socio");
                try{
                    dniSeleccionado = Integer.parseInt(consola.nextLine());
                    break;
                } catch(Exception ex){
                    System.out.println("entrada no valida");
                    System.out.println("por favor, ingrese un dni valido");
                }
            }  
            
            for(Socio s : listaSocios){
                if (dniSeleccionado == s.getDni()) {
                    System.out.println("socio encontrado");
                    System.out.println(s);
                    socioSeleccionado = s;
                    encontrado = true;
                }
            }
                
            if (encontrado == false) {
                System.out.println("no se encontro un socio con ese dni");
            }
        }
        
        prestamoGenerado = new Prestamo(generarId(), libroSeleccionado, socioSeleccionado,
        Prestamo.preguntarFecha());
        gestionPrestamos.agregar(prestamoGenerado);
        
        System.out.println("se registro el siguiente prestamo");
        System.out.println(prestamoGenerado);
    }
    
    // funcion estatica que permite al operador ver la lista con todos
    // los pestamos registrados
    public static void listarPrestamos(GestionGenerica<Prestamo> gestionPrestamos){
        List listaPrestamos = gestionPrestamos.getLista();
        
        if (listaPrestamos.isEmpty() == true) {
            System.out.println("no hay prestamos registrados");
        }else{
            System.out.println("los prestamos registrados son los siguientes:");
            gestionPrestamos.imprimirLista();
        }
    }
    
    //funcion estatica que permite al operador ver la lista 
    // con todos los libros registrados
    public static void listarLibros(GestionGenerica<Libro> gestionLibros){
        List listaLibros = gestionLibros.getLista();
        
        if (listaLibros.isEmpty() == true) {
            System.out.println("no hay libros registrados");
        }else{
            System.out.println("los libros registrados son los siguientes:");
            gestionLibros.imprimirLista();
        }
    }
    
    
}
