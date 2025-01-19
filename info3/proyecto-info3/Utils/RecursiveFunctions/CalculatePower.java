package Utils.RecursiveFunctions;

public class CalculatePower {

    public static int power(int base, int exponent){
        if(exponent == 0){
            return 1;
        }

        return base * power(base, exponent - 1);
    }

}