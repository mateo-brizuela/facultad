#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	
	int a = 0;
	int *pa = &a;
	
	printf("direccion de memoria variable a: %d \n"
		   "valor almacenado en la variable a: %d\n"
		   "valor almacenado en el puntero: %d\n"
		   "valor al que apunta el puntero: %d\n",&a,a,*pa,pa);
	
	return 0;
}

