/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ArchivosJava;
import static ArchivosJava.ManejoArchivos.crearArchivo;
import static ArchivosJava.ManejoArchivos.escribirArchivo;
/**
 *
 * @author mateo
 */
public class TestEscribirArchivo {
    public static void main(String[] args) {
        String nombreArchivo = "C:\\Users\\mateo\\Desktop\\Archivos java\\prueba3.txt";
        escribirArchivo(nombreArchivo,"hola y chau desde java 2");
        
    }
}
