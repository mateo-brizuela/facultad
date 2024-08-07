/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package enumeraciones;

/**
 *
 * @author mateo
 */
public class EjEnumeraciones {
    public static void main(String[] args) {
        System.out.println("valor numero 1 del enumerado " + dias.LUNES);
        
        indicarDias(dias.DOMINGO);
    }
    
    public static void indicarDias(dias dia){
        switch (dia){
            case LUNES:
                System.out.println("dia 1 de la semana");
                break;
            case MARTES:
                System.out.println("dia 2 de la semana");
                break;
            case MIERCOLES:
                System.out.println("dia 3 de la semana");
                break;
            case JUEVES:
                System.out.println("dia 4 de la semana");
                break;
            case VIERNES:
                System.out.println("dia 5 de la semana");
                break;
            case SABADO:
                System.out.println("dia 6 de la semana");
                break;
            case DOMINGO:
                System.out.println("dia 7 de la semana");
                break;
        }
    }
}
