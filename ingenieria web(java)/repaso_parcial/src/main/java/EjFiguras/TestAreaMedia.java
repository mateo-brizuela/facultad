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
public class TestAreaMedia {
    public static void main(String[] args) {
        FiguraGeometrica arr[] =
        {
            new circulo(5),
            new cuadrado(5)
        };
        
        double promedio = FiguraGeometrica.areaPromedio(arr);
        System.out.println("promedio = " + promedio);
    }
}
