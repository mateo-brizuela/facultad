/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package interfaces;

/**
 *
 * @author mateo
 */
public class ImplementacionSQL implements IAccesoDatos {
    @Override 
    public void insertar(){
        System.out.println("insertar desde sql");
    }
    
    @Override
    public void listar(){
        System.out.println("listar desde sql");
    }
    
    @Override
    public void actualizar(){
        System.out.println("actualizar desde sql");
    }
    
    @Override
    public void eliminar(){
        System.out.println("eliminar desde sql");
    }
    
}
