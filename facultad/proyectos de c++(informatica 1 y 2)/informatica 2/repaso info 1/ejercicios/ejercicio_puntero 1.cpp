#include <iostream>
#include<stdio.h>
using namespace std;

void imprimir_resultado(float *n);
int main(int argc, char *argv[]) {
	float n = 5.0/2;
	float *dn = 0; // direccion de la variable n
	dn = &n;
	imprimir_resultado(dn);
	return 0;
}

void imprimir_resultado(float *n)
{
	printf("el resultado de la division 5/2 es: %.1f\n ",*n);
}

