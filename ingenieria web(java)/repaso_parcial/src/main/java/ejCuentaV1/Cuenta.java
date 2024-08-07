/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ejCuentaV1;

import java.util.Scanner;

/**
 *
 * @author mateo
 */
public class Cuenta {
    private String nombre;
    private float saldo;
    private int numero;
    private String tipoCuenta;
    Scanner consola = new Scanner(System.in);
    
    public Cuenta(String nombre, float saldo, int numero, String tipoCuenta){
        this.nombre = nombre;
        this.saldo = saldo;
        this.numero = numero;
        this.tipoCuenta = tipoCuenta;
    }
    
    public Cuenta(){
        
    }
    
    public String toString(){
        return "nombre: "+ nombre +"\n"+ "saldo: " + saldo + "\n"
                + "numero: "+ numero + "\n" + "tipo de cuenta: " + tipoCuenta;
    }
    
    public boolean equals(Object o){
        Cuenta otro = (Cuenta)o;
        return (nombre == otro.nombre) && (numero == otro.numero) && (saldo == otro.saldo)
                && (tipoCuenta.equals(otro.tipoCuenta));
    }
    
    public void setNombre(String nombre){
        this.nombre = nombre;
    }
    
    public String getNombre(){
        return nombre;
    }
    
    public void setSaldo(float saldo){
        this.saldo = saldo;
    }
    
    public float getSaldo(){
        return saldo;
    }
    
    public void setNumero(int numero){
        this.numero = numero;
    }
    
    public int getNumero(){
        return numero;
    }
    
    public void setTipocuenta(){
        System.out.println("seleccione una opcion:");
        System.out.println("1) debito");
        System.out.println("2) credito");
        int opcion = 0;
        opcion = Integer.parseInt(consola.nextLine());
        
        switch(opcion){
            case 1:
                tipoCuenta = "debito";
                break;
            case 2:
                tipoCuenta = "credito";
                break;
        }
    }
    
    public String getTipocuenta(){
        return tipoCuenta;
    }
    
    
    public void depositarSaldo(float deposito){
        if (deposito <= 0) {
            while(deposito <= 0){
                System.out.println("error: el deposito debe ser un numero"
                        + "mayor o igual a cero");
                System.out.println("ingrese la cantidad a depositar "
                        + "nuevamente");
                deposito = Float.parseFloat(consola.nextLine());
            }
        }
        saldo += deposito;
    }
    
    public void retirarSaldo(float retiro){
        if (retiro <= 0) {
            while(retiro <= 0){
                System.out.println("error: la cantidad a retirar debe"
                        + "ser un numero mayor a cero");
                System.out.println("ingrese la cantidad a retirar"
                        + "nuevamente");
                retiro = Float.parseFloat(consola.nextLine());
            }
        }
        saldo -= retiro;
    }
    
    public void imprimir(){
        System.out.println("nombre: " + nombre);
        System.out.println("saldo: " + saldo);
        System.out.println("numero: " + numero);
        System.out.println("tipo de cuenta: " + tipoCuenta);
    }
    
}
