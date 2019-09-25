#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>

void repartir(int cantidad,char* mazo_jugador,char* mazo_origen);
void dar_carta(char* nombre_carta,char* mazo);
void quitar_carta(char* nombre_carta,char* mazo);
void liberar_memoria(char** lista,int size);
void crear_cartas_iniciales(char* nombre_cartas);
void crear_carta(char* nombre_carta);
void quitar_ultima_carta(char* last_card);
void transferir_cartas(char** cartas,int* seleccion_cartas,char* mazo_origen,char* mazo_destino,int cantidad);
void ver_cartas(char** mazo,int cantidad);
void inicio();
int contar_cartas(char* mazo);
int * seleccion_aleatoria(int N,int tamano_mazo);
char** dar_mazo(char* directorio,int cantidad);

int main()
{

	

	inicio();
	
	return 0;
}

void inicio()
{

	char** MAZO;
	int SIZE;
	int* SELECCION;

	crear_cartas_iniciales("nombre_cartas.txt");

	repartir(7,"player1/","mazo/");
	repartir(7,"player2/","mazo/");
	repartir(7,"player3/","mazo/");
	repartir(7,"player4/","mazo/");
	
	SIZE=contar_cartas("mazo/");
	MAZO=dar_mazo("mazo/",SIZE);
	SELECCION=seleccion_aleatoria(1,SIZE);

	transferir_cartas(MAZO,SELECCION,"mazo/","last_card/",1);

}

void repartir(int cantidad,char* mazo_jugador,char* mazo_origen)
{
	char** lista_cartas;
	int tamano_mazo;
	int* seleccion_cartas;

	tamano_mazo=contar_cartas(mazo_origen);
	
	lista_cartas=dar_mazo(mazo_origen,tamano_mazo);
	
	seleccion_cartas=seleccion_aleatoria(cantidad,tamano_mazo);
	
	transferir_cartas(lista_cartas,seleccion_cartas,mazo_origen,mazo_jugador,cantidad);

	liberar_memoria(lista_cartas,tamano_mazo);

	free(seleccion_cartas);
}

void dar_carta(char* nombre_carta,char* mazo)
{
	char temp[30];

	strcpy(temp,mazo);
	strcat(temp,nombre_carta);

	FILE* fp=fopen(temp,"w");
	fclose(fp);
	
}

void quitar_carta(char* nombre_carta,char* mazo)
{
	char temp[30];

	strcpy(temp,mazo);
	strcat(temp,nombre_carta);
	remove(temp);
}

int * seleccion_aleatoria(int N,int tamano_mazo)
{
	int i=0;
	int j;
	int flag=1;
	int temp;
	int *numeros=(int *)malloc(sizeof(int)*N);

	srand(time(NULL));

	while(i<N)
	{
		temp=rand() % tamano_mazo;
		for(j=0;j<i;j++)
		{
			if (temp == numeros[j])
			{
				flag=0;
			}

		}
		if (flag)
		{
			numeros[i]=temp;
			i++;
		}
		flag=1;
	}
	
	return numeros;

}

void quitar_ultima_carta(char* last_card)
{
	char** carta;

	carta=dar_mazo(last_card,1);
	quitar_carta(carta[0],last_card);

}

void transferir_cartas(char** cartas,int* seleccion_cartas,char* mazo_origen,char* mazo_destino,int cantidad)
{
	int i;
	for(i=0;i<cantidad;i++)
	{
		dar_carta(cartas[seleccion_cartas[i]],mazo_destino);
		quitar_carta(cartas[seleccion_cartas[i]],mazo_origen);
	}
	
	
}


void ver_cartas(char** mazo,int cantidad)
{
	int i=0;
	char temp1[30];
	char *temp2;
	char color[10];
	char tipo[10];
	
			
	while(i<cantidad)
	{
		strcpy(temp1,mazo[i]);

		temp2=strtok(temp1,"_");
		strcpy(color,temp2);
		temp2=strtok(NULL,"_");
		strcpy(tipo,temp2);

		printf("%d: %s %s.\n",i+1,color,tipo);
		
		i++;

	}




}


int contar_cartas(char* mazo)
{
	DIR* dir;
	struct dirent* ent;
	dir=opendir(mazo);

	int contador=0;

	while((ent=readdir(dir))!=NULL)
	{	
		
		if(strcmp(ent->d_name,".")!=0 && strcmp(ent->d_name,"..")!=0)
		{
			contador++;
			
			
		}
	}
	closedir(dir);
	return contador;
}

char** dar_mazo(char* directorio,int cantidad)
{
	DIR* dir;
	struct dirent* ent;
	dir=opendir(directorio);

	char** lista=(char**)malloc(sizeof(char*)*cantidad);
	int i=0;

	while((ent=readdir(dir))!=NULL)
	{	
		
		if(strcmp(ent->d_name,".")!=0 && strcmp(ent->d_name,"..")!=0)
		{

			lista[i]=(char*)malloc(sizeof(char)*30);
			strcpy(lista[i],ent->d_name);
			
			i++;
		}
	}
	closedir(dir);
	return lista;
}

void liberar_memoria(char** lista,int size)
{
	
	int i=0;
	
	while(i<size)
	{
	
		free(lista[i]);
		i++;
	
	}
	
	free(lista);

}



void crear_cartas_iniciales(char* nombre_cartas)
{
	FILE* fp=fopen(nombre_cartas,"r");
	char name[20];
	
	
	while (feof(fp)==0)
	{
		
		fscanf(fp,"%s\n",name);
		crear_carta(name);
	
	}

	fclose(fp);
	
}

void crear_carta(char* nombre_carta)
{
	char directorio[30];
	strcpy(directorio, "mazo/");
	strcat(directorio,nombre_carta);
	strcat(directorio,".txt");
	FILE* fp=fopen(directorio,"w");
	fclose(fp);



}
