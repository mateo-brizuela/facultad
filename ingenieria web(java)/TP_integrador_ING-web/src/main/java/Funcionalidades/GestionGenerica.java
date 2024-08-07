/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Funcionalidades;
import Entidades.Libro;
import Interfaces.GestionLista;
import java.util.*;
/**
 *
 * @author mateo
 * @param <T>
 */

// esta es una clase generica la cual hace las funciones basicas(agregar,eliminar,imprimir) de 
// gestion de una lista de cualquier tipo(socios, autores, libros)
public class GestionGenerica<T> implements GestionLista<T> {
    List<T> lista = new ArrayList<>();
    
    @Override
    public void agregar(T elemento){
        lista.add(elemento);
    }
    
    @Override
    public void eliminar(T elemento){
        lista.remove(elemento);
    }
    
    @Override
    public void imprimirLista(){
        for(T elemento : lista){
            System.out.println(elemento);
        }
    }
  
    @Override
    public List getLista(){
        return lista;
    }
}
