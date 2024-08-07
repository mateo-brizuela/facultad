/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package generics;

/**
 *
 * @author mateo
 */
public class Main {
    public static void main(String[] args) {
        Pair<Integer,String> e1 = new Pair<>(1 ,"hola pibes");
        Pair<Double,Boolean> e2 = new Pair<>(4.234234324,true);
        
        System.out.println(e1);
        System.out.println(e2);
    }
}
