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
public class Main {
    public static void main(String[] args) {
        double promedio = 0;
        Cuadrado figura1 = new Cuadrado(2);
        Circulo figura2 = new Circulo(2);
        Rectangulo figura3 = new Rectangulo(3,4);
        
        FiguraGeometrica vector[] = {
            figura1,
            figura2,
            figura3
        };
        
        promedio = FiguraGeometrica.areaPromedio(vector);
        System.out.println("el promedio de area es de: "+ promedio);
       
        
        System.out.println(figura1);
        System.out.println(figura2);
        System.out.println(figura3);
    }
}
