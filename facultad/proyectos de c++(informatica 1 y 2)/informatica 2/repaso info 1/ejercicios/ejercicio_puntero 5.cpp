#include <iostream>
#include <math.h>

using namespace std;

void i_numeros(int *dn1, int *dn2, bool raiz);
void sumar(int *d1, int *d2, float *dresultado);
void restar(int *d1, int *d2, float *dresultado);
void multiplicar(int *d1, int *d2, float *dresultado);
void dividir(int *d1, int *d2, float *dresultado);
void elevar(int *d1, int *d2, float *dresultado);

int main(int argc, char *argv[]) {
	int n1 = 0;
	int n2 = 0;
	float resultado = 0.0;
	float *dresultado = &resultado;
	int *d1 = &n1;
	int *d2 = &n2;
	char opcion = '0';
	
	printf("ingrese una opcion:\n"
		   "a) sumar 2 numeros\n"
		   "b) restar 2 numeros\n"
		   "c) multiplicar 2 numeros\n"
		   "d) dividir 2 numeros\n"
		   "e) elevar a una optencia\n"
		   "f) calcular la raiz cuadrada de un numero\n");
	scanf("%c",&opcion);
	printf("\n");
	
	switch(opcion)
	{
	case 'a':
		i_numeros(d1,d2,false);
		sumar(d1,d2,dresultado);
		printf(" %d + %d = %.0f \n\n",n1,n2,resultado);
		break;
		
	case 'b':
		i_numeros(d1,d2,false);
		restar(d1,d2,dresultado);
		printf(" %d - %d = %.0f \n\n",n1,n2,resultado);
		break;
		
	case 'c':
		i_numeros(d1,d2,false);
		multiplicar(d1,d2,dresultado);
		printf(" %d * %d = %.0f \n\n",n1,n2,resultado);
		break;
		
	case 'd':
		i_numeros(d1,d2,false);
		dividir(d1,d2,dresultado);
		printf(" %d / %d = %.0f \n\n",n1,n2,resultado);
		break;
		
	case 'e':
		i_numeros(d1,d2,false);
		elevar(d1,d2,dresultado);
		printf(" %d ^ %d = %.0f \n\n",n1,n2,resultado);
		break;
		
	case 'f':
		i_numeros(d1,d2,true);
		elevar(d1,d2,dresultado);
		printf("la raiz cuadrada de %d es igual  a %.2f \n\n",n1,resultado);
		break;
	}
	return 0;
}

void i_numeros(int *d1, int *d2,bool raiz) //ingresar numeros
{
	if(raiz == false)
	{
		printf("ingrese el primer numero: ");
		scanf("%d",d1);
		printf("ingrese el segundo numero: ");
		scanf("%d",d2);
	}else
	{
		printf("ingrese el primer numero: ");
		scanf("%d",d1);
	}
	
}

void sumar(int *d1, int *d2, float *dresultado)
{
	*dresultado = *d1 + *d2;
}

void restar(int *d1, int *d2, float *dresultado)
{
	*dresultado = *d1 - *d2;
}

void multiplicar(int *d1, int *d2, float *dresultado)
{
	*dresultado = (*d1) * (*d2);
}

void elevar(int *d1, int *d2, float *dresultado)
{
	int i = 1;
	(*dresultado) = (*d1);
	for(i=1;i<(*d2);i++)
	{
		(*dresultado)= (*dresultado) * (*d1);
	}
}

void dividir(int *d1, int *d2, float *dresultado)
{
	*dresultado = (*d1) / (*d2);
}

void raiz(int *d1, int *dresultado)
{
	*dresultado = sqrt(*d1);
}

