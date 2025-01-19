package Utils.RecursiveFunctions;

public class AddInteger {
    public static void main(String[] args) {
        int num = 5;
        int result = add(num, 1);

        System.out.println("el resultado de sumar los primeros " + num + " numeros es " + result);
    }


    public static int add(int cantidad, int num){
        if(cantidad == 0){
            return 0;
        }
    
        return num + add(cantidad - 1, num + 1);
    }
    
}
