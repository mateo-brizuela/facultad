/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ArchivosJava;

import java.io.*;
import java.util.Scanner;

/**
 *
 * @author mateo
 */
public class EscribirMensaje {
    public static void main(String[] args) {
        File archivo = new File("C:\\Users\\mateo\\Desktop\\Archivos java\\prueba4.txt");
        Scanner consola = new Scanner(System.in); 
        String mensaje;
        System.out.println("escriba un mensaje para el archivo");
        mensaje = consola.nextLine();
        
        try{
            PrintWriter salida = new PrintWriter(archivo);
            salida.print(mensaje);
            salida.close();
        } catch(IOException ex){
            ex.printStackTrace(System.out);
        }
    }
}
