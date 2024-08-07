/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package generics;

/**
 *
 * @author mateo
 */
public class Pair<T,U> {
    private T objeto1;
    private U objeto2;
    
    public Pair(T objeto1, U objeto2){
        this.objeto1 = objeto1;
        this.objeto2 = objeto2;
    }
    
    public Pair(){
        
    }
    
    public String toString(){
        return "objeto1: "+ objeto1+", objeto2: "+objeto2;
    }
    
    public void setObjeto1(T objeto1){
        this.objeto1 = objeto1;
    }
    
    public void setObjeto2(U objeto2){
        this.objeto2 = objeto2;
    }
    
    public T getObjeto1(){
        return objeto1;
    }
    
    public U getObjeto2(){
        return objeto2;
    }
    
    
}
