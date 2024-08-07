/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ManejoArchivos;
import java.io.*;

/**
 *
 * @author mateo
 */
public class GestionArchivos {
    public static void crearArchivo(String nombreArchivo){
        File archivo = new File(nombreArchivo);
        
        try{
            PrintWriter salida = new PrintWriter(archivo);
            salida.close();
            System.out.println("se creo el archivo correctamente");
        } catch (FileNotFoundException ex){
            ex.printStackTrace(System.out);
        }
    }
    
    public static void escribirArchivo(String nombreArchivo, String contenido){
        File archivo = new File(nombreArchivo);
        
        try{
            PrintWriter salida = new PrintWriter(archivo);
            salida.println(contenido);
            salida.close();
            System.out.println("el archivo se escribio correctamente");
        } catch(FileNotFoundException ex){
            ex.printStackTrace(System.out);
        }
    }
    
    public static void AppendArchivo(String nombreArchivo, String contenido){
        File archivo = new File(nombreArchivo);
        
        try{
            PrintWriter salida = new PrintWriter(new FileWriter(archivo,true));
            salida.println(contenido);
            salida.close();
            System.out.println("se aniadio info al archivo correctamente");
        } catch(IOException ex){
            ex.printStackTrace(System.out);
        }
    }
    
    public static void leerArchivo(String nombreArchivo){
        File archivo = new File(nombreArchivo);
        
        try{
            var entrada = new BufferedReader(new FileReader(archivo));
            var lectura = entrada.readLine();
            
            while(lectura != null){
                System.out.println("lectura = " + lectura);
                lectura = entrada.readLine();
            }
            entrada.close();
        } catch(IOException ex){
            ex.printStackTrace(System.out);
        }
    }
}
