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
public class Rectangulo extends FiguraGeometrica {
    private double base;
    private double altura;
    private double resultado;
    
    public Rectangulo(double base, double altura){
        this.base = base;
        this.altura = altura;
    }
    
    public Rectangulo(){
        
    }
    
    public String toString(){
        return "rectangulo " + super.toString();
    }
    
    @Override
    public double calcularArea(){
        resultado = base * altura;
        return resultado;
    }
}
