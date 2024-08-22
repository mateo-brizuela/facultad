package utils;

public class FactorialNumero {
    public static void main(String[] args) {
        System.out.println("hola mundo");
        int numero = 5;
        int resultado = 0;
        resultado = CFactorial(numero);
        System.out.println("el resultado del factorial de "+ numero+
        " es "+ resultado);

        
    }

    public static int CFactorial(int numero){

        if (numero == 1 || numero == 0) {
            return 1;
        }else{

            return numero * CFactorial(numero - 1);
        }
    }


}
