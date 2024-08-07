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
public class EscribirArchivoMain {
    public static void main(String[] args) {
        File archivo = new File("C:\\Users\\mateo\\Desktop\\Archivos java\\Prueba3.txt");
        
        try{
            PrintWriter salida = new PrintWriter(archivo);
            salida.println("Hola y chau desde java");
            salida.close();
            System.out.println("se escribio el archivo correctamente");
        } catch(IOException ex){
            ex.printStackTrace(System.out);
        }
        
        
    }
}
