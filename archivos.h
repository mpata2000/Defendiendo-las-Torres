#ifndef __ARCHIVOS_H__
#define __ARCHIVOS_H__

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "defendiendo_torres.h"
#include "comandos.h"
#include "utiles.h"

#define NO_EXISTE_ARCHIVO -1
#define EXISTE_ARCHIVO 0




typedef struct caminos_nivel{
    coordenada_t camino_1[MAX_LONGITUD_CAMINO];
	int tope_camino_1;
	coordenada_t torre_1;
    
	coordenada_t camino_2[MAX_LONGITUD_CAMINO];
	int tope_camino_2;
	coordenada_t torre_2;
}camino_nivel_t;

typedef struct jugador{
	char nombre[MAX_NOMBRE];
	int puntaje;
}jugador_t;

/*
* Recibe: -> La ruta de la configuracion sin extension.
*
* Procedimiento:->Se llena configuracion_t con datos validos ingresados por el usuario.
*
* Post:-> Crea un archivo ordenado con los datos de configuracion_t.
*/
void crear_configuracion(char ruta_configuracion[MAX_RUTA_ARCHIVO]);

/*
* Pre: Que el jugador haya ingresado un comando valido con una configuracion valida
* Recibe: -> La ruta de la configuracion sin extension.
*         -> Una estructura configuracion_t por referencia.
*
* Procedimiento: Carga los contenidos del archivo en configuracion_t.
*
* Post:-> Devolvera -1 si el archivo del camino no existe.
*	   -> Devolvera 0 si el archivo fue cargado con exito.
*/
int leer_configuracion(configuracion_t* configuracion,char ruta_configuracion[MAX_RUTA_ARCHIVO]);


//Pre: Recive una configuracion_t valida y inicializada
//Post: Carga los valores correspondientes a cada parte de configuracion_t.
void llenar_valores_standard_config(configuracion_t *configuracion);

/* 
* Pre: Que el jugador haya ingresado los comandos correctos
*      ->Recive: Un nombre para los caminos custom sin extension
*
* Post: Crea un archivo con los caminos custom
*/
void crear_caminos_custom(char ruta_camino[MAX_RUTA_ARCHIVO]);

/*
* Pre: Que la configuracion tenga un archivo que sea valido y este ordenado por nivel
* Recibe: -> La ruta del camino sin extension.
*         -> Una estructura caminos_nivel_t.
*
* Procedimiento: Carga los contenidos del archivo en caminos_nivel_t.
*
* Post:-> Devolvera -1 si el archivo del camino no existe.
*	   -> Devolvera 0 si el archivo fue cargado con exito.
*/
int leer_caminos(char ruta_camino[MAX_RUTA_ARCHIVO],camino_nivel_t caminos_nivel[MAX_NIVELES]);

/* Pre: Recibe una ruta de la partida grabada con extension y a la velocidad que se quiere mostrar la repe
*
*  Procedimiento: -> Se verifica si el archivo existe
*                 -> Si existe se lee el archivo, carga en juego_t y se lo muestra hata que termine el archivo
*/
void mostrar_video_partida(char ruta_grabacion[MAX_RUTA_ARCHIVO],float velocidad);


/*
* Pre: Que haya terminado el juego
* Recibe: -> La ruta del ranking sin extension(El mismo nombre de la configuracion).
*         -> Una estructura juegador_t valida
*
* Post:-> Si el ranking existe se lo agregara al ranking de forma ordenada
*	   -> Si no existe el ranking se crea un nuevo ranking que contiene el nuevo jugador
*/
void agregar_ranking(char ruta_ranking[MAX_RUTA_ARCHIVO],jugador_t jugador);


/* 
* Recibe: -> La ruta del ranking sin extension
*         -> La cantidad de jugadores del ranking a listar(si recibe el default(-1) se listan todos)
*
* Post: Imprime los jugadores del ranking solicitado si el archivo existe
 */
void mostrar_ranking(char ruta_config[MAX_RUTA_ARCHIVO],int listar);

#endif/*__ARCHIVOS_H__*/