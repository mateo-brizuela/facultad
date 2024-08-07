/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Enumeraciones;

/**
 *
 * @author mateo
 */
public enum MensajeDelDia {
    LUNES("buen dia hoy es lunes"),
    MARTES("buen dia hoy es martes"),
    MIERCOLES("ya estamos a mitad de semana"),
    JUEVES("falta poco para el fin de semana"),
    VIERNES("ya arranco el fin de semana :)"),
    SABADO("hoy se sale"),
    DOMINGO("que triste, maniana es lunes :(");
    
    // declaro las variables de los elementos de la enumeracion
    private final String mensaje;
    
    // declaro el constructor
    MensajeDelDia(String mensaje){
        this.mensaje = mensaje;
    }
    
    // funcion para obtener el mensaje
    public String getMensaje(){
        return "el mensaje del dia es: " + mensaje;
    }
}
