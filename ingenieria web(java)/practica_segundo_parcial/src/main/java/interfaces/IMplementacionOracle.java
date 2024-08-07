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
public class IMplementacionOracle implements IAccesoDatos {
    @Override 
    public void insertar(){
        System.out.println("insertar desde oracle");
    }
    
    @Override
    public void listar(){
        System.out.println("listar desde oracle");
    }
    
    @Override
    public void actualizar(){
        System.out.println("actualizar desde oracle");
    }
    
    @Override
    public void eliminar(){
        System.out.println("eliminar desde oracle");
    }
}
