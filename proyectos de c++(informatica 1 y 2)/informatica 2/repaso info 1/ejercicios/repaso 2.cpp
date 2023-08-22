#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

int generar_random (int min, int max);
void mostrar_matriz(float matriz[5][6]);
void mostrar_retraso(float matriz[5][6]);
void g_expensas(float matriz[5][6]); 
void mostrar_vivienda(float matriz[5][6]);
void c_montos(float matriz[5][6]);
int recaudacion (float matriz[5][6]);

int main(int argc, char *argv[]) {
	srand(time(NULL));
	float matriz[5][6];
	int opcion = 0;
	float d_recaudado = 0;
	
	while(opcion != 6)
	{
		printf("ingrese una opcion\n"
			   "1) generar expensas\n"
			   "2) mostrar expensa de una vivienda en particular\n"
			   "3) mostrar la recaudacion del mes de la inmobiliaria\n"
			   "4) mostrar viviendas que pagaron con retraso o no pagaron\n"
			   "5) mostrar todas las expensas emitidas en el mes\n"
			   "6) salir\n"
			   );
		scanf("%d",&opcion);
		printf("\n");
		switch(opcion)
		{
		case 1:
			g_expensas(matriz);
			c_montos(matriz);
			printf("tabla cargada\n\n");
			break;
			
		case 2:
			mostrar_vivienda(matriz);
			break;
			
		case 3:
			d_recaudado = recaudacion(matriz);
			printf("el dinero recaudado de todas las expensas es de %.2f\n\n",d_recaudado);
			break;
			
		case 4:
			mostrar_retraso(matriz);
			break;
			
		case 5:
			mostrar_matriz(matriz);
			break;
			
		case 6:
			printf("saliendo del programa\n\n");
			break;
		}
	
	}
	
	
	return 0;
}

void g_expensas(float matriz[5][6]) //generar expensas
{
	int i = 0;
	int j = 0;
	int m2_min = 30;
	int m2_max = 500;
	int dia_pago_min = 0;
	int dia_pago_max = 60;//supongo que es 30 por la cantidad de dias del mes
	
	for(i=0;i<5;i++)
	{
		for(j=0;j<6;j++)
		{
			matriz[i][j] = 0;
		}
	}
	
	for(i=0;i<5;i++)
	{
		matriz[i][0] = i+1; //rellenar numero de vivienda
	}
	
	for(i=0;i<5;i++)
	{
		matriz[i][1] = generar_random(m2_min,m2_max); // rellenar cantidad de metros cuadrados con numero aleatorios
	}
	
	for(i=0;i<5;i++)
	{
		matriz[i][3] = generar_random(dia_pago_min, dia_pago_max); //rellenar dia de pago con numeros aleatorios
	}
	
}

void calcular_monto(float matriz[5][6])
{
	
}

void mostrar_matriz(float matriz[5][6])
{
	int i = 0;
	int j = 0;
	printf("N°vivienda\tcant.m2\t\tmonto_expensa\t\tdia_pago\trecargo\t\tmonto_total\n");
	for(i=0;i<5;i++)
	{
		for(j=0;j<6;j++)
		{
			switch(j)
			{
			case 0:
				printf("%.0f\t\t",matriz[i][j]);
				break;
				
			case 1:
				printf("%.2f\t\t",matriz[i][j]);
				break;
				
			case 2:
				printf("%.2f\t\t",matriz[i][j]);
				break;
				
			case 3:
				printf("%.0f\t\t",matriz[i][j]);
				break;
				
			case 4:
				printf("%.2f\t\t",matriz[i][j]);
				break;
				
			case 5:
				printf("%.2f\t\t",matriz[i][j]);
				break;
			}
			
		}
		printf("\n");
	}
}

void c_montos(float matriz[5][6]) //calcular montos
{
	int i = 0;
	float precio_expensa = 100.0;
	int dias_atrazo = 0;
	int dia_pago = 10;
	float recargo = 0;
	float p_recargo10 = 100; //penalizacion de atraso de mas de 10 dias en expensas
	float p_recargo20 = 200; //penalizacion de atraso de mas de 20 dias en expensas
	
	for(i=0;i<5;i++)
	{
		matriz[i][2] = matriz[i][1] * precio_expensa;
	}
	
	for(i=0;i<5;i++)
	{
		dias_atrazo = matriz[i][3] - dia_pago;
		if(dias_atrazo > 0 and dias_atrazo <= dia_pago)
		{
			recargo = dias_atrazo * p_recargo10;
		}
		
		if(dias_atrazo > dia_pago)
		{
			dias_atrazo = dias_atrazo - dia_pago;
			recargo = (p_recargo10 * 10) + (dias_atrazo * p_recargo20);
		}
		
		matriz[i][4] = recargo;
	}
	
	for(i=0;i<5;i++)
	{
		matriz[i][5] = matriz[i][4] + matriz[i][2]; //el monto total es el monto de la expensa mas el recargo si es que tiene
	}
}

void mostrar_vivienda(float matriz[5][6])
{
	int i = 0;
	int cs = 0; //casa seleccionada
	printf("ingrese la casa que quiere ver 1-6");
	scanf("%d",&cs);
	cs = cs-1;
	printf("N°vivienda\tcant.m2\t\tmonto_expensa\t\tdia_pago\trecargo\t\tmonto_total\n");
	for(i=0;i<6;i++)
	{
		printf("%f\t\t",matriz[cs][i]);
	}
	printf("\n\n");
}

void mostrar_retraso(float matriz[5][6]) //muestra solo la gente que tiene penalizacion por no pagar en wtiempo y forma
{
	int i = 0;
	int j = 0;
	printf("N°vivienda\tcant.m2\t\tmonto_expensa\t\tdia_pago\trecargo\t\tmonto_total\n");
	for(i=0;i<5;i++)
	{
		if(matriz[i][4] != 0 or matriz[i][3] == 0) //para que muestre solo gente que tiene recargo o que jno haya pagado aun
		for(j=0;j<6;j++)
		{
			switch(j)
			{
			case 0:
				printf("%.0f\t\t",matriz[i][j]);
				break;
				
			case 1:
				printf("%.2f\t\t",matriz[i][j]);
				break;
				
			case 2:
				printf("%.2f\t\t",matriz[i][j]);
				break;
				
			case 3:
				printf("%.0f\t\t",matriz[i][j]);
				break;
				
			case 4:
				printf("%.2f\t\t",matriz[i][j]);
				break;
				
			case 5:
				printf("%.2f\t\t",matriz[i][j]);
				break;
			}
			
		}
		printf("\n");
	}
}

int recaudacion (float matriz[5][6])
{
	int i = 0;
	float d_recaudado = 0; // dinero recaudado
	for(i=0;i<6;i++)
	{
		d_recaudado = d_recaudado + matriz[i][5];
	}
	return(d_recaudado);
}


int generar_random (int min, int max)
{
	int r_num = min+(rand()%((max+1)-min));
	return(r_num);
}



