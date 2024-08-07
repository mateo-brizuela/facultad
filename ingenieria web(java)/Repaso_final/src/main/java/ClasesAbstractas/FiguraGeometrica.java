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
public abstract class FiguraGeometrica {
    private double area;
    
    public String toString(){
        return "area = "+ calcularArea();
    }
    
    public abstract double calcularArea();
    
    public static double areaPromedio(FiguraGeometrica vector[]){
        double resultado = 0;
        for (int i = 0; i < vector.length; i++) {
            resultado += vector[i].getArea();
        }
        resultado = resultado/vector.length;
        return resultado;
    }
    
    
    public void setArea(double area){
        this.area = area;
    }
    
    public double getArea(){
        return calcularArea();
    }
}
