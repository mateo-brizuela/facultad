#include <iostream>
using namespace std;

void leer(int *dv);

int main(int argc, char *argv[]) {
	int vector[3]= {1,2,3}; 
	int *dv = vector;
	leer(dv);
	return 0;
	
	
}

void leer(int *dv)
{
	int i = 0;
	for(i=0;i<3;i++)
	{
		printf("%d\t",*(dv+i));
	}
}
