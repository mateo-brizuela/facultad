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
public class MainCrearArchivo {
    public static void main(String[] args) {
        File archivo = new File("C:\\Users\\mateo\\Desktop\\Archivos java\\Prueba1.txt");
        
        try{
            PrintWriter salida = new PrintWriter(archivo);
            salida.close();
        }
        
        catch(IOException ex){
            ex.printStackTrace();
        }
        
        System.out.println("el archivo fue creado correctamente");
    }
}
