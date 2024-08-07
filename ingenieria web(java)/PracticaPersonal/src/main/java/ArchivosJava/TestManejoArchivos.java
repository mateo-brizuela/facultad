/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ArchivosJava;
import static ArchivosJava.ManejoArchivos.crearArchivo;
/**
 *
 * @author mateo
 */
public class TestManejoArchivos {
    public static void main(String[] args) {
        String nombreArchivo = "C:\\Users\\mateo\\Desktop\\Archivos java\\Prueba2.txt";
        crearArchivo(nombreArchivo);
    }
}
