/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ejFecha;

/**
 *
 * @author mateo
 */
public class Fecha {
    private int dia;
    private int mes;
    private int anio;
    
    // constructor
    public Fecha(int dia,int mes, int anio){
        this.dia = dia;
        this.mes = mes;
        this.anio = anio;
    }
    
    public Fecha(String t){
        int pos1 = 0;
        int pos2 = 0;
        
        pos1 = t.indexOf("/");
        pos2 = t.lastIndexOf("/");
        
        dia = Integer.parseInt(t.substring(0, pos1));
        mes = Integer.parseInt(t.substring(pos1 + 1, pos2));
        anio = Integer.parseInt(t.substring(pos2 + 1));
    }
    
    //constructor vacio
    public Fecha(){
        
    }
    
    public String toString(){
        return dia+"/"+mes+"/"+anio;
    }
    
    public boolean equals(Object o){
        Fecha otra = (Fecha) o;
        return (dia == otra.dia)&&(mes == otra.mes)&&(anio == otra.anio);
    }
    
    public void setDia(int dia){
        this.dia = dia;
    }
    
    public void setMes(int mes){
        this.mes = mes;
    }
    
    public void setAnio(int anio){
        this.anio = anio;
    }
    
    public int getDia(){
        return dia;
    }
    
    public int getMes(){
        return mes;
    }
    
    public int getAnio(){
        return anio;
    }
    
    private int fechaToDias(){
        int diasTotales = 0;
        diasTotales = (anio*360)+(mes*30)+dia;
        return diasTotales;
    }
    
    private void diasToFecha(int diasTotales){
        int resto = 0;
        resto = diasTotales % 360;
        anio = diasTotales/360;
        mes = resto /30 ;
        resto = resto % 30;
        dia = resto;
        
        if (dia == 0) {
            dia = 30;
            mes--;
        }
        
        if (mes == 0) {
            mes = 12;
            anio--;
        }
    }
    
    public void addDias(int diaSuma){
        int diasTotales = fechaToDias();
        diasTotales += diaSuma;
        diasToFecha(diasTotales);
    }
}
