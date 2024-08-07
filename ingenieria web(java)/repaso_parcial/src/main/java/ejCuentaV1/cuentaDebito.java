/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ejCuentaV1;

/**
 *
 * @author mateo
 */
public class cuentaDebito {
    public static void main(String[] args) {
        //declaro una variable de tipo object
        //esta variable es una instancia de la clase Cuenta que se llama cuentaDebito
        Cuenta cuentaDebito = new Cuenta();
        
        //defino los atributos del objeto
        cuentaDebito.setNombre("pablo garcia");
        cuentaDebito.setSaldo(1000);
        cuentaDebito.setNumero(175869);
        cuentaDebito.setTipocuenta();
        cuentaDebito.imprimir();
        
        System.out.println("");
        System.out.println("///////// cuenta credito/////////");
        //declaro otra variable de tipo object pero esta vez utilizo un 
        // constructor
        Cuenta cuentaCredito = new Cuenta("Pedro Sanchez",1500,244513,"credito");
        //cuentaCredito.imprimir(); ahora voy usar el metodo toString() que sobrescribi
        System.out.println(cuentaCredito);
        
        if (cuentaCredito.equals(cuentaCredito)) {
            System.out.println("son iguales");
        }else{
            System.out.println("son diferentes");
        }
    }
}
