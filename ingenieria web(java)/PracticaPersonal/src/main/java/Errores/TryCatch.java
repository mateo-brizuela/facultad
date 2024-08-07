/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Errores;

import java.util.Scanner;

/**
 *
 * @author mateo
 */
public class TryCatch {
    public static void main(String[] args) {
        Scanner consola = new Scanner(System.in);
        int num1 = 0;
        int num2 = 0;
        int resultado = 0;
        System.out.println("ingrese el primer numero a dividir: ");
        num1 = Integer.parseInt(consola.nextLine());
        System.out.println("ingrese el segundo numero a dividir: ");
        num2 = Integer.parseInt(consola.nextLine());
        
       // try{
            resultado = num1 / num2;
        //} catch(Exception ex){
            System.out.println("hubo un error: ");
            //ex.printStackTrace(System.out);
        //}
        System.out.println("resultado = " + resultado);
    }
}
