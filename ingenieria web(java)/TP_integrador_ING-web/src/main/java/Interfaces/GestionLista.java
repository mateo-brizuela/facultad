/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Interfaces;

import java.util.List;

/**
 *
 * @author mateo
 * @param <T>
 */
public interface GestionLista<T> {
    void agregar(T elemento);
    void eliminar(T elemento);
    void imprimirLista();
    List getLista();
}
