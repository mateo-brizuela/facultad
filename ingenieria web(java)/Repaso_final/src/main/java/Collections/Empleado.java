/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Collections;

/**
 *
 * @author mateo
 */
public class Empleado {
    private String nombre;
    private int dni;
    private int legajo;
    private int sueldo;
    
    // Constructor que recibe todos los parámetros
    public Empleado(int legajo, String nombre, int dni, int sueldo) {
        this.nombre = nombre;
        this.dni = dni;
        this.legajo = legajo;
        this.sueldo = sueldo;
    }
    
    // Constructor vacío
    public Empleado() {
        // Puedes inicializar valores por defecto si lo deseas
        this.nombre = "";
        this.dni = 0;
        this.legajo = 0;
        this.sueldo = 0;
    }
    
    // Método toString para imprimir los datos del empleado
    @Override
    public String toString() {
        return "Empleado{" +
               "legajo=" + legajo +
               ", nombre=" + nombre +
               ", dni=" + dni +
               ", sueldo=" + sueldo +
               '}';
    }
    
    // Getters y setters
    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public int getDni() {
        return dni;
    }

    public void setDni(int dni) {
        this.dni = dni;
    }

    public int getLegajo() {
        return legajo;
    }

    public void setLegajo(int legajo) {
        this.legajo = legajo;
    }

    public int getSueldo() {
        return sueldo;
    }

    public void setSueldo(int sueldo) {
        this.sueldo = sueldo;
    }
}
