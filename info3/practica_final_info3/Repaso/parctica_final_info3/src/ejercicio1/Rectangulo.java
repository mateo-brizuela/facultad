package ejercicio1;

public class Rectangulo {
    private double  base;
    private double  altura;

    // constructor
    public Rectangulo(double base, double altura){
        this.base = base;
        this.altura = altura;
    }


    
    // getters y setters 

    public double getBase(){
        return  base;
    }

    public double getAltura(){
        return  altura;
    }

    public void setBase(double base){
        this.base = base;
    }

    public void setAltura(double  altura){
        this.altura = altura;
    }


    //funciones de la clase

    public void calcularArea(){
        double area = base * altura;
        System.out.println("area del rectangulo: " + area);

    }

    public void calcularPerimetro(){
        double perimetro = 2 * (base + altura);
        System.out.println("perimetro del rectangulo: " + perimetro);
    }

    

}
