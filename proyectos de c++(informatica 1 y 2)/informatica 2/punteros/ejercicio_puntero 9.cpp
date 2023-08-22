#include <iostream>
using namespace std;

void mostrar_par(int *dvector);
void mostrar_impar(int *dvector);

int main(int argc, char *argv[]) {
	int vector[10] = {1,2,3,4,5,6,7,8,9,10};
	int *dvector = vector; // direccion del vector
	mostrar_par(dvector);
	mostrar_impar(dvector);
	
	return 0;
}

void mostrar_par(int *dvector)
{
	int i = 0;
	int par = 0;
	printf("los numeros pares son:\t");
	for(i=0;i<10;i++)
	{
		par = (*(dvector+i))%2;
		
		if(par == 0)
		{
			printf("%d\t",*(dvector+i));
		}
	}
	printf("\n\n");
}

void mostrar_impar(int *dvector)
{
	int i = 0;
	int par = 0;
	printf("los numeros impares son:\t");
	for(i=0;i<10;i++)
	{
		par = (*(dvector+i))%2;
		
		if(par != 0)
		{
			printf("%d\t",*(dvector+i));
		}
	}
	printf("\n\n");
	
}
