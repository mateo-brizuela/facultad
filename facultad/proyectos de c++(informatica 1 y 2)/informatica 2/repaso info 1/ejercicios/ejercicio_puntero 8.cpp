#include <iostream>
using namespace std;

void c_vector(char *dab);
void leer(char *dab);
void p_mayuscula(char *dab);
void p_minuscula(char *dab);

int main(int argc, char *argv[]) {
	char ab[26];
	char *dab = ab;
	char opcion = '0';
	c_vector(dab);
	
	while(opcion != 's')
	{
		printf("seleccione una opcion:\n"
			   "a) mostrar abecedario en mayusculas\n"
			   "b) mostrar abecedario en minusculas\n"
			   "s) salir\n");
		scanf("%c",&opcion);
		printf("\n");
		
		switch(opcion)
		{
		case 'a':
				p_mayuscula(dab);
				leer(dab);
				break;
				
		case 'b':
				p_minuscula(dab);
				leer(dab);
				break;	
		}
	}
	
	return 0;
}

void c_vector(char *dab) //cargar vector
{
	int i = 0;
	for(i=0;i<26;i++)
	{
		*(dab+i) = i+65;
	}
}

void leer(char *dab)
{
	int i = 0;
	for(i=0;i<26;i++)
	{
		printf("%c",*(dab+i));
	}
	printf("\n\n");
}

void p_mayuscula(char *dab)
{
	int i = 0;
	for(i=0;i<26;i++)
	{
		*(dab+i) = toupper(*(dab+i));
	}
}

void p_minuscula(char *dab)
{
	int i = 0;
	for(i=0;i<26;i++)
	{
		*(dab+i) = tolower(*(dab+i));
	}
}


