/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ArchivosJava;

import java.io.*;

/**
 *
 * @author mateo
 */
public class ManejoArchivos {
    public static void crearArchivo(String nombreArchivo){
        File archivo = new File(nombreArchivo);
        System.out.println("ruta: " + archivo.getAbsolutePath());
        
        try{
            PrintWriter salida = new PrintWriter(archivo);
            salida.close();
            System.out.println("el archivo se creo correctamente");
        } catch(FileNotFoundException ex){
           ex.printStackTrace(System.out);
        }
    }
    
    public static void escribirArchivo(String nombreArchivo, String contenido){
        File archivo = new File(nombreArchivo);
        try{
            PrintWriter salida = new PrintWriter(archivo);
            salida.println(contenido);
            salida.close();
            System.out.println("el archivo se escrivio correctamente");
        } catch(FileNotFoundException ex){
            ex.printStackTrace(System.out);
        }
    }
    
    public static void anexarArchivo(String nombreArchivo, String contenido){
        File archivo = new File(nombreArchivo);
        try{
            PrintWriter salida = new PrintWriter(new FileWriter(archivo, true));
            salida.println(contenido);
            salida.close();
            System.out.println("se escribio el archivo correctamente");
        }catch(FileNotFoundException ex){
            ex.printStackTrace(System.out);
        } catch(IOException ex){
            ex.printStackTrace(System.out);
        }
    }
    
    public static void leerArchivo(String nombreArchivo){
        File archivo = new File(nombreArchivo);
        try{
            BufferedReader entrada = new BufferedReader(new FileReader(archivo));
            var lectura = entrada.readLine();
            
            while(lectura != null){
                System.out.println("lectura = " + lectura);
                lectura = entrada.readLine();
            }
            entrada.close();
        } catch(FileNotFoundException ex){
            ex.printStackTrace(System.out);
        } catch(IOException ex){
            ex.printStackTrace(System.out);
        }
    }
}
