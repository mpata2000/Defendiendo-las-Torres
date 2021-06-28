#ifndef __DEFENDIENDO_TORRES_H__
#define __DEFENDIENDO_TORRES_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define NIVEL_1 0
#define NIVEL_2 1
#define NIVEL_3 2
#define NIVEL_4 3
#define MAX_FILAS 30
#define MAX_COLUMNAS 30
#define TOPE_NIVEL_CHICO 15
#define TOPE_NIVEL_GRANDE 20
#define MAX_LONGITUD_CAMINO 200
#define MAX_ENEMIGOS 500
#define MAX_DEFENSORES 50
#define MAX_TORRES 2
#define MAX_NIVELES 4
#define MAX_RUTA_ARCHIVO 100
#define MAX_NOMBRE 40


typedef struct coordenada {
	int fil;
	int col;
} coordenada_t;

typedef struct defensor {
	char tipo;
	int fuerza_ataque;
	coordenada_t posicion;
} defensor_t;

typedef struct torres {
	int resistencia_torre_1;
	int resistencia_torre_2;
	int enanos_extra;
	int coste_enanos_torre_1;
	int coste_enanos_torre_2;
	int elfos_extra;
	int coste_elfos_torre_1;
	int coste_elfos_torre_2;
} torres_t;

typedef struct enemigo {
	int camino;
	int pos_en_camino;
	int vida;
} enemigo_t;

typedef struct nivel {
	coordenada_t camino_1[MAX_LONGITUD_CAMINO];
	int tope_camino_1;
	
	coordenada_t camino_2[MAX_LONGITUD_CAMINO];
	int tope_camino_2;

	defensor_t defensores[MAX_DEFENSORES];
	int tope_defensores;

	enemigo_t enemigos[MAX_ENEMIGOS];
	int tope_enemigos;

	int max_enemigos_nivel;
} nivel_t;

typedef struct juego {
	nivel_t nivel;
	torres_t torres;
	int nivel_actual;
	int critico_legolas;
	int critico_gimli;
	int fallo_legolas;
	int fallo_gimli;
} juego_t;

typedef struct configuracion{
	int resistencia_torre[MAX_TORRES];
	int enanos_nivel[MAX_NIVELES];
	int elfos_nivel[MAX_NIVELES];
	int enanos_extra;
	int coste_torres_enanos[MAX_TORRES];
	int elfos_extra;
	int coste_torres_elfos[MAX_TORRES];
	int fallo_enano,critico_enano;
	int fallo_elfo, critico_elfo;
	float velocidad;
	char ruta_camino[MAX_RUTA_ARCHIVO];
	int listar;
} configuracion_t;

typedef struct rutas{
	char ruta_config[MAX_RUTA_ARCHIVO];
	bool hay_config;
	char ruta_ranking[MAX_RUTA_ARCHIVO];
	char ruta_caminos[MAX_RUTA_ARCHIVO];
	char ruta_grabacion[MAX_RUTA_ARCHIVO];
	bool hay_grabacion;
}rutas_t;


/*
 * Inicializará el juego, cargando la informacion de las torres y
 * los ataques críticos y fallo de Legolas y Gimli.
 * NO inicializará el primer nivel.
 */
void inicializar_juego(juego_t* juego,configuracion_t configuracion, int viento, int humedad, char animo_legolas, char animo_gimli);

/*
 * Recibe un juego con todas sus estructuras válidas. 
 * El juego se dará por ganado si el juego está en el ultimo nivel y éste ha sido terminado.
 * El juego se dará por perdido, si alguna de las torres llega a 0 en su resistencia.
 * Devolverá:
 * >  0 si el estado es jugando.
 * > -1 si el estado es perdido.
 * >  1 si el estado es ganado.
 */
int estado_juego(juego_t juego);

/*
 * Recibe un nivel con todas sus estructuras válidas. 
 * El nivel se dará por ganado cuando estén TODOS los orcos de ese 
 * nivel muertos (esto es, con vida menor o igual a 0).
 * Devolverá:
 * >  0 si el estado es jugando.
 * >  1 si el estado es ganado.
 */
int estado_nivel(nivel_t nivel);

/* 
 * Agregará un defensor en el nivel recibido como parametro.
 * Devolverá:
 * >  0 si pudo agregar el defensor correctamente.
 * > -1 si no pudo (la coordenada es parte del camino de ese nivel, 
 * existe otro defensor, etc.)
 */
int agregar_defensor(nivel_t* nivel, coordenada_t posicion, char tipo);

/*
 * Jugará un turno y dejará el juego en el estado correspondiente.
 * Harán su jugada enanos, elfos y orcos en ese orden.
 */
void jugar_turno(juego_t* juego);

/* 
 * Mostrará el mapa dependiendo del nivel en que se encuentra el jugador.
 */
void mostrar_juego(juego_t juego);

#endif /* __DEFENDIENDO_TORRES_H__ */
