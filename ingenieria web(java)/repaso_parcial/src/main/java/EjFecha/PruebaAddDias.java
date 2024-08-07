/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package EjFecha;

import java.util.Scanner;

/**
 *
 * @author mateo
 */
public class PruebaAddDias {
    public static void main(String[] args) {
        int dias;
        int mes;
        int anio;
        Scanner consola  = new Scanner(System.in);
        System.out.println("ingrese una cantidad de dias");
        dias = Integer.parseInt(consola.nextLine());
        diasToFecha(dias);
        
        
    }
    
    static void diasToFecha(int dias){
        int anio;
        int resAnio;
        int mes;
        int resMes;
        
        resAnio = dias%360;
        anio = dias/360;
        resMes = resAnio%30;
        mes = resAnio/30;
        if (mes == 0) {
            mes = 12;
            anio--;
        }
        dias = resMes;
        if (dias == 0) {
            dias = 30;
            mes--;
        }
        
        System.out.println("fecha: " + dias+ "/" + mes + "/" + anio);
    }
}
