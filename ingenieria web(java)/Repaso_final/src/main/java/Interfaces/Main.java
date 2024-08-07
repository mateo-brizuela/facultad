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
public class Main {
    public static void main(String[] args) {
        GestionDatos mySQL = new GestionSQL();
        GestionDatos oracleBD = new GestionOracle();
        GestionSQL puedo = new GestionSQL();
        
        mySQL.registrarDatos();
        mySQL.listarDatos();
        mySQL.eliminarDatos();
        
        oracleBD.registrarDatos();
        oracleBD.listarDatos();
        oracleBD.eliminarDatos();
        
        puedo.mostrarConstante();
    }
}
