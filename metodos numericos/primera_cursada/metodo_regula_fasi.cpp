#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

double calcular_funcion(double x);

int main(int argc, char *argv[]) {

	double a = 0; // primer(a) y segundo(b) valor del intervalo
	double b = 0;
	double c = 0; // valor que esta en medio del intervalo [a;b]
	double fa = 0; // funcion valuada en a b y c respectivamente
	double fb = 0;
	double fc = 0;
	double error_aprox = 0; //error absoluto aproximado(+- la mitad de la longitud del intervalo)
	int cifras_tolerancia = 0;
	int iteraciones = 1;
	
	printf("ingrese los valores del intervalo que van desde \"a\" hasta \"b\" respectivamente\n");
	scanf("%lf %lf", &a, &b);
	
	fa = calcular_funcion(a);
	fb = calcular_funcion(b);
	
	printf("ingrese las cifras minimas de precision\n");
	scanf("%d",&cifras_tolerancia);
	
	if((fa*fb) > 0){
		printf("error: no hay un punto critico en el intervalo definido\n\n");
	}else{
		error_aprox = (b-a)/2;
		while(error_aprox > pow(10,-cifras_tolerancia)){
			iteraciones++;
			c = (a*fb - b*fa)/(fb-fa);
			fc = calcular_funcion(c);
			if((fa * fc) > 0){
				a = c;
			}else if((fa * fc) < 0){
				b = c;
			}else{
				printf("encontraste la raiz exacta");
				error_aprox = 0;
			}
			error_aprox = (b - a)/2;
		}
		
		printf("la raiz es %.10lf\n" ,c);
		printf("raiz valuada en la funcion: %.10lf\n",fc);
		printf("el error es +-%.10lf\n",error_aprox);
		printf("intervalo: [%.10lf ; %.10lf]\n",a,b);
		printf("iteraciones: %d\n",iteraciones);
	}
	
	
	return 0;
}

double calcular_funcion(double x){
	double fx = -2 +(7*x)+(-5*pow(x,2))+(6*pow(x,3));
	return fx;
}

