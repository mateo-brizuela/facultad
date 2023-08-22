#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {

	int i = 0;
	int notas[3] = {0,0,0};
	float promedio = 0;
	
	for(i=0;i<3;i++)
	{
		printf("ingrese la nota N° %d: ",i+1);
		scanf("%d",&notas[i]);
		promedio = promedio + notas[i];
	}
	
	promedio = promedio/3.0;
	printf("el promedio de las notas es : %.2f",promedio);
	
	return 0;
}

