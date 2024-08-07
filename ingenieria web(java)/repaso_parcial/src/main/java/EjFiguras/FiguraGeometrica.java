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
public abstract class FiguraGeometrica {
    //declaro un metodo abstracto
    public abstract double area();
    private String nombre;
    
    public FiguraGeometrica(String nombre){
        this.nombre = nombre;
    }
    
    public String getNombre(){
        return nombre;
    }
    
    public String toString(){
        return  nombre + ": (area = "+ area()+")";
    }
    
     static double areaPromedio(FiguraGeometrica arr[]){
         int sum = 0;
         for (int i = 0; i < arr.length; i++) {
            sum += arr[i].area();
         }
         return sum/arr.length;
     }
}
