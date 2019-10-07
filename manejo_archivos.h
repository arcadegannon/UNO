#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

/*---===PROTOTIPOS===---*/

void inicio();
/*****
* void inicio
******
* prepara los archivos y carpetas necesarios para el inicio del juego
******
* input:
*	none
*
******
* returns:
*	none
*****/

void repartir(int cantidad,char* mazo_jugador,char* mazo_origen);
/*****
* void repartir
******
* le da a un jugador una cantidad dada de cartas de forma aleatoria
******
* input:
*	int cantidad	  : numero de cartas a dar
*	char* mazo_jugador: directorio donde se encuentra el mazo del jugador
*	char* mazo_origen : directorio donde se encuentra el mazo principal
******
* returns:
*	none
*****/

void transferir_cartas(char** cartas,int* seleccion_cartas,char* mazo_origen,char* mazo_destino,int cantidad);
/*****
* void transferir_cartas
******
* transfiere una cantidad dada de cartas de un mazo origen a uno destino
******
* input:
*	char** cartas	     : arreglo de strings que contiene los nombres de los archivos de texto de un mazo origen
*	int* seleccion_cartas: arreglo de enteros que contiene los indices de las cartas a transferir
*	char* mazo_origen    : directorio donde se encuentra el mazo origen
*	char* mazo_destino   : directorio donde se encuentra el mazo destino
*	int cantidad         : numero de cartas a transferir
******
* returns:
*	none
*****/

void ver_cartas(char** mazo,int cantidad);
/*****
* void ver_cartas
******
* muestra las cartas de un mazo con sus respectivos indices +1
******
* input:
*	char** mazo	     : arreglo de strings que contiene los nombres de los archivos de texto de un mazo
*	int cantidad         : numero de cartas en el mazo
******
* returns:
*	none
*****/

void quitar_ultima_carta(char* last_card);
/*****
* void quitar_ultima_carta
******
* elimina la unica carta ubicada en la carpeta last_card
******
* input:
*	char* last_card: directorio donde se encuentra la carpeta last_card
******
* returns:
*	none
*****/

void dar_carta(char* nombre_carta,char* mazo);
/*****
* void dar_carta
******
* crea una carta en un mazo dado
******
* input:
*	char* nombre_carta: nombre del archivo de texto que representa a una carta
*	char* mazo	  : directorio de un mazo
******
* returns:
*	none
*****/

void quitar_carta(char* nombre_carta,char* mazo);
/*****
* void quitar_carta
******
* elimina una carta de un mazo dado
******
* input:
*	char* nombre_carta: nombre del archivo de texto que representa a una carta
*	char* mazo	  : directorio de un mazo
******
* returns:
*	none
*****/

void crear_cartas_iniciales(char* nombre_cartas);
/*****
* void crear_cartas_iniciales
******
* crea todas las cartas del juego
******
* input:
*	char* nombre_carta: nombre del archivo de texto que contiene el nombre de cada carta a crear
******
* returns:
*	none
*****/

void crear_carta(char* nombre_carta);
/*****
* void crear_carta
******
* crea el archivo de texto para una carta
******
* input:
*	char* nombre_carta: nombre de la carta
******
* returns:
*	none
*****/

void crear_carpetas(char** directorios,int cantidad);
/*****
* void crear_carpetas
******
* crea las carpetas necesarias para el funcionamiento del programa
******
* input:
*	char** directorio: arreglo con los directorios de cada carpeta
*	int cantidad     : cantidad de carpetas a crear
******
* returns:
*	none
*****/

void liberar_memoria(char** lista,int size);
/*****
* void liberar_memoria
******
* libera la memoria utilizada por un arreglo de strings
******
* input:
*	char** lista: arreglo de strings
*	int size    : cantidad de strings en el arreglo
******
* returns:
*	none
*****/

void ver_archivos(char* directorio);
/*****
* void ver_archivos
******
* muestra los archivos que se encuentran en una carpeta
******
* input:
*	char* directorio: nombre del directorio
******
* returns:
*	none
*****/

char** dar_mazo(char* directorio,int cantidad);
/*****
* char** dar_mazo
******
* entrega un arreglo con los nombres de cada archivo de texto (carta) en un mazo dado
******
* input:
*	char* directorio: directorio del mazo
*	int cantidad    : cantidad de cartas en el mazo
******
* returns:
*	char** : arreglo con los nombres de cada carta en el mazo
*****/



int contar_cartas(char* mazo);
/*****
* int contar_cartas
******
* cuenta la cantidad de cartas que se encuentra en un mazo
******
* input:
*	char* mazo: directorio del mazo
******
* returns:
*	int : cantidad de cartas en el mazo
*****/

int * seleccion_aleatoria(int N,int tamano_mazo);
/*****
* int* seleccion_aleatoria
******
* selecciona N enteros (indices) de forma aleatoria con un valor maximo dado
******
* input:
*	int N	       : cantidad a seleccionar
*	int tamano_mazo: valor maximo
******
* returns:
*	int* : arreglo con los enteros obtenidos
*****/
