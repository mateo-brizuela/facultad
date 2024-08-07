/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Mapas;

/**
 *
 * @author mateo
 */
public interface GestionMapa<T> {
    void agregar(T elemento);
    void Eliminar(T elemento);
    void imprimir();
}
