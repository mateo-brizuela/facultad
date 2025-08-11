package ejercicio4;
import java.util.*;

public class Repositorio<T> {
    private ArrayList<T> lista = new ArrayList<>();

    public void agregar(T objeto){
        lista.add(objeto);
    }

    public void eliminarIndice(int indice){
        lista.remove(indice);
    }

    public T obtenerIndice(int indice){
        return lista.get(indice);
    }   

    public void mostrar(){
        for (T t : lista) {
            System.out.println(t);
        }
    }

}
