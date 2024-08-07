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
public class circulo extends FiguraGeometrica {
    private float radio;
    
    public circulo(float radio){
        super("circulo");
        this.radio = radio;
    }
    
    public double area(){
        return  Math.PI*radio*radio;
    }
}
