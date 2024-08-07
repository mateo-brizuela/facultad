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
public class TestManejoArchivos {
    public static void main(String[] args) {
        String contenido;
        String nombreArchivo = "C:\\Users\\mateo\\Desktop\\Archivos java\\prueba5.txt";
        Scanner consola = new Scanner(System.in);
        
        System.out.println("ingrese el contenido del archivo");
        contenido = consola.nextLine();
        
        //ManejoArchivos.crearArchivos(nombreArchivo);
        //ManejoArchivos.appendArchivo(nombreArchivo, contenido);
        ManejoArchivos.leerArchivo(nombreArchivo);
    }
}
