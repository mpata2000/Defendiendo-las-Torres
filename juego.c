#include "animos.h"
#include "defendiendo_torres.h"
#include "archivos.h"
#include "comandos.h"
#include "graficos.h"
#include "utiles.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


const int VIENTO_BASE = 50;
const int HUMEDAD_BASE = 50;
const char ANIMO_GIMLI_BASE = 'R';
const char ANIMO_LEGOLAS_BASE = 'R';

const char SI='S';
const char NO='N';

const char AMBOS = 'A';
const char ELFO  = 'L';
const char ENANO = 'G';
const char ORCOS = 'O';
const char TORRE = 'T';
const char ENTRADA = 'E';
const int FILA_NORTE = 0;
const int FILA_SUR = 19;
const int COLUMNA_ESTE= 14;
const int COLUMNA_OESTE = 0;

const int MAX_FILA_NIVEL_CHICO = 15;
const int MAX_COLUMNA_NIVEL_GRANDE = 20;

const int MAX_ENANOS_NIVEL[] = {5,0,3,4};
const int MAX_ELFOS_NIVEL[] = {0,5,3,4};
const int MAX_ENEMIGOS_NIVEL[] = {100,200,300,500};
const int ORCOS_PARA_DEFENSOR_EXTRA_NIVEL[] = {25,50,50,50};

const int VALOR_DEFENSOR_EXTRA = 50;
const int ATAQUE_BASE_ENANO = 60;
const int ATAQUE_CRITICO_ENANO = 100;
const int ATAQUE_BASE_ELFO = 30;
const int ATAQUE_CRITICO_ELFO = 70;
const int VIDA_BASE_ORCO = 200;
const int VIDA_EXTRA_ORCO = 101;
const int NO_SE_PUDO_AGREGAR = -1;
const char NORTE = 'N';
const char SUR = 'S';
const char ESTE = 'E';
const char OESTE = 'O';
const int JUGANDO = 0;
const int PERDIO = -1;
const int GANO =  1 ;
const int EMPEZAR_JUEGO_SIN_ANIMOS = 5;
const int EMPEZAR_JUEGO_CON_ANIMOS = 6;
const int MENU = 0;
const int DEFAULT = -1;



/*Parte: Funciones Generales*/
bool coste_enanos_menor_resistencia(torres_t torre){
	return (torre.resistencia_torre_1 > torre.coste_enanos_torre_1)&&(torre.resistencia_torre_2 > torre.coste_enanos_torre_2);
}
bool coste_elfos_menor_resistencia(torres_t torre){
	return (torre.resistencia_torre_1 > torre.coste_elfos_torre_1)&&(torre.resistencia_torre_2 > torre.coste_elfos_torre_2);
}
//Pre: Recibe un nivel valido mientras que se esta jugando, una constante de cada cuanto se puede agregar un defensor
//Post: Devuelve true si se cuando se puede agregar un enano extra
bool se_puede_agregar_enano(juego_t defendiendo_torres, int orcos_para_def_extra){
	return (defendiendo_torres.nivel.tope_enemigos % orcos_para_def_extra == 0) && (defendiendo_torres.nivel_actual != NIVEL_2) && coste_enanos_menor_resistencia(defendiendo_torres.torres) && (defendiendo_torres.torres.enanos_extra > 0) && (defendiendo_torres.nivel.tope_enemigos < defendiendo_torres.nivel.max_enemigos_nivel);
}

//Pre: Recibe un nivel valido mientras que se esta jugando, una constante de cada cuanto se puede agregar un defensor
//Post: Devuelve true si se cuando se puede agregar un eldo extra
bool se_puede_agregar_elfo(juego_t defendiendo_torres, int orcos_para_def_extra){
	return (defendiendo_torres.nivel.tope_enemigos % orcos_para_def_extra == 0) && (defendiendo_torres.nivel_actual != NIVEL_1) && (defendiendo_torres.nivel.tope_enemigos > 0) && coste_elfos_menor_resistencia(defendiendo_torres.torres) && (defendiendo_torres.torres.elfos_extra > 0) && (defendiendo_torres.nivel.tope_enemigos < defendiendo_torres.nivel.max_enemigos_nivel);
}


//Pre: Recibe una estructura coordenada mientras que queden defensores por poner del nivel
//Post: Devuelve la estructura con los datos preguntados al usuario
void pregunta_pos_agregar_def(coordenada_t *posicion){
	printf("\n  Fila del nuevo defensor: ");
	scanf("%i", &(*posicion).fil);
	printf("  Columna del nuevo defensor:  ");
	scanf("%i", &(*posicion).col);			
}

//Pre: Que se pueda agregar un defensor extra
//Post: Devuelve un tipo de defensor valido
char preguntar_tipo_defensor(){
	char tipo;

	system("clear");
	mostrar_juego(*defendiendo_torres);
	printf("De que tipo de defensor desea agregar Enano(G) o Elfo(L): ");
	scanf(" %c", &tipo);

	while( tipo != ENANO && tipo != ELFO){
		system("clear");
		mostrar_juego(*defendiendo_torres);
		printf("\n   Parece que ingreso un caracter incorrecto");
		printf("\n   De que tipo de defensor desea agregar Enano(G) o Elfo(L): ");
		scanf(" %c", &tipo);
	}
	return tipo;
}

/*
* Pre: Recive un juego_t valido y los enemigos para un defensor extra valido para ese nivel
* Post: Devuelve AMBOS(A) si se puede agregar ambos.
*                ELFO(L) o ENANO(G) si se puede agregar uno de los dos
*                0 si no se puede agragar un defensor extra
*/ 
char tipo_def_extra(juego_t* defendiendo_torres, int enemigos_para_defensor){
	char tipo = 0;

	if(se_puede_agregar_enano((*defendiendo_torres), enemigos_para_defensor) && se_puede_agregar_elfo((*defendiendo_torres), enemigos_para_defensor)){
		tipo = AMBOS;
	}else if(se_puede_agregar_enano((*defendiendo_torres), enemigos_para_defensor)){
		tipo = ENANO;
	}else if(se_puede_agregar_elfo((*defendiendo_torres), enemigos_para_defensor)){
		tipo = ELFO;
	}
	return tipo;	
}

/*
* Pre: Recibe un juego valido, el tipo de defensor que se quiere colocar y los defensores restantes
* Post: Agrega un defensor en la posicion valida ingresada por el jugador
*/
void colocar_defensor(juego_t* defendiendo_torres, char tipo,int enanos_por_agregar, int elfos_por_agregar){
	int i=0;
	coordenada_t posicion;
	do{
		system("clear");
		mostrar_juego(*defendiendo_torres);
		mostrar_defensores_por_agregar(enanos_por_agregar,elfos_por_agregar, defendiendo_torres->nivel_actual);
		caracteristicas_defensor(*defendiendo_torres,tipo);
		if(i > 0){
			printf("\n\n  La posicion fila = %i, columna = %i es invalida, ingrese nuevas coordenada",posicion.fil,posicion.col);
			printf("\n  Recuerde que un defensor debe ser colocado al lado de un camino(pero no sobre el)\n  y no puede estar un defensor en esa posicion\n");
		}
		pregunta_posicion(&posicion);
		i++;
	}while(agregar_defensor( &((*defendiendo_torres).nivel), posicion, tipo) == NO_SE_PUDO_AGREGAR);
}

//Pre:Recibe una estructura juego valida, cuando la torre tiene mas
//Post: Agrega un defensor al vector defeensores y le resta vida a la torre correspondiente
void agregar_defensor_extra(juego_t* defendiendo_torres, int enemigos_para_defensor){
	char aux;
	char tipo;
	
	tipo = tipo_def_extra(defendiendo_torres,enemigos_para_defensor);

	if(tipo != 0){
		printf(" Desea agragar un defensor extra? Esto cuesta 50 puntos de a su Torre correspondiente\n Si/No(S para si N para no): ");
		scanf(" %c",&aux);
		while(aux != SI && aux != NO){
			system("clear");
			mostrar_juego(*defendiendo_torres);
			printf("\n   Parese que no ingresaste el caracter correcto\n   Desea agregar un defensor extra? Si/No(S para si N para no): ");
			scanf(" %c", &aux);
		}

		if(aux == SI){
			if(tipo == AMBOS){
				tipo = preguntar_tipo_defensor(*defendiendo_torres);
			}
			
			colocar_defensor(defendiendo_torres,tipo,0,0);

			if(tipo == ELFO){
				(*defendiendo_torres).torres.resistencia_torre_2 -= VALOR_DEFENSOR_EXTRA; 
				(*defendiendo_torres).torres.elfos_extra--;
			}else{
				(*defendiendo_torres).torres.resistencia_torre_1 -= VALOR_DEFENSOR_EXTRA; 
				(*defendiendo_torres).torres.enanos_extra--;	
			}
		}
	}
}


//Pre:Recibe una coordenada valida, un punto cardinal y la una variable ara el punto random
//Post: Inicializa la coordenada segun el punto cardinal
void inicializar_coordenada_cardinal(coordenada_t* coordenada, char punto_cardinal, int variable_max){
	if(punto_cardinal == NORTE){
		(*coordenada).fil= FILA_NORTE;
		(*coordenada).col= rand() % variable_max;
	}else if(punto_cardinal == SUR){
		(*coordenada).fil= FILA_SUR;
		(*coordenada).col= rand() % variable_max;
	}else if(punto_cardinal == ESTE){
		(*coordenada).fil= rand() % variable_max;
		(*coordenada).col= COLUMNA_ESTE;
	}else if(punto_cardinal == OESTE){
		(*coordenada).fil= rand() % variable_max;
		(*coordenada).col= COLUMNA_OESTE;
	}
}


//Pre: Recibe dos ecoordenadas
//Post: Inicializa las coordenadas valida para el  nivel 1
void inicializar_coordenadas_nivel(int nivel,coordenada_t* entrada_1,coordenada_t* torre_1,coordenada_t* entrada_2,coordenada_t* torre_2){
	switch (nivel){
		case NIVEL_1:
			inicializar_coordenada_cardinal(entrada_1, ESTE, MAX_FILA_NIVEL_CHICO);
			inicializar_coordenada_cardinal(torre_1, OESTE, MAX_FILA_NIVEL_CHICO);
			break;
		case NIVEL_2:
			inicializar_coordenada_cardinal(entrada_2, OESTE, MAX_FILA_NIVEL_CHICO);
			inicializar_coordenada_cardinal(torre_2, ESTE, MAX_FILA_NIVEL_CHICO);
			break;
		case NIVEL_3:
			inicializar_coordenada_cardinal(entrada_1, NORTE,MAX_COLUMNA_NIVEL_GRANDE);
			inicializar_coordenada_cardinal(entrada_2, NORTE, MAX_COLUMNA_NIVEL_GRANDE);
			inicializar_coordenada_cardinal(torre_1, SUR, MAX_COLUMNA_NIVEL_GRANDE);
			inicializar_coordenada_cardinal(torre_2, SUR, MAX_COLUMNA_NIVEL_GRANDE);
			
			while((*entrada_1).col == (*entrada_2).col){
				inicializar_coordenada_cardinal(entrada_2, NORTE, MAX_COLUMNA_NIVEL_GRANDE);
			}
			while((*torre_1).col == (*torre_2).col){
				inicializar_coordenada_cardinal(torre_2, SUR, MAX_COLUMNA_NIVEL_GRANDE);
			}
			break;
		case NIVEL_4:
			inicializar_coordenada_cardinal(entrada_1, SUR ,MAX_COLUMNA_NIVEL_GRANDE);
			inicializar_coordenada_cardinal(entrada_2, SUR ,MAX_COLUMNA_NIVEL_GRANDE);
			inicializar_coordenada_cardinal(torre_1, NORTE, MAX_COLUMNA_NIVEL_GRANDE);
			inicializar_coordenada_cardinal(torre_2, NORTE, MAX_COLUMNA_NIVEL_GRANDE);

			while((*entrada_1).col == (*entrada_2).col){
				inicializar_coordenada_cardinal(entrada_2, SUR , MAX_COLUMNA_NIVEL_GRANDE);
			}
			while((*torre_1).col == (*torre_2).col){
				inicializar_coordenada_cardinal(torre_2, NORTE, MAX_COLUMNA_NIVEL_GRANDE);
			}
			break;
	}
}



//Pre: Recibe el nivel que se va a jugar
//Post Devuelve la cantidad maxima de enemigos del nive
int enemigos_nivel(int nivel){
	return MAX_ENEMIGOS_NIVEL[nivel];
}

//Pre: Recibe el nivel actual
//Post: Devuelve la cantidad de enemigos que tienen que entrar para poner el defensor extra
int calculos_enemigos_por_defensor(int nivel){
	return ORCOS_PARA_DEFENSOR_EXTRA_NIVEL[nivel];
}

// Pre: Que no se haya cargado en caminos_t los caminos custom de un archivo
// Post: Genera caminos al azar y los carga en juego_t
void generar_caminos_random(juego_t* defendiendo_torres){
	coordenada_t entrada_1;
	coordenada_t torre_1;
	coordenada_t entrada_2;
	coordenada_t torre_2;

	inicializar_coordenadas_nivel(defendiendo_torres->nivel_actual, &entrada_1,&torre_1, &entrada_2, &torre_2);
	
	if(defendiendo_torres->nivel_actual != NIVEL_2){
		obtener_camino((*defendiendo_torres).nivel.camino_1, &((*defendiendo_torres).nivel.tope_camino_1),entrada_1, torre_1);
	}
	if(defendiendo_torres->nivel_actual != NIVEL_1){
		obtener_camino((*defendiendo_torres).nivel.camino_2, &((*defendiendo_torres).nivel.tope_camino_2),entrada_2, torre_2);
	}
}


// Pre: Que se haya cargado en caminos_t los caminos custom de un archivo
// Post: Carga caminos_t en juegos_t 
void cargar_caminos_custom(juego_t* defendiendo_torres,camino_nivel_t caminos_nivel[MAX_NIVELES]){	
	defendiendo_torres->nivel.tope_camino_1 = caminos_nivel[defendiendo_torres->nivel_actual].tope_camino_1;
	defendiendo_torres->nivel.tope_camino_2 = caminos_nivel[defendiendo_torres->nivel_actual].tope_camino_2;

	for(int i=0; i < defendiendo_torres->nivel.tope_camino_1; i++){
		(*defendiendo_torres).nivel.camino_1[i] = caminos_nivel[defendiendo_torres->nivel_actual].camino_1[i];
	}

	for(int i=0; i < defendiendo_torres->nivel.tope_camino_2; i++){
		(*defendiendo_torres).nivel.camino_2[i] = caminos_nivel[defendiendo_torres->nivel_actual].camino_2[i];
	}	
}

//Pre: Recibe cuatro estructuras de coordenadas y una estructura juego valida
//Post: Inicializa la estructura juego con las caracteristicas del nivel 4
void inicializar_nivel(juego_t* defendiendo_torres,camino_nivel_t caminos_nivel[MAX_NIVELES], bool usar_caminos_custom){
	(*defendiendo_torres).nivel.tope_camino_1 = 0;
	(*defendiendo_torres).nivel.tope_camino_2 = 0;
	(*defendiendo_torres).nivel.tope_defensores = 0;
	(*defendiendo_torres).nivel.tope_enemigos = 0;
	(*defendiendo_torres).nivel.max_enemigos_nivel = enemigos_nivel(defendiendo_torres->nivel_actual);
	
	if(usar_caminos_custom){
		cargar_caminos_custom(defendiendo_torres,caminos_nivel);
	}else{
		generar_caminos_random(defendiendo_torres);
	}


}
	
/* 
* Recibe un juego valido, con un nivel inicializado
* ->Agrega todos los defensores del nivel
*/
void agregar_defensa_inicial(juego_t* defendiendo_torres, configuracion_t configuracion){
	int i = 0;
	coordenada_t posicion;
	int enanos_por_agregar = configuracion.enanos_nivel[defendiendo_torres->nivel_actual]; 
	int elfos_por_agregar = configuracion.elfos_nivel[defendiendo_torres->nivel_actual];

	while(enanos_por_agregar > 0){
		colocar_defensor(defendiendo_torres,ENANO,enanos_por_agregar,elfos_por_agregar);
		enanos_por_agregar--;
	}
	while(elfos_por_agregar > 0){
		colocar_defensor(defendiendo_torres, ELFO,enanos_por_agregar, elfos_por_agregar);
		elfos_por_agregar--;
	}
}



/*
*Este procedimiento recibe una estructura juego inicializado 
*Se agregara los defensores correspondientes aa nivel 
*Por cada cuarto de enemigos maximos del nivel se dejara agregar un defensor extra
*Se jugara por turnos hasta que se gane el nivel o pierda
*/
void jugar_nivel(juego_t* defendiendo_torres,configuracion_t configuracion, FILE* archivo_repe){
	int enemigos_para_defensor = calculos_enemigos_por_defensor(defendiendo_torres->nivel_actual);

	agregar_defensa_inicial(defendiendo_torres,configuracion);

	while((estado_nivel(defendiendo_torres->nivel) == JUGANDO) && (estado_juego(*defendiendo_torres) != PERDIO)){
		jugar_turno(defendiendo_torres);
		mostrar_juego(*defendiendo_torres);
		detener_el_tiempo(configuracion.velocidad);

		agregar_defensor_extra(defendiendo_torres, enemigos_para_defensor);
		

		if(estado_nivel(defendiendo_torres->nivel) == GANO){
			if(defendiendo_torres->nivel_actual == NIVEL_1 || defendiendo_torres->nivel_actual == NIVEL_2){
				mostra_horda_derrotada_nivel_chico(*defendiendo_torres);
			}else{
				mostra_horda_derrotada_nivel_grande(*defendiendo_torres);
			}	
		}

		if(archivo_repe){
			fwrite(defendiendo_torres,sizeof(juego_t),1,archivo_repe);
		}
		system("clear");
	}
}

void jugar(juego_t* defendiendo_torres, configuracion_t configuracion, rutas_t rutas_juego){
	FILE* archivo_repe;
	camino_nivel_t caminos_custom[MAX_NIVELES];
	bool usar_caminos_custom = false;

	if(strcmp(configuracion.ruta_camino, "-1") != 0){
		if(leer_caminos(configuracion.ruta_camino, caminos_custom) == EXISTE_ARCHIVO){
			usar_caminos_custom = true;
		}
	}
	if(rutas_juego.hay_grabacion){
		archivo_repe = fopen(rutas_juego.ruta_grabacion, "w");
	}

	while(estado_juego(*defendiendo_torres) == JUGANDO){
		defendiendo_torres->nivel_actual ++;
		inicializar_nivel(defendiendo_torres,caminos_custom,usar_caminos_custom);
		mostrar_carga(defendiendo_torres->nivel_actual);
		jugar_nivel(defendiendo_torres, configuracion,archivo_repe);
	}

	if(rutas_juego.hay_grabacion){
		fclose(archivo_repe);
	}
}

//Pre: Recibe la configuracion usada por el jugador
//Post:Devuelve la suma de la resistencia iniciales de las torres que uso el jugador
int suma_resistencia_torres(configuracion_t configuracion){
	int suma = 0;

	for (size_t i = 0; i < MAX_TORRES; i++){
		suma += configuracion.resistencia_torre[i];
	}
	return suma;
}

//Pre: Recibe la configuracion usada por el jugador
//Post:Devuelve la cantidad de defensores iniciales que uso el jugador
int suma_defensores_iniciales(configuracion_t configuracion){
	int suma = 0;

	for (size_t i = 0; i < MAX_TORRES; i++){
		suma += configuracion.enanos_nivel[i];
		suma += configuracion.elfos_nivel[i];
	}
	return suma;
}
//Pre: Recibe la configuracion usada y los orcos muertos
//Post:Devuelve el puntaje del jugador
int calcular_puntaje(configuracion_t configuracion,int orcos_muertos){
	return ((orcos_muertos*1000)/(suma_resistencia_torres(configuracion)+suma_defensores_iniciales(configuracion)+ configuracion.elfos_extra +configuracion.enanos_extra));
}

//Pre: Perder el juego en algun nivel
//Post:Dvuelve la cantidad de orcos que murieron ese nivel
int orcos_muertos_nivel(enemigo_t enemigos[MAX_ENEMIGOS],int tope_enemigos){
	int suma = 0;
	for(int i=0;i<tope_enemigos; i++){
		if(enemigos[i].vida <= 0){
			suma++;
		}
	}
	return suma;
}

//Pre: Que el juego haya terminado(Recibe un juego valido y el estado en el que termino el juego)
//Post: Devuelve la cantidad de orcos que murieron en el juego
int orcos_muertos_total(juego_t defendiendo_torres, int estado_juego){
	int suma = 0;
	
	for(int i = 0; i<defendiendo_torres.nivel_actual;i++){
		suma+=MAX_ENEMIGOS_NIVEL[i];
	}
	if(estado_juego == PERDIO){
		suma-=MAX_ENEMIGOS_NIVEL[defendiendo_torres.nivel_actual];
		suma+=orcos_muertos_nivel(defendiendo_torres.nivel.enemigos, defendiendo_torres.nivel.tope_enemigos);
	}

	return suma;
}

/* Recibe una configuracion_t por referencia y lo inicializa en su valor DEFAULT*/
void inicializar_configuracion_estandar(configuracion_t* configuracion){
	for (size_t i = 0; i < MAX_TORRES; i++){
		configuracion->resistencia_torre[i] = DEFAULT;
		configuracion->coste_torres_enanos[i] = DEFAULT;
		configuracion->coste_torres_elfos[i] = DEFAULT;
	}
	for (size_t i = 0; i < MAX_NIVELES; i++){
		configuracion->enanos_nivel[i] = DEFAULT;
		configuracion->elfos_nivel[i] = DEFAULT;
	}

	configuracion->enanos_extra = configuracion->elfos_extra = DEFAULT;
	configuracion->fallo_enano = configuracion->critico_enano = DEFAULT;
	configuracion->fallo_elfo = configuracion->critico_elfo = DEFAULT;
	configuracion->velocidad = (float)DEFAULT;
	strcpy(configuracion->ruta_camino,"-1");
	configuracion->listar = DEFAULT;

	llenar_valores_standard_config(configuracion);	
}

int main(int argc, char *argv[]){
	int viento = VIENTO_BASE;
	int humedad = HUMEDAD_BASE;
	char animo_legolas = ANIMO_LEGOLAS_BASE;
	char animo_gimli= ANIMO_GIMLI_BASE;
	int selector = MENU;
	juego_t defendiendo_torres;
	configuracion_t configuracion;
	comando_t comandos[MAX_COMANDOS];
	size_t cantidad_comandos;
	rutas_t rutas_juego;
	jugador_t jugador;

	srand((unsigned)time(NULL));
	
	if(argc == 1){
		printf("No se ingreso una cantidad de comandos suficiente");
		return 0;
	}

	parse_comando(argc, argv,comandos, &cantidad_comandos);
	inicializar_configuracion_estandar(&configuracion);	
	comandos_defendiendo_torres(&configuracion,comandos,cantidad_comandos,&rutas_juego);

	if(strcmp(argv[1],"jugar") == 0){
		mostrar_carga_presentacion();
		mostrar_ingresar_nombre(jugador.nombre);
		mostrar_caracteristicas_juego(&selector);

		if(selector == EMPEZAR_JUEGO_CON_ANIMOS){
			animos(&viento,&humedad,&animo_legolas,&animo_gimli);
		}

		inicializar_juego(&defendiendo_torres,configuracion,viento,humedad,animo_legolas,animo_gimli);
		jugar(&defendiendo_torres, configuracion,rutas_juego);

		jugador.puntaje = calcular_puntaje(configuracion,orcos_muertos_total(defendiendo_torres,estado_juego(defendiendo_torres)));
		agregar_ranking(rutas_juego.ruta_ranking,jugador);

		mostrar_final_juego(defendiendo_torres);
	}else if(strcmp(argv[1],"poneme_la_repe") == 0){
		if(rutas_juego.hay_grabacion){
			mostrar_video_partida(rutas_juego.ruta_grabacion,configuracion.velocidad);
		}	
	}else if(strcmp(argv[1],"crear_configuracion") == 0){
		comandos_simples(argc, argv,rutas_juego.ruta_config);
		crear_configuracion(rutas_juego.ruta_config);
	}else if(strcmp(argv[1],"crear_camino") == 0){
		comandos_simples(argc, argv,rutas_juego.ruta_caminos);
		crear_caminos_custom(rutas_juego.ruta_caminos);
	}else if(strcmp(argv[1],"ranking") == 0){
		mostrar_ranking(rutas_juego.ruta_config,configuracion.listar);	
	}
	
	return 0;
} 
