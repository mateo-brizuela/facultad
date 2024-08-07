/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Interfaces;

/**
 *
 * @author mateo
 */
public class GestionOracle implements GestionDatos {
    
    @Override
    public void registrarDatos(){
        System.out.println("registrar datos desde oracle");
    }
    
    @Override
    public void listarDatos(){
        System.out.println("listar datos desde oracle");
    }
    
    @Override
    public void eliminarDatos(){
        System.out.println("eliminar datos desde oracle");
    }
    
    public void mostrarConstante(){
        System.out.println("la constante de la interface es: " + NUM_PROTOCOLO);
    }
}
