#include "manejo_archivos.h"



void inicio()
{
	char *directorios[]={"mazo/","player1/","player2/","player3/","player4/","last_card/"};
	char** MAZO;
	int SIZE;
	int* SELECCION;

	srand(time(NULL));	

	crear_carpetas(directorios,6);
	
	crear_cartas_iniciales("nombre_cartas.txt");

	/*reparte cartas a cada jugador*/
	repartir(7,"player1/","mazo/");
	repartir(7,"player2/","mazo/");
	repartir(7,"player3/","mazo/");
	repartir(7,"player4/","mazo/");
	
	SIZE=contar_cartas("mazo/");
	MAZO=dar_mazo("mazo/",SIZE);
	SELECCION=seleccion_aleatoria(1,SIZE);

	/*transfiere la carta inicial*/
	transferir_cartas(MAZO,SELECCION,"mazo/","last_card/",1);

	liberar_memoria(MAZO,SIZE);
	free(SELECCION);

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
		/*split del string*/
		temp2=strtok(temp1,"_");
		strcpy(color,temp2);
		temp2=strtok(NULL,"_");
		strcpy(tipo,temp2);

		printf("%d: %s %s.\n",i+1,color,tipo);
		
		i++;

	}




}

void quitar_ultima_carta(char* last_card)
{
	char** carta;

	carta=dar_mazo(last_card,1);
	quitar_carta(carta[0],last_card);

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

void crear_carpetas(char** directorios,int cantidad)
{
	int i;
	DIR* dir;
	
	for (i=0;i<cantidad;i++)
	{
		dir=opendir(directorios[i]);
		/*verifica si el directorio no esta creado*/
		if(ENOENT==errno)
		{
			if(mkdir(directorios[i],0777)==-1)
			{
				printf("--==Error al crear carpeta %s==--\n",directorios[i]);
			}
		}
		closedir(dir);
		
	}
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

void ver_archivos(char* directorio)
{
	DIR* dir;
	struct dirent* ent;
	dir=opendir(directorio);

	while((ent=readdir(dir))!=NULL)
	{	
		
		if(strcmp(ent->d_name,".")!=0 && strcmp(ent->d_name,"..")!=0)
		{
			printf("%s\n",ent->d_name);
			
		}
	}
	closedir(dir);
}

char** dar_mazo(char* directorio,int cantidad)
{
	DIR* dir;
	struct dirent* ent;
	dir=opendir(directorio);

	char** lista=(char**)malloc(sizeof(char*)*cantidad);
	int i=0;

	if (lista==NULL)
	{
		printf("--==Memory not allocated (dar_mazo)==--\n");
	}

	while((ent=readdir(dir))!=NULL)
	{	
		
		if(strcmp(ent->d_name,".")!=0 && strcmp(ent->d_name,"..")!=0)
		{

			lista[i]=(char*)malloc(sizeof(char)*30);
			
			if (lista[i]==NULL)
			{
				printf("--==Memory not allocated (dar_mazo)==--\n");
			}

			strcpy(lista[i],ent->d_name);
			
			i++;
		}
	}
	closedir(dir);
	return lista;
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


int * seleccion_aleatoria(int N,int tamano_mazo)
{
	int i=0;
	int j;
	int flag=1;
	int temp;
	int *numeros=(int *)malloc(sizeof(int)*N);

	

	if (numeros==NULL)
	{
		printf("--==Memory not allocated(seleccion_aleatoria)==--\n");
	}

	while(i<N)
	{
		temp=rand() % tamano_mazo;

		/*verifica si el numero no esta repetido*/
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

















