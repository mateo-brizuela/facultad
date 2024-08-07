/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ArchivosJava;

import java.io.*;
import java.io.PrintWriter;

/**
 *
 * @author mateo
 */
public class ManejoArchivos {
    public static void crearArchivos(String nombreArchivo){
        File archivo = new File(nombreArchivo);
        System.out.println("direccion del archivo:");
        archivo.getAbsolutePath();
        
        try{
            PrintWriter salida = new PrintWriter(archivo);
            salida.close();
            System.out.println("el archivo se genero correctamente");
        } catch(IOException e){
            e.printStackTrace();
        }
    }
    
    public static void appendArchivo(String nombreArchivo, String contenido){
        File archivo = new File(nombreArchivo);
        
        try{
            PrintWriter salida = new PrintWriter(new FileWriter(archivo,true));
            salida.println(contenido);
            salida.close();
            System.out.println("el archivo se escribio correctamente");
        } catch(IOException ex){
            ex.printStackTrace();
        }
    }
    
    public static void leerArchivo(String nombreArchivo){
        File archivo = new File(nombreArchivo);
        
        try{
            var entrada = new BufferedReader(new FileReader(archivo));
            var lectura = entrada.readLine();
            
            while(lectura != null){
                System.out.println(lectura);
                lectura = entrada.readLine();
            }
            
            entrada.close();
        } catch(IOException ex){
            ex.printStackTrace();
        }
    }
    
    
}
