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
public class TestInterfaces {
    public static void main(String[] args) {
        IAccesoDatos datos = new IMplementacionOracle();
        datos.listar();
        
        datos = new ImplementacionSQL();
        datos.listar();
    }
    
    
}
