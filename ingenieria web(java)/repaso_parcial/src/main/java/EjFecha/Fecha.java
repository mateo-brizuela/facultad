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
public class Fecha {
    private int dia;
    private int mes;
    private int anio;
    Scanner consola = new Scanner(System.in);
    
    
    public Fecha(int dia, int mes, int anio){
        
        setDia(dia);
        setMes(mes);
        setAnio(anio);
    }
    
    public Fecha(){
        
    }
    
    public Fecha(String fecha){
      int pos1 = fecha.indexOf("/");
      int pos2 = fecha.lastIndexOf("/");
      
      dia = Integer.parseInt(fecha.substring(0,pos1));
      mes = Integer.parseInt(fecha.substring(pos1 + 1, pos2));
      anio = Integer.parseInt(fecha.substring(pos2 + 1));
    }
    
    private void diasToFecha(int i){
        int resAnio;
        int resMes;
        
        resAnio = i%360;
        anio = i/360;
        resMes = resAnio%30;
        mes = resAnio/30;
        dia = resMes;
        if (mes == 0) {
            mes = 12;
            anio--;
        }
        if (dia == 0) {
            dia = 30;
            mes--;
        }
    }
    
    private int fechaToDias(){
        return anio*360 + mes*30 + dia;
    }
    
    public void addDias(int i){
        int totalDias = fechaToDias();
        totalDias += i;
        diasToFecha(totalDias);
    }
    
    public String toString(){
        return dia+"/"+mes+"/"+anio;
    }
    
    public boolean equals(Object o){
        Fecha otro = (Fecha)o;
        return (dia == otro.dia) && (mes == otro.mes) && (anio == otro.anio);
    }
    
    
    public void setDia(int dia){
        if (dia > 30) {
            while(dia > 30){
                System.out.println("error: el dia no debe ser un numero mayor a 30");
                System.out.println("ingrese el dia nuevamente");
                dia = Integer.parseInt(consola.nextLine());
            }
        }
        this.dia = dia;
    }
    
    public int getDia(){
        return dia;
    }
    
    public void setMes(int mes){
        if (mes > 12) {
            while(mes > 12){
                System.out.println("error: el mes no puede ser un numero "
                        + "mayor a 12");
                System.out.println("ingrese el mes nuevamente");
                mes = Integer.parseInt(consola.nextLine());
            }
        }
        this.mes = mes;
    }
    
    public int getMes(){
        return mes;
    }
    
    public void setAnio( int anio){
        this.anio = anio;
    }
    
    public int getAnio(){
        return anio;
    }
}
