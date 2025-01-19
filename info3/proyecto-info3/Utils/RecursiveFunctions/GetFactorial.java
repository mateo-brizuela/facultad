package Utils.RecursiveFunctions;

public class GetFactorial {

    public static int factorial(int num){
        // caso base
        if(num == 1){
            return 1;
        }

        return  num * factorial(num - 1);
    }
}
