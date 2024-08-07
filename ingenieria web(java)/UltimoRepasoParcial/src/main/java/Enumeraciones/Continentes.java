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
public enum Continentes {
    AMERICA(50),
    AFRICA(23),
    ASIA(65),
    OCEANIA(23),
    EUROPA(24);
    
    private int paises;
    
    Continentes(int paises){
        this.paises = paises;
    }
    
    public int getPaises(){
        return paises;
    }
}
