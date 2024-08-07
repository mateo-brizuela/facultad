#include <iostream>
using namespace std;

void leer(float *dv);
void csumatoria(float *dv,float *dsumatoria);
void cpromedio(float *dsumatoria,float *dpromedio);

int main(int argc, char *argv[]) {
	float vector[5] = {4.5,8,2.3,1.1,3};
	float *dv = vector; // direccion del vector
	float sumatoria = 0;
	float *dsumatoria = &sumatoria; //direccion de sumatoria
	float  promedio = 0;
	float *dpromedio = &promedio;
	
	csumatoria(dv,dsumatoria);
	cpromedio(dsumatoria,dpromedio);
	leer(dv);
	printf("la sumatoria es: %.1f\n"
		   "el promedio es: %.2f",sumatoria,promedio);
	
	
	return 0;
}

void leer(float *dv)
{
	int i = 0;
	printf("el vector es: ");
	for(i=0;i<5;i++)
	{
		printf("%.1f\t",*(dv+i));
	}
	printf("\n");
}

void csumatoria(float *dv,float *dsumatoria) //calcular sumatoria5
{
	int i = 0;
	for(i=0;i<5;i++)
	{
		*dsumatoria = (*dsumatoria) + (*(dv+i)); 
	}
}

void cpromedio(float *dsumatoria,float *dpromedio) // calcular el promedio
{
	*dpromedio = (*dsumatoria)/5;
}

