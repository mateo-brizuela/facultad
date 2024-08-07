package personas;


import personas.Persona;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author mateo
 */
public class TestPersona {
    public static void main(String[] args) {
        Persona p = new Persona();
        p.setDni(44972137);
        p.setId(1);
        p.setEdad(20);
        p.setNombre("Mateo Brizuela");
        System.out.println(p);
        
        Persona p2 = new Persona(2,"Julia Brizuela",46973274,17);
        System.out.println(p2);
    }
}
