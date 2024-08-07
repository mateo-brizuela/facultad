/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ManejoArchivos;

/**
 *
 * @author mateo
 */
public class Main {
    public static void main(String[] args) {
        String nombreArchivo = "C:\\Users\\mateo\\Desktop\\Archivos java\\repasoFinal\\prueba1.txt";
        String contenido = "hola y chau desde java pedaso de trolo adicto a la verga";
        
        //GestionArchivos.crearArchivo(nombreArchivo);
        //GestionArchivos.escribirArchivo(nombreArchivo, contenido);
        //GestionArchivos.AppendArchivo(nombreArchivo, contenido);
        GestionArchivos.leerArchivo(nombreArchivo);
    }
}
