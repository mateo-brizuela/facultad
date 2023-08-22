#include <iostream>
#include <stdio.h>
using namespace std;

void contar(int v[5], int *dc1, int *dc2);
	
int main(int argc, char *argv[]) {
	int v[5] = {1,2,1,1,2};
	int c1 = 0;
	int c2 = 0;
	int *dc1 = nullptr;
	int *dc2 = nullptr;
	dc1 = &c1;
	dc2 = &c2;
	
	contar(v, dc1, dc2);
	printf("%d\n%d\n",c1,c2);
	return 0;
}

void contar(int v[5], int *dc1, int *dc2)
{
	int i = 0;
	for(i=0;i<5;i++)
	{
		if(v[i] == 1)
		{
			*dc1 = *dc1 +1;
		}
		
		if(v[i] == 2)
		{
			*dc2 = *dc2 +1;
		}
	}
}

