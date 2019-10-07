#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include "manejo_archivos.h"


/*---===PROTOTIPOS===---*/


void efecto(char* ENVIO,char* tipo);
/*****
* void efecto
******
* Entrega el efecto que tendra la carta sobre el siguiente jugador
******
* input:
*	char* ENVIO : Variable donde se guarda el efecto
*	char* tipo  : Es el efecto de la carta
******
* returns:
*	none
*****/

void JUGADOR(char* nombre,char* mazo);
/*****
* void JUGADOR
******
* Detecta al jugador en turno y lo guarda en una variable
******
* input:
*	char* nombre: variable en donde se guarda el nombre jugador en turno
*	char* mazo  : mazo del jugador en turno
******
* returns:
*	none
*****/

void UNO();
/*****
* void UNO
******
* Detecta a los jugadores con una sola carta y los imprime por consola
******
* input:
*	none
******
* returns:
*	none
*****/

void jugada_anterior_datos(char* DATO1,char* DATO2,char* jugada_anterior);
/*****
* void jugada_anterior_datos
******
* Procesa la jugada anterior y guarda los datos importantes en dos variables
******
* input:
*	char* DATO1	     : variable en donde se guarda el tipo de jugada anterior(NORMAL, SALTO ,+2 ,+4)
*	char* DATO2	     : variable en donde se guarda el dato extra de la jugada anterior(Color: rojo, azul, etc; NORMAL: 0)
*	char* jugada_anterior: Dato de la jugada anterior
******
* returns:
*	none
*****/

void jugada(char* ENVIO,char* mazo_jugador,char* mazo_destino,char* mazo_origen,char* tipo_ja,char* dato_ja);
/*****
* void jugada
******
* Permite al jugador en turno realizar su jugada segun el efecto de la jugada anterior
******
* input:
*	char* ENVIO	  : variable en donde se guarda el efecto que tendra la jugada actual sobre la siguiente
*	char* mazo_jugador: Mazo del jugador en turno
*	char* mazo_destino: Carpeta donde se encuentra la ultima carta jugada
*	char* mazo_origen : Mazo principal
*	char* tipo_ja	  : Efecto de la jugada anterior
*	char* dato_ja	  : Efecto extra de la jugada anterior 
******
* returns:
*	none
*****/


char* menu_jugador(char* mazo_jugador,char* mazo_destino,char* mazo_origen,char* jugada_anterior);
/*****
* char* menu_jugador
******
* Prepara el turno de un jugador, detecta si le queda una carta o si ya no le queda ninguna, y retorna el efecto de la jugada actual
******
* input:
*	char* mazo_jugador   : Mazo del jugador en turno
*	char* mazo_destino   : Carpeta donde se encuentra la ultima carta jugada
*	char* mazo_origen    : Mazo principal
*	char* jugada_anterior: Efecto de la jugada anterior
******
* returns:
*	char* : Efecto de la jugada actual
*****/

char** color_tipo(char* carta);
/*****
* char** color_tipo
******
* Extrae de una carta su color y su tipo
******
* input:
*	char* carta: nombre del archivo de texto de la carta
******
* returns:
*	char**: arreglo de tamaño 2 con el color y el tipo de la carta
*****/

int main()
{
	char jugada_anterior[20];
	char ENVIO[20];
	char** ultima_carta;
	char** datos;

	inicio();
	
	ultima_carta=dar_mazo("last_card/",1);
	//se extraen los datos de la ultima carta
	datos=color_tipo(ultima_carta[0]);
	//se aplican los efectos de esta carta 
	efecto(jugada_anterior,datos[1]);
	
	//se inicia la jugada del jugador 1 y luego se guarda el efecto de su jugada 
	strcpy(ENVIO,menu_jugador("player1/","last_card/","mazo/",jugada_anterior));
	
	printf("El siguiente jugador recibira: %s\n",ENVIO);
	sleep(1);
	//se inicia la jugada del jugador 2
	menu_jugador("player1/","last_card/","mazo/",ENVIO);
	
	return 0;
}

void efecto(char* ENVIO,char* tipo)
{
	int opcion;
	
	
	if(strcmp(tipo,"+2")==0	)//carta de tipo +2 aplica el efecto +2_0
	{
		strcpy(ENVIO,"+2_0");
	}
	else if(strcmp(tipo,"+4")==0)//carta de tipo +4 aplica el efecto +4_color, el color es escogido por el jugador
	{
		printf("Color :\n1.-Azul\n2.-Rojo\n3.-Verde\n4.-Amarillo\nEscoger: ");
		scanf("%d",&opcion);
		if(opcion==1)
		{
			strcpy(ENVIO,"+4_azul");
		}
		else if(opcion==2)
		{
			strcpy(ENVIO,"+4_rojo");
		}
		else if(opcion==3)
		{
			strcpy(ENVIO,"+4_verde");
		}
		else
		{
			strcpy(ENVIO,"+4_amarillo");
		}
	}
	else if(strcmp(tipo,"Reversa")==0)//carta de tipo Reversa aplica el efecto REVERSA_0, afectara la direccion de envio de los pipes
	{
		strcpy(ENVIO,"REVERSA_0");
	}
	else if(strcmp(tipo,"Salto")==0)//carta de tipo Salto aplica el efecto SALTO_0
	{
		strcpy(ENVIO,"SALTO_0");
	}
	else if(strcmp(tipo,"Colores")==0)//carta de tipo Colores aplica el efecto NORMAL_color, el color es escogido por el jugador
	{
		printf("Color :\n1.-Azul\n2.-Rojo\n3.-Verde\n4.-Amarillo\nEscoger: ");
		scanf("%d",&opcion);
		if(opcion==1)
		{
			strcpy(ENVIO,"NORMAL_azul");
		}
		else if(opcion==2)
		{
			strcpy(ENVIO,"NORMAL_rojo");
		}
		else if(opcion==3)
		{
			strcpy(ENVIO,"NORMAL_verde");
		}
		else
		{
			strcpy(ENVIO,"NORMAL_amarillo");
		}
	}
	else//aqui entran las cartas normales de la forma <color numero>, aplican un efecto NORMAL_0
	{
		strcpy(ENVIO,"NORMAL_0");
	}
}

void JUGADOR(char* nombre,char* mazo)
{
	if(mazo[6]=='1')
	{
		strcpy(nombre,"Jugador 1");
	}
	else if(mazo[6]=='2')
	{
		strcpy(nombre,"Jugador 2");
	}
	else if(mazo[6]=='3')
	{
		strcpy(nombre,"Jugador 3");
	}
	else
	{
		strcpy(nombre,"Jugador 4");
	}

}

void UNO()
{
	int flag=1;
	
	if(contar_cartas("player1/")==1){
		printf("<Jugador 1>\n");
		flag=0;
	}
	if(contar_cartas("player1/")==1){
		printf("<Jugador 2>\n");
		flag=0;
	}
	if(contar_cartas("player1/")==1){
		printf("<Jugador 3>\n");
		flag=0;
	}
	if(contar_cartas("player1/")==1){
		printf("<Jugador 4>\n");
		flag=0;
	}	

	if(flag)
	{
		printf("Nadie\n");
	}

}

void jugada_anterior_datos(char* DATO1,char* DATO2,char* jugada_anterior)
{
	char temp1[30];
	char* temp2;

	strcpy(temp1,jugada_anterior);

	temp2=strtok(temp1,"_");
	
	strcpy(DATO1,temp2);
	
	temp2=strtok(NULL,"_");
	
	strcpy(DATO2,temp2);
}

void jugada(char* ENVIO,char* mazo_jugador,char* mazo_destino,char* mazo_origen,char* tipo_ja,char* dato_ja)
{
	char** ultima_carta;
	char** lista_cartas_jugador;
	char** lista_cartas_origen;
	char** datos_ultima_carta;
	char** datos_carta_escogida;
	int carta_escogida[1];
	int *carta_aleatoria;
	int tamano_mazo_jugador;
	int tamano_mazo_origen;
	int flag=1;
	int opcion;

	ultima_carta=dar_mazo(mazo_destino,1);

	printf("--==Jugadores con una carta==--\n");
	UNO();
	printf("--====--\n");
	
	printf("--==Ultima Carta==--\n");
	ver_cartas(ultima_carta,1);
	printf("--====--\n");

	if(strcmp(dato_ja,"0")!=0)
	{
		printf("--==Color Escogido: %s==--\n",dato_ja);
	}

	//un efecto NORMAL es aquel que no interrumpe y permiten al jugador interactuar con su mazo
	if(strcmp(tipo_ja,"NORMAL")==0)
	{
		
		tamano_mazo_jugador=contar_cartas(mazo_jugador);
		tamano_mazo_origen=contar_cartas(mazo_origen);
			
		lista_cartas_jugador=dar_mazo(mazo_jugador,tamano_mazo_jugador);
		lista_cartas_origen=dar_mazo(mazo_origen,tamano_mazo_origen);
		
		datos_ultima_carta=color_tipo(ultima_carta[0]);
			
		printf("--==MAZO==--\n");
		ver_cartas(lista_cartas_jugador,tamano_mazo_jugador);
		printf("0.- Tomar carta del mazo.\n");
		printf("--====--\n");
		

		while(flag)
		{
			
			printf("Escoger :");
			scanf("%d",&carta_escogida[0]);
			carta_escogida[0]--;//se adapta el indice escogido al arreglo
			
			if(carta_escogida[0]>=0)
			{
				datos_carta_escogida=color_tipo(lista_cartas_jugador[carta_escogida[0]]);
					
				if(strcmp(datos_carta_escogida[0],datos_ultima_carta[0])==0 || //¿El color de la carta escogida es igual al de la ultima carta puesta?
				   strcmp(datos_carta_escogida[1],datos_ultima_carta[1])==0 || //¿El numero de la carta escogida es igual al de la ultima carta puesta?
				   strcmp(datos_carta_escogida[0],dato_ja)==0		    || //¿El color de la carta escogida es igual al color escogido por el jugador anterior(carta negra colores o +4)?
				   strcmp(datos_carta_escogida[0],"negro")==0		      )//¿El color de la carta escogida es negra?
				{
					flag=0;//se rompe el ciclo
					//se quita la ultima carta puesta
					quitar_ultima_carta(mazo_destino);			
					//se transfiere la carta obtenida al puesto de la ultima carta
					transferir_cartas(lista_cartas_jugador,carta_escogida,mazo_jugador,mazo_destino,1);
					//se aplica el efecto de la carta escogida en ENVIO para el proximo jugador
					efecto(ENVIO,datos_carta_escogida[1]);
			
					/*  <<liberar memoria>>*/
					liberar_memoria(lista_cartas_jugador,tamano_mazo_jugador);
					liberar_memoria(lista_cartas_origen,tamano_mazo_origen);
					liberar_memoria(ultima_carta,1);
					liberar_memoria(datos_ultima_carta,2);	
					liberar_memoria(datos_carta_escogida,2);
					/*<<>>*/	
				}
				else
				{
					printf("--==Carta invalida==--\n");//La carta escogida no es valida
				}
			}
			else
			{
				carta_aleatoria=seleccion_aleatoria(1,tamano_mazo_origen);
	
				datos_carta_escogida=color_tipo(lista_cartas_origen[carta_aleatoria[0]]);

				if(strcmp(datos_carta_escogida[0],datos_ultima_carta[0])==0 ||//¿El color de la carta obtenida es igual al de la ultima carta puesta?
				   strcmp(datos_carta_escogida[1],datos_ultima_carta[1])==0 ||//¿El numero de la carta obtenida es igual al de la ultima carta puesta? 
				   strcmp(datos_carta_escogida[0],dato_ja)==0		    ||//¿El color de la carta obtenida es igual al color escogido por el jugador anterior(carta negra colores o +4)?
				   strcmp(datos_carta_escogida[0],"negro")==0			)//¿El color de la carta obtenida es negra?
				{
					printf("Carta Obtenida: %s %s\n",datos_carta_escogida[0],datos_carta_escogida[1]);
					printf("¿Colocar?\n1.- SI.\n2.- NO.\n");
					scanf("%d",&opcion);
					
										

					if(opcion==1)
					{	//se quita la ultima carta puesta
						quitar_ultima_carta(mazo_destino);
						//se transfiere la carta obtenida al puesto de la ultima carta
						transferir_cartas(lista_cartas_origen,carta_aleatoria,mazo_origen,mazo_destino,1);
						efecto(ENVIO,datos_carta_escogida[1]);

						/*  <<liberar memoria>>*/
						liberar_memoria(lista_cartas_jugador,tamano_mazo_jugador);
						liberar_memoria(lista_cartas_origen,tamano_mazo_origen);
						liberar_memoria(ultima_carta,1);
						liberar_memoria(datos_ultima_carta,2);	
						liberar_memoria(datos_carta_escogida,2);
						free(carta_aleatoria);
						/*<<>>*/

						flag=0;//se rompe el ciclo
					}
					else
					{	
						// se transfiere la carta obtenida al mazo del jugador
						transferir_cartas(lista_cartas_origen,carta_aleatoria,mazo_origen,mazo_jugador,1);
						strcpy(ENVIO,"NORMAL_");
						strcat(ENVIO,dato_ja);
						
						/*  <<liberar memoria>>*/
						liberar_memoria(lista_cartas_jugador,tamano_mazo_jugador);
						liberar_memoria(lista_cartas_origen,tamano_mazo_origen);
						liberar_memoria(ultima_carta,1);
						liberar_memoria(datos_ultima_carta,2);	
						liberar_memoria(datos_carta_escogida,2);
						free(carta_aleatoria);
						/*<<>>*/
	
						flag=0;//se rompe el ciclo
					}
				}
				else
				{
					
					printf("Carta Obtenida: %s %s\n",datos_carta_escogida[0],datos_carta_escogida[1]);
					// se transfiere la carta obtenida al mazo del jugador
					transferir_cartas(lista_cartas_origen,carta_aleatoria,mazo_origen,mazo_jugador,1);
					//se transfiere el efecto de la ultima carta para el proximo jugador
					strcpy(ENVIO,"NORMAL_");
					strcat(ENVIO,dato_ja);

					/*  <<liberar memoria>>*/
					liberar_memoria(lista_cartas_jugador,tamano_mazo_jugador);
					liberar_memoria(lista_cartas_origen,tamano_mazo_origen);
					liberar_memoria(ultima_carta,1);
					liberar_memoria(datos_ultima_carta,2);	
					liberar_memoria(datos_carta_escogida,2);
					free(carta_aleatoria);
					/*<<>>*/
					flag=0;//se rompe el ciclo
				}
			}
		}
		
	}
	else// estos efectos si interrumpen la jugada {+2,+4,SALTO}
	{
		if(strcmp(tipo_ja,"+2")==0)
		{
			printf("--==El jugador toma dos cartas y termina su turno==--\n");

			tamano_mazo_origen=contar_cartas(mazo_origen);
			lista_cartas_origen=dar_mazo(mazo_origen,tamano_mazo_origen);
			//se seleccionan 2 indices de cartas del mazo principal
			carta_aleatoria=seleccion_aleatoria(2,tamano_mazo_origen);
			//se transfieren esas dos cartas al mazo del jugador
			transferir_cartas(lista_cartas_origen,carta_aleatoria,mazo_jugador,mazo_destino,2);
			//se cambia el efecto de la jugada anterior
			strcpy(ENVIO,"NORMAL_0");
			//se libera memoria
			liberar_memoria(lista_cartas_origen,tamano_mazo_origen);
			free(carta_aleatoria);
		}
		else if(strcmp(tipo_ja,"+4")==0)
		{
			printf("--==El jugador toma cuatro cartas y termina su turno==--\n");
			tamano_mazo_origen=contar_cartas(mazo_origen);
			lista_cartas_origen=dar_mazo(mazo_origen,tamano_mazo_origen);
			//se seleccionan 4 indices de cartas del mazo principal
			carta_aleatoria=seleccion_aleatoria(4,tamano_mazo_origen);
			//se transfieren esas 4 cartas al mazo del jugador
			transferir_cartas(lista_cartas_origen,carta_aleatoria,mazo_jugador,mazo_destino,4);
			//se cambia el tipo de jugada pero se mantiene el efecto extra de la jugada anterior(color escogido por el jugador anterior)
			strcpy(ENVIO,"NORMAL_");
			strcat(ENVIO,dato_ja);
			//se libera memoria
			liberar_memoria(lista_cartas_origen,tamano_mazo_origen);
			free(carta_aleatoria);
		}
		else/*salto*/
		{
			printf("--==El jugador salta su turno==--\n");
			//se salta el turno y se cambia el efecto
			strcpy(ENVIO,"NORMAL_0");
		}
	}

}


char* menu_jugador(char* mazo_jugador,char* mazo_destino,char* mazo_origen,char* jugada_anterior)
{
	
	char *ENVIO=(char*)malloc(sizeof(char)*20);
	char DATO1[10];
	char DATO2[10];
	char jugador[10];
	int cantidad;
	
	//Se detecta el jugador en turno
	JUGADOR(jugador,mazo_jugador);
	
	printf("--==Turno del %s==--\n",jugador);
	//se extraen los datos de la jugada anterior
	jugada_anterior_datos(DATO1,DATO2,jugada_anterior);
	//se inicia la jugada para el jugador en turno
	jugada(ENVIO,mazo_jugador,mazo_destino,mazo_origen,DATO1,DATO2);
	
	cantidad=contar_cartas(mazo_jugador);
	//Si el jugador se queda con una carta se imprime UNO, si le queda ninguna se aplica un efecto especial que a futuro terminara el juego anunciando al ganador
	if(cantidad==1)
	{	
		printf("¡¡¡¡¡UNO!!!!!\n");
	}
	else if(cantidad==0)
	{
		strcpy(ENVIO,"WIN_0");
	}


	return ENVIO;
}


char** color_tipo(char* carta)
{
	char** CT=malloc(sizeof(char*)*2);
	char temp1[30];
	char* temp2;
	
	CT[0]=(char*)malloc(sizeof(char)*10);
	CT[1]=(char*)malloc(sizeof(char)*10);
	
	strcpy(temp1,carta);

	temp2=strtok(temp1,"_");
	
	strcpy(CT[0],temp2);
	
	temp2=strtok(NULL,"_");
	
	strcpy(CT[1],temp2);
	
	return CT;
}
