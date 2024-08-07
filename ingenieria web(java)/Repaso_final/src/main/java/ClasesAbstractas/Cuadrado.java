/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ClasesAbstractas;

/**
 *
 * @author mateo
 */
public class Cuadrado extends FiguraGeometrica {
    private double base;
    private double resultado;
    
    public Cuadrado (double base){
        this.base = base;
    }
    
    public Cuadrado(){
        
    }
    
    public String toString(){
        return "cuadrado " + super.toString();
    }
    
    @Override
    public double calcularArea(){
        resultado = base*base;
        return resultado;
    }
}
