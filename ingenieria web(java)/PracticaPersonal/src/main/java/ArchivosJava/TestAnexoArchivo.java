/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ArchivosJava;
import static ArchivosJava.ManejoArchivos.*;
/**
 *
 * @author mateo
 */
public class TestAnexoArchivo {
    public static void main(String[] args) {
        String nombreArchivo = "C:\\Users\\mateo\\Desktop\\Archivos java\\prueba3.txt";
        anexarArchivo(nombreArchivo, "esto es un append");
        anexarArchivo(nombreArchivo, "adios");
    }
    
}
