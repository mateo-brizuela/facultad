package ejercicio3;

public class Persona {
    private String nombre;
    private int edad;

    // constructor
    public Persona(String nombre, int edad){
        this.nombre = nombre;
        this.edad = edad;
    }

    // constructor vacio
    public Persona(){
        nombre = "";
        edad = 0;
    }

    // sobrescribo el metodo toString()
    public String toString(){
        return "nombre: " + nombre + " edad: " + edad;
    }

    // getters y setters
    public String getNombre(){
        return nombre;
    }

    public int getEdad(){
        return edad;
    }

    public void setNombre(String nombre){
        this.nombre = nombre;
    }

    public void setEdad(int edad){
        this.edad = edad;
    }
}
