#include <iostream>
using namespace std;


void intercambiar(int *ptra, int *ptrb);
int main(int argc, char *argv[]) {
	
	int a = 1;
	int b = 2;
	int *ptra = &a;
	int *ptrb = &b;
	
	printf("valor almacenado en la variable a: %d\n"
		   "valor almacenado en la variable b: %d\n\n"
		   "intercambiando valores\n\n",a,b);
	intercambiar(ptra,ptrb);
	printf("valor almacenado en la variable a: %d\n"
		   "valor almacenado en la variable b: %d\n",a,b);
	
	
	return 0;
}

void intercambiar(int *ptra, int *ptrb)
{
	int temp = 0;
	
	temp = *ptra;
	*ptra = *ptrb;
	*ptrb = temp;

}

