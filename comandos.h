#ifndef __COMANDOS_H__
#define __COMANDOS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "defendiendo_torres.h"
#include "archivos.h"


#define MAX_NOMBRE_COMANDO 100
#define MAX_COMANDOS 15
#define COMANDO_NO_FUNCIONO -1
#define COMANDO_FUNCIONO 0

typedef struct comando{
	char key[MAX_NOMBRE_COMANDO];
	char valor[MAX_NOMBRE_COMANDO];
}comando_t;

/* 
* Pre: Que el jugador haya ingresado mas de un argumento
*
* Post: Carga los argumentos que contienen un igual en comandos_t por key (El nombre del comando) y valor
*/
void parse_comando(int argc, char* argv[],comando_t comando[MAX_COMANDOS], size_t* num_comando);

/* 
* Pre: Recive un nombre de archivo valido(Sin puntos en medio).
* Post: Le saca la extension al archivo(si la tenia).
*/
void sacar_extension_archivo(char nombre_archivo[MAX_NOMBRE_COMANDO]);


void comandos_defendiendo_torres(configuracion_t* config, comando_t comandos[MAX_COMANDOS],size_t num_comando,rutas_t* rutas);

int comandos_simples(int argc, char* argv[],char nombre_archivo[MAX_NOMBRE_COMANDO]);

#endif/*__COMANDOS_H__*/