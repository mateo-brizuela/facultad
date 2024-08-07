/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Generico;

import java.util.*;

/**
 *
 * @author mateo
 */
public class ColeccionStringG {
    public static void main(String[] args) {
        List<String> miLista = new ArrayList<>();
        miLista.add("lunes");
        miLista.add("martes");
        
        imprimirLista(miLista);
    }
    
    public static void imprimirLista(List<String> lista){
        for(String s: lista){
            System.out.println("hoy es: " + s);
        }
    }
}
