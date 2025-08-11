package ejercicio3;
import java.util.*;

public class MainPersona {
    public static void main(String[] args) {
        Scanner consola = new Scanner (System.in);
        ArrayList<Persona> listaPersonas = new ArrayList<>();
        int opcion;

        do{
            System.out.println("seleccione una opcion");
            System.out.println("0. salir");
            System.out.println("1. agregar persona");
            System.out.println("2. eliminar una persona por nombre");
            System.out.println("3. mostrar lista de personas");
            System.out.println("4. buscar persona por nombre y mostrar edad");
            opcion = consola.nextInt();
            consola.nextLine();

            switch (opcion) {

                case 0:
                    System.out.println("saliendo...");
                    break;

                case 1:
                    System.out.println("ingrese el nombre de la persona");
                    String nombre = consola.nextLine();
                    System.out.println("ingrese la edad de la persona");
                    int edad = consola.nextInt();
                    consola.nextLine();
                    listaPersonas.add(new Persona(nombre, edad));
                    break;

                case 2:

                    boolean encontrado = false;
                    System.out.println("ingrese el nombre de la persona a eliminar");
                    String nombreEliminar = consola.nextLine();
                    for (int i = 0; i < listaPersonas.size(); i++) {
                        if(listaPersonas.get(i).getNombre().equals(nombreEliminar)){
                            listaPersonas.remove(i);
                            encontrado = true;
                            System.out.println("persona eliminada");
                            break;
                        }
                    }
                    if (!encontrado){
                        System.out.println("persona no encontrada");
                    }

                    break;

                case 3:
                    for (Persona persona : listaPersonas) {
                        System.out.println(persona);
                    }
                    break;
                
                case 4:
                    System.out.println("ingrese el nombre de la persona a buscar");
                    String nombreBuscar = consola.nextLine();
                    for (Persona persona : listaPersonas) {
                        if(persona.getNombre().equals(nombreBuscar)){
                            System.out.println("la edad de " + persona.getNombre() + " es " + persona.getEdad());
                            break;
                        }
                    }
                    break;
            
                default:
                    System.out.println("opcion no valida");
                    break;
            }
        }while(opcion != 0);
    }
}
