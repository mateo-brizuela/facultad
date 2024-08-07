/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package EjFiguras;

/**
 *
 * @author mateo
 */
public class cuadrado extends FiguraGeometrica {
    private double base;
    
    public cuadrado(double base){
        super("cuadrado");
        this.base = base;
    }
    
    public double area(){
        return base*base;
    }
}
