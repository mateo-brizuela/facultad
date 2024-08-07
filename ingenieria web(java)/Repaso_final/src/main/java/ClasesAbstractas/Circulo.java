/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ClasesAbstractas;
import java.math.*;

/**
 *
 * @author mateo
 */
public class Circulo extends FiguraGeometrica {
    private double radio;
    private double resultado;
    
    public Circulo(float radio){
        this.radio = radio;
    }
    
    public Circulo(){
        
    }
    
    public String toString(){
        return "circulo "+ super.toString();
    }
    
    public void setRadio(double radio){
        this.radio = radio;
    }
    
    public double getRadio(){
        return radio;
    }
    
    public double calcularArea(){
        resultado = Math.PI * Math.pow(radio, 2);
        return resultado;
    }
}
