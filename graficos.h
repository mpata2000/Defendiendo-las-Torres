#ifndef __GRAFICOS_H__
#define __GRAFICOS_H__

#include <stdio.h>
#include <stdbool.h>
#include "defendiendo_torres.h"
#include "archivos.h"
#include "utiles.h"


//Recibe: Un selector por referencia
//Post Imprime un menu en el que se puede "navegar"
void mostrar_caracteristicas_juego(int* selector);

//Post imprime una pantalla de carga de presentacion del juego
void mostrar_carga_presentacion();

//Pre: Recibe un nivel valido en el que se va a jugar
//Post: Imprime una pantalla de carga para el nivel
void mostrar_carga(int nivel);

//Pre: El juego tiene que haber finalizado y ecive un juego_t valido 
//Post: Imprime una imagen distinta dependiendo si ganaste o perdiste
void mostrar_final_juego(juego_t juego);

//Pre: Haber ganado un nivel chico(Nivel 1 y 2)
//Post Imprime un texto abajo de mostrar juego indicando que se gano el nivel
void mostra_horda_derrotada_nivel_chico(juego_t juego);

//Pre: Haber ganado un nivel grande(Nivel 3 y 4)
//Post Imprime un texto abajo de mostrar juego indicando que se gano el nivel
void mostra_horda_derrotada_nivel_grande(juego_t juego);

//Pre: Estar creando un camino custom, recive un camino_t valido y en el nivel que se esta creando el camino
//Post Imprime el camino que se esta creando
void mostrar_crear_camino(camino_nivel_t caminos, int nivel);

/*
*Este procedimiento imprime la caracteristicas del defensor
*	que va a ser agregado
*/
void caracteristicas_defensor(juego_t defendiendo_torres,char tipo);

//Pre: Recibe los defensores que se van a agregar y el nivel
//Post: Imprime la caracteristicas del defensor siendo agregado
void mostrar_defensores_por_agregar(int por_agregar_enano,int por_agregar_elfo,int nivel);

//Pre: Recibe un string
//Post: Imprime la ingresar nombre y el usuario debe ingresar su nombre.
void mostrar_ingresar_nombre(char nombre[MAX_NOMBRE]);



//Pre: Recibe el numero de torre de que se esta preguntando y la resistencia maxima que se le puede poner
//Post: Imprime en pantalla las condiciones validas de preguntar resistencia torres
void mostrar_preguntar_resistencia_torres(int numero_torre, int max_resistencia_torres);

//Pre: Recibe el nivel del que se esta preguntando, el nombre del tipo de defensor y el maximo de defensores de los niveles
//Post: Imprime en pantalla las condiciones validas de preguntar defensores nivel
void mostrar_preguntar_defensores_nivel(int nivel, char nombre_defensor[MAX_NOMBRE],int max_def_nivel);

//Pre: Recibe el numero de torre de que se esta preguntando y la resistencia maxima que se le puede poner
//Post: Imprime en pantalla las condiciones validas de preguntar defensores extra
void mostrar_preguntar_defensores_extra(char nombre_defensor_extra[MAX_NOMBRE], int max_coste_def, int max_def_extra);

//Pre: Recibe el nombre del tipo de defensor y los valores maximos que se pueden asignar
//Post: Imprime en pantalla las condiciones validas de preguntar animos defensores
void mostrar_preguntar_animos_defensor(char nombre_defensor_extra[MAX_NOMBRE], int max_animos);

//Pre: Recibe la velocidad maxima del juego
//Post: Imprime en pantalla las condiciones validas de preguntar velocidad
void mostrar_preguntar_velocidad(int max_velocidad);

//Post: Imprime en pantalla las condiciones validas de preguntar ruta caminos
void mostrar_preguntar_ruta_camino();

#endif/*__GRAFICOS_H__*/