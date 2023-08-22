#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
void r_matriz(int matriz[10][4]); //rellenar matriz
void r_cupo(int matriz[10][4]); //rellenar cupo
void r_promocion(int matriz[10][4]); // rellenar promocion
void r_monto (int matriz[10][4],int cuota_1,int cuota_2,int cuota_3,float promocion); // rellenar monto
void v_cupo(int matriz[10][4]); // verificar cupo
void mostrar_matriz(int matriz[10][4]);
void ordenar_matriz_nivel(int matriz[10][4]);
void contar_alumnos(int matriz[10][4], int *c_alumnos_n_1, int *c_alumnos_n_2, int *c_alumnos_n_3,int *c_alumnos_anulados);
int calcular_recaudacion(int matriz[10][4]);
int generar_random(int min,int max); //genera un numero random pasandole como parametro el numero minimo y el maximo 

int main(int argc, char *argv[]) {
	
	srand(time(NULL));
	int matriz[10][4];
	int opcion = 0;
	int recaudacion = 0;
	int cuota_principiantes = 3000;
	int cuota_intermedios = 4000;
	int cuota_avanzados = 5000;
	int alumnos_n_1 = 0; //cantidad de alumnos nivel 1, 2, 3
	int alumnos_n_2 = 0; //2
	int alumnos_n_3 = 0; //3
	int alumnos_anulados = 0; //cantidad de alumnos con inscripciones anuladas
	int *dir_alumnos_nivel_1 = nullptr; //puntero a cantidad de alumnos 1, 2, 3
	int *dir_alumnos_nivel_2 = nullptr;
	int *dir_alumnos_nivel_3 = nullptr;
	int *dir_alumnos_anulados = nullptr; //puntero a cantidad de alumnos anulados
	float promocion = 0.90; //descuento de la promocion
	
	dir_alumnos_nivel_1 = &alumnos_n_1;
	dir_alumnos_nivel_2 = &alumnos_n_2;
	dir_alumnos_nivel_3 = &alumnos_n_3;
	dir_alumnos_anulados = &alumnos_anulados;
	
	while(opcion != 6)
	{
		printf("seleccione una opcion\n"
			   "1) rellenar matriz\n"
			   "2) Mostrar todas las inscripciones por nivel.\n"
			   "3) Mostrar la cantidad de alumnos por cada nivel.\n"
			   "4) Calcular la recaudación de la academia de música.\n"
			   "5) mostrar tabla completa\n"
			   "6) salir\n"
			   );
		scanf("%d",&opcion);
		printf("\n");
		
		switch (opcion)
		{
		case 1:
			r_matriz(matriz);
			r_cupo(matriz);
			v_cupo(matriz);
			r_promocion(matriz);
			r_monto(matriz,cuota_principiantes,cuota_intermedios,cuota_avanzados,promocion);
			printf("matriz rellenada\n\n");
			break;
		
		case 2:
			ordenar_matriz_nivel(matriz);
			mostrar_matriz(matriz);
			break;
		
		case 3:
			contar_alumnos(matriz, dir_alumnos_nivel_1, dir_alumnos_nivel_2, dir_alumnos_nivel_3, dir_alumnos_anulados);
			printf("hay %d alumnos de nivel 1\n"
				   "hay %d alumnos de nivel 2\n"
				   "hay %d alumnos de nivel 3\n"
				   "hay %d alumnos anulados\n\n"
				   ,alumnos_n_1, alumnos_n_2, alumnos_n_3, alumnos_anulados);
			break;
		
		case 4:
			recaudacion = 0;
			recaudacion = calcular_recaudacion(matriz);
			printf("el monto recaudado es de $%d\n\n",recaudacion);
			break;
			
		case 5:
			mostrar_matriz(matriz);
			break;
		
		}
	}
	
	return 0;
}

void r_matriz(int matriz[10][4])
{
	int i = 0;
	for(i=0;i<10;i++)
	{
		matriz[i][0] = i+1;
		matriz[i][1] = 0;
		matriz[i][2] = 0;
		matriz[i][3] = 0;
	}
}

void r_cupo(int matriz[10][4])
{
	int n_min = 1; //nivel minimo
	int n_max = 3; //nivel maximo 
	int i = 0;
	for(i=0;i<10;i++)
	{
		matriz[i][1] = generar_random(n_min,n_max);
	}
}

void v_cupo(int matriz[10][4])
{
	int i = 0;
	int cupo = 3;
	int cont[3] = {0}; //contador de repeticiones
	int rep[3] = {0}; //valor para verificar si el se excedio el cupo
	for(i=0;i<10;i++)
	{
		switch(matriz[i][1])
		{
		case 1:
			cont[0]++;
			if(cont[0]>cupo)
			{
				rep[0] = 1;
				matriz[i][1] = 0;
				matriz[i][2] = 0;
				matriz[i][3] = 0;
			}
			break;
		case 2:
			cont[1]++;
			if(cont[1]>cupo)
			{
				rep[1] = 1;
				matriz[i][1] = 0;
				matriz[i][2] = 0;
				matriz[i][3] = 0;
			}
			break;
		case 3:
			cont[2]++;
			if(cont[2]>cupo)
			{
				rep[2] = 1;
				matriz[i][1] = 0;
				matriz[i][2] = 0;
				matriz[i][3] = 0;
			}
			break;
		}
	}
	if(rep[0] == 1)
	{
		printf("el nivel 1 esta excedido por %d cupos\n%d inscripciones fueron anuladas\n\n",cont[0]-3,cont[0]-cupo);
	}
	
	if(rep[1] == 1)
	{
		printf("el nivel 2 esta excedido por %d cupos\n%d inscripciones fueron anuladas\n\n",cont[1]-3,cont[1]-cupo);
	}
	
	if(rep[2] == 1)
	{
		printf("el nivel 3 esta excedido por %d cupos\n%d inscripciones fueron anuladas\n\n",cont[2]-3,cont[2]-cupo);
	}
}

void r_promocion(int matriz[10][4])
{
	int i = 0;
	int min =0;
	int max = 1;
	for(i=0;i<10;i++)
	{
		if(matriz[i][1]!= 0)
		{
			matriz[i][2] = generar_random(min,max);
		}
	}
}

void r_monto(int matriz[10][4],int cuota_1,int cuota_2,int cuota_3,float promocion)
{
	int i = 0;
	for(i=0;i<10;i++)
	{
		if(matriz[i][1]!=0)
		{
			switch(matriz[i][1])
			{
			case 1:
				matriz[i][3] = cuota_1;
				break;
				
			case 2:
				matriz[i][3] = cuota_2;
				break;
				
			case 3:
				matriz[i][3] = cuota_3;
				break;
			}
		}
	}
	
	for(i=0;i<10;i++)
	{
		if(matriz[i][2] == 1)
		{
			matriz[i][3] = matriz[i][3] * promocion;
		}
	}
}

void mostrar_matriz(int matriz[10][4])
{
	int i = 0;
	int j = 0;
	printf("N_inscripcion\tnivel_curso\tpromocion\tmonto_total\n");
	for(i=0;i<=9;i++)
	{
		for(j=0;j<=3;j++)
		{
			printf("%d\t\t",matriz[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void ordenar_matriz_nivel(int matriz[10][4])
{
	int v_temporal[4] = {0};
	int i = 0;
	int j = 0;
	int h = 0;
	
	for(i=0; i<9; i++)
	{
		for(j=0; j<9; j++)
		{
			if(matriz[j][1] > matriz[j+1][1])
			{
				for(h=0; h<4; h++)
				{
					v_temporal[h] = matriz[j][h];
				}
				
				for(h=0; h<4; h++)
				{
					matriz[j][h] = matriz[j+1][h];
				}
				
				for(h=0; h<4; h++)
				{
					matriz[j+1][h] = v_temporal[h];
				}
			}
		}
	}
}

void contar_alumnos(int matriz[10][4], int *c_alumnos_n_1, int *c_alumnos_n_2, int *c_alumnos_n_3,int *c_alumnos_anulados)
{
	int i = 0;

	for(i=0;i<10;i++)
	{
		switch(matriz[i][1])
		{
		case 0:
			*c_alumnos_anulados = *c_alumnos_anulados +1;
			break;
		case 1:
			*c_alumnos_n_1 = *c_alumnos_n_1 +1;
			break;
			
		case 2:
			*c_alumnos_n_2 = *c_alumnos_n_2 +1;
			break;

		case 3:
			*c_alumnos_n_3 = *c_alumnos_n_3 +1;
			break;}
	}
}

int calcular_recaudacion(int matriz[10][4])
{
	int i = 0;
	int recaudacion = 0;
	recaudacion = 0;
	
	for(i=0;i<10;i++)
	{
		recaudacion = recaudacion + matriz[i][3];
	}
	return(recaudacion);
}

int generar_random(int min ,int max)
{
	int r_num = min+(rand()%((max+1)-min));
	return(r_num);
}

