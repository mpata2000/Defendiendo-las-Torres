#include "archivos.h"
#include "graficos.h"


#define CAMINO_1 1
#define CAMINO_2 2
#define MAX_LONGITUD_CAMINO 200
#define MAX_COORDENADA_NIVEL_CHICO 14
#define MAX_COORDENADA_NIVEL_GRANDE 20
#define MIN_COORDENADA_NIVEL 0


static const int MAX_ENANOS_NIVEL[MAX_NIVELES] = {5,0,3,4};
static const int MAX_ELFOS_NIVEL[MAX_NIVELES] = {0,5,3,4};

const int MAX_RESISTENCIA_TORRES = 100000;
const int MAX_COSTE_DEFENSOR_TORRES = 100000;
const int MAX_VELOCIDAD = 10;
const int MAX_ANIMOS = 100;
const int MAX_DEFENSORES_NIVEL = 10;
const int MAX_DEFENSORES_EXTRA = 30;
static const int  DEFAULT = -1;
static const int RESISTENCIA_BASE_TORRES = 600;
static const int DEFENSORES_EXTRA_ENANOS = 10;
static const int DEFENSORES_EXTRA_ELFOS = 10;
static const float VELOCIDAD_BASE = (float)1;
const int COSTE_TORRE_BASE = 50;


/*     Parte:PREGUNTAS CONFIGURACION      */

void preguntar_resistencia_torres(int resistencia_torres[MAX_TORRES]){
	for(int i=0; i<MAX_TORRES;i++){
		mostrar_preguntar_resistencia_torres(i, MAX_RESISTENCIA_TORRES);
		
		printf("Resistencia: ");
		scanf("%i",&(resistencia_torres[i]));
		
		while((resistencia_torres[i] >= MAX_RESISTENCIA_TORRES) || ((resistencia_torres[i] <= 0) && (resistencia_torres[i] != DEFAULT))){
			printf("\nPLischu lee devuelta\n");
			printf("Resistencia: ");
			scanf("%i",&(resistencia_torres[i]));
		}
	}
}


void preguntar_defensores_nivel(int defensore_iniciales[MAX_NIVELES], char nombre_defensor[MAX_NOMBRE]){
	for(int i=0; i < MAX_NIVELES; i++){
		mostrar_preguntar_defensores_nivel(i, nombre_defensor,MAX_DEFENSORES_NIVEL);

		printf("»Cantidad de defensores iniciales: ");
		scanf("%i",&(defensore_iniciales[i]));

		while((defensore_iniciales[i] >= MAX_DEFENSORES_NIVEL) || ((defensore_iniciales[i] < 0) && (defensore_iniciales[i] != DEFAULT))){
			printf("\nPLischu lee devuelta\n");
			printf("»Cantidad de defensores iniciales: ");
			scanf("%i",&(defensore_iniciales[i]));
		}
	}
}


void preguntar_coste_defensor_extra(int* coste_defensor, int torre){
	printf("»Coste a Torre %i: ",torre);
	scanf("%i",coste_defensor);
	while (((*coste_defensor) >= MAX_COSTE_DEFENSOR_TORRES) || (((*coste_defensor) < 0) && ((*coste_defensor) != DEFAULT))){
		printf("\nVolve a leer capueira.");
		printf("\n»Coste a Torre %i: ",torre);
		scanf("%i",coste_defensor);
	}
}


void preguntar_defensores_extra(int* defensores_extra, int coste_defensor_extra[MAX_TORRES],char nombre_defensor_extra[MAX_NOMBRE]){
	
	mostrar_preguntar_defensores_extra(nombre_defensor_extra, MAX_COSTE_DEFENSOR_TORRES, MAX_DEFENSORES_EXTRA);

	printf("»Cantidad de %s extra: ",nombre_defensor_extra);
	scanf("%i",defensores_extra);
	while (((*defensores_extra) >= MAX_DEFENSORES_EXTRA) || (((*defensores_extra) < 0) && ((*defensores_extra) != DEFAULT))){
		printf("\nVolve a leer capueira.");
		printf("\n»Cantidad de %s extra: ",nombre_defensor_extra);
		scanf("%i",defensores_extra);
	}
	for (int i=0; i < MAX_TORRES; i++){
		preguntar_coste_defensor_extra(&(coste_defensor_extra[i]),(i+1));
	}	
}


void preguntar_animos_defensor(int* fallo,int* critico,char nombre_defensor_extra[MAX_NOMBRE]){
	mostrar_preguntar_animos_defensor(nombre_defensor_extra, MAX_ANIMOS);

	printf("»El fallo de los %s: ",nombre_defensor_extra);
	scanf("%i",fallo);
	while (((*fallo) > MAX_ANIMOS) || (((*fallo) < 0) && ((*fallo) != DEFAULT))){
		printf("\nLook up.\n");
		printf("»El fallo de los %s: ",nombre_defensor_extra);
		scanf("%i",fallo);
	}
	printf("»El critico de los %s: ",nombre_defensor_extra);
	scanf("%i",critico);
	while (((*critico) > MAX_ANIMOS) || (((*critico) < 0) && ((*critico) != DEFAULT))){
		printf("\nLook up.\n");
		printf("»El critio de los %s: ",nombre_defensor_extra);
		scanf("%i",critico);
	}
}


void preguntar_velocidad(float* velocidad){
	mostrar_preguntar_velocidad(MAX_VELOCIDAD);

	printf("»La velocidad: ");
	scanf("%f",velocidad);
	while (((*velocidad) >= MAX_VELOCIDAD) || (((*velocidad) <= 0) && ((*velocidad) != DEFAULT))){
		printf("\nTry again.\n");
		printf("»La velocidad: ");
		scanf("%f",velocidad);
	}
}

void preguntar_ruta_camino(char ruta_camino[MAX_RUTA_ARCHIVO]){	
	mostrar_preguntar_ruta_camino();

	printf("»Ruta de los caminos custom: ");
	scanf("%s",ruta_camino);

	sacar_extension_archivo(ruta_camino);

}

/* 
* Recibe una configuracion_t por referencia
* Carga la configuracion_t con datos validos ingresados por el usuario
*/
void preguntar_configuracion(configuracion_t* configuracion){
	preguntar_resistencia_torres(configuracion->resistencia_torre);
	preguntar_defensores_nivel(configuracion->enanos_nivel,"Enanos");
	preguntar_defensores_nivel(configuracion->elfos_nivel,"Elfos");
	preguntar_defensores_extra(&(configuracion->enanos_extra),configuracion->coste_torres_enanos,"Enanos");
	preguntar_defensores_extra(&(configuracion->elfos_extra),configuracion->coste_torres_elfos,"Elfos");
	preguntar_animos_defensor(&(configuracion->fallo_enano),&(configuracion->critico_enano),"Enanos");
	preguntar_animos_defensor(&(configuracion->fallo_elfo),&(configuracion->critico_elfo),"Elfos");
	preguntar_velocidad(&(configuracion->velocidad));
	preguntar_ruta_camino(configuracion->ruta_camino);
}



/*     Parte: CONFIGURACION      */

/*
* Recibe: -> La ruta de la configuracion sin extension.
*
* Procedimiento:->Se llena configuracion_t con datos validos ingresados por el usuario.
*
* Post:-> Crea un archivo ordenado con los datos de configuracion_t.
*/
void crear_configuracion(char ruta_configuracion[MAX_RUTA_ARCHIVO]){
	configuracion_t configuracion;
	FILE* archivo_config;
	
	preguntar_configuracion(&configuracion);
	strcat(ruta_configuracion, ".txt");

	archivo_config = fopen(ruta_configuracion, "w");
	if(!archivo_config){
 		printf("\nNo se pudo abrir el archivo para escritura");
		return;
    }

	fprintf(archivo_config,"RESISTENCIA_TORRES=%i,%i\n",configuracion.resistencia_torre[0],configuracion.resistencia_torre[1]);
	fprintf(archivo_config,"ENANOS_INICIO=%i,%i,%i,%i\n",configuracion.enanos_nivel[0],configuracion.enanos_nivel[1],configuracion.enanos_nivel[2],configuracion.enanos_nivel[3]);
	fprintf(archivo_config,"ELFOS_INICIO=%i,%i,%i,%i\n",configuracion.elfos_nivel[0],configuracion.elfos_nivel[1],configuracion.elfos_nivel[2],configuracion.elfos_nivel[3]);
	fprintf(archivo_config,"ENANOS_EXTRA=%i,%i,%i\n",configuracion.enanos_extra,configuracion.coste_torres_enanos[0],configuracion.coste_torres_enanos[1]);
	fprintf(archivo_config,"ELFOS_EXTRA=%i,%i,%i\n",configuracion.elfos_extra,configuracion.coste_torres_elfos[0],configuracion.coste_torres_elfos[1]);
	fprintf(archivo_config,"ENANOS_ANIMO=%i,%i\n",configuracion.fallo_enano,configuracion.critico_enano);
	fprintf(archivo_config,"ELFOS_ANIMO=%i,%i\n",configuracion.fallo_elfo,configuracion.critico_elfo);
	fprintf(archivo_config,"VELOCIDAD=%f\n",configuracion.velocidad);
	fprintf(archivo_config,"CAMINOS=%s\n",configuracion.ruta_camino);
	
	fclose(archivo_config);
}


//Pre: Recive una configuracion_t valida y inicializada
//Post: Carga los valores correspondientes a cada parte de configuracion_t.
void llenar_valores_standard_config(configuracion_t *configuracion){
	for(int i=0; i<MAX_TORRES;i++){
		if(configuracion->resistencia_torre[i] == DEFAULT){
			configuracion->resistencia_torre[i]=RESISTENCIA_BASE_TORRES;

		}	
	}
	for(int i=0; i<MAX_NIVELES;i++){
		if(configuracion->enanos_nivel[i] == DEFAULT){
			configuracion->enanos_nivel[i]= MAX_ENANOS_NIVEL[i];

		}
		if(configuracion->elfos_nivel[i] == DEFAULT){
			configuracion->elfos_nivel[i]= MAX_ELFOS_NIVEL[i];
		}	
	}

	if(configuracion->enanos_extra == DEFAULT){
		configuracion->enanos_extra = DEFENSORES_EXTRA_ENANOS;
	}
	if(configuracion->coste_torres_enanos[0] == DEFAULT){
		configuracion->coste_torres_enanos[0] = COSTE_TORRE_BASE;
	}
	if(configuracion->coste_torres_enanos[1] == DEFAULT){
		configuracion->coste_torres_enanos[1] = 0;
	}

	if(configuracion->elfos_extra == DEFAULT){
		configuracion->elfos_extra = DEFENSORES_EXTRA_ELFOS;
	}
	if(configuracion->coste_torres_elfos[0] == DEFAULT){
		configuracion->coste_torres_elfos[0] = 0;
	}
	if(configuracion->coste_torres_elfos[1] == DEFAULT){
		configuracion->coste_torres_elfos[1] = COSTE_TORRE_BASE;
	}

	if(configuracion->velocidad == (float)DEFAULT){
		configuracion->velocidad = VELOCIDAD_BASE;
	}
}

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
int leer_configuracion(configuracion_t* configuracion,char ruta_configuracion[MAX_RUTA_ARCHIVO]){
	char dato_config[MAX_NOMBRE];
	FILE* archivo_config;

	strcat(ruta_configuracion, ".txt");

	archivo_config = fopen(ruta_configuracion, "r");
	if(!archivo_config){
		return NO_EXISTE_ARCHIVO;
    }

	int leidos= fscanf(archivo_config,"%[^=]",dato_config);

	while(leidos == 1){
		if(strcmp(dato_config,"RESISTENCIA_TORRES") == 0){
			fscanf(archivo_config,"=%i,%i\n",&(configuracion->resistencia_torre[0]),&(configuracion->resistencia_torre[1]));
		}else if(strcmp(dato_config,"ENANOS_INICIO") == 0){
			fscanf(archivo_config,"=%i,%i,%i,%i\n",&(configuracion->enanos_nivel[0]),&(configuracion->enanos_nivel[1]),&(configuracion->enanos_nivel[2]),&(configuracion->enanos_nivel[3]));
		}else if(strcmp(dato_config,"ELFOS_INICIO") == 0){
			fscanf(archivo_config,"=%i,%i,%i,%i\n",&(configuracion->elfos_nivel[0]),&(configuracion->elfos_nivel[1]),&(configuracion->elfos_nivel[2]),&(configuracion->elfos_nivel[3]));
		}else if(strcmp(dato_config,"ENANOS_EXTRA") == 0){
			fscanf(archivo_config,"=%i,%i,%i\n",&(configuracion->enanos_extra),&(configuracion->coste_torres_enanos[0]),&(configuracion->coste_torres_enanos[1]));
		}else if(strcmp(dato_config,"ELFOS_EXTRA") == 0){
			fscanf(archivo_config,"=%i,%i,%i\n",&(configuracion->elfos_extra),&(configuracion->coste_torres_elfos[0]),&(configuracion->coste_torres_elfos[1]));
		}else if(strcmp(dato_config,"ENANOS_ANIMO") == 0){
			fscanf(archivo_config,"=%i,%i\n",&(configuracion->fallo_enano),&(configuracion->critico_enano));
		}else if(strcmp(dato_config,"ELFOS_ANIMO") == 0){
			fscanf(archivo_config,"=%i,%i\n",&(configuracion->fallo_elfo),&(configuracion->critico_elfo));
		}else if(strcmp(dato_config,"VELOCIDAD") == 0){
			fscanf(archivo_config,"=%f\n",&(configuracion->velocidad));
		}else if(strcmp(dato_config,"CAMINOS") == 0){
			fscanf(archivo_config,"=%s\n",configuracion->ruta_camino);
		}
		
		leidos= fscanf(archivo_config,"%[^=]",dato_config);
	}
	llenar_valores_standard_config(configuracion);

	fclose(archivo_config);

	return EXISTE_ARCHIVO;
}

/*     Parte: CAMINOS CUSTOM      */

//Pre: Que el nivel actual se un nivel chico(Nivel 1 y 2).
//Post: Devuelve true si esa coordenada esta adentro de ese nivel.
bool coordenada_en_nivel_chico(int coordenada){
	return((coordenada >= MIN_COORDENADA_NIVEL)&&(coordenada <= MAX_COORDENADA_NIVEL_CHICO));
}

//Pre: Que el nivel actual se un nivel grande(Nivel 3 y 4).
//Post: Devuelve true si esa coordenada esta adentro de ese nivel.
bool coordenada_en_nivel_grande(int coordenada){
	return((coordenada >= MIN_COORDENADA_NIVEL)&&(coordenada <= MAX_COORDENADA_NIVEL_GRANDE));
}

//Pre:Recive una coordenada y el nivel actual.
//Post devuelve true si esa coordenada esta adentro del nivel.
bool en_mapa(int nivel, coordenada_t coordenada){
	if((nivel == NIVEL_1)||(nivel == NIVEL_2)){
	    return(coordenada_en_nivel_chico(coordenada.fil) && coordenada_en_nivel_chico(coordenada.col));   
	}else{
	    return(coordenada_en_nivel_grande(coordenada.fil) && coordenada_en_nivel_grande(coordenada.col));
	}
}

//Pre: Recive un camino valido con su tope y una nueva coordena.
//Post: Devuelve true si la coordenada esta sobre el camino.
bool coordenada_sobre_camino(coordenada_t camino[MAX_LONGITUD_CAMINO], coordenada_t posicion,int tope){
	int i = 0;
	int fil;
	int col;
	bool en_camino = false;

	while((i < tope) && (!en_camino)){
		fil = camino[i].fil;
		col = camino[i].col;

		if((fil == posicion.fil)&&(col == posicion.col)){
			en_camino = true;
		}
		i++;
    }
    return en_camino;	
}

//Pre: Recive una coordenada_t por referencia y el nivel actual
//Post: Carga una coordenada valida para ese nivel
void pedir_coordenada(coordenada_t* coordenada, int nivel){
	printf("\nFila: ");
	scanf(" %i", &(coordenada->fil));
	printf("Columna: ");
	scanf(" %i", &(coordenada->col));
	while (!en_mapa(nivel,*coordenada)){
	    printf("La coordenada esta afura del mapa");
		printf("\nFila: ");
		scanf(" %i", &(coordenada->fil));
		printf("Columna: ");
		scanf(" %i", &(coordenada->col));
	} 
}

/* 
* Pre: Recive un camino valido y su tope por referencia y el nivel actual en el que se esta cargando el camino
* Procedimiento: -> Se le pide al usuario un "movimiento" del camino y se verifica que sea valido
*				 -> Si se mueve, se verifica que la nueva coordenada es valida
* Post: Agrega una nueva coordenada al camino si es valida
 */
void mover_camino(coordenada_t camino[MAX_LONGITUD_CAMINO],int* tope_camino, int nivel){
	coordenada_t nueva_cordenada_camino;
	char movimiento;

	nueva_cordenada_camino.fil = camino[*tope_camino-1].fil;
	nueva_cordenada_camino.col = camino[*tope_camino-1].col;

	printf("Presione: W(Arriba) A(Izquierda) S(Abajo) D(Derecha) ");
	scanf(" %c", &movimiento);

	switch (movimiento){
		case 'W':case 'w':
			nueva_cordenada_camino.fil --;
			break;
		case 'A':case 'a':
			nueva_cordenada_camino.col --;
			break;
		case 'S':case 's':
			nueva_cordenada_camino.fil ++;
			break;
		case 'D':case 'd':
			nueva_cordenada_camino.col ++;
			break;
	}
	coordenada_sobre_camino(camino,nueva_cordenada_camino,(*tope_camino));

	if(en_mapa(nivel,nueva_cordenada_camino)&&!coordenada_sobre_camino(camino,nueva_cordenada_camino,(*tope_camino))){
		camino[*tope_camino].fil = nueva_cordenada_camino.fil;
		camino[*tope_camino].col = nueva_cordenada_camino.col;
		(*tope_camino)++;	
	}	
		
}

//Pre: Recive la ultima coordenada valida del camino y la coordenda de la torre.
//Post: Devuelve true si la coordenada esta sobre la torre
bool llego_final_camino(coordenada_t ultima_coor_camino, coordenada_t torre){
	return ((ultima_coor_camino.fil==torre.fil)&&(ultima_coor_camino.col==torre.col));
}


/* 
* Pre: Recive caminos_nivel_t
*
* Post: Crea un archivo con los caminos custom
*/
void crear_camino_por_nivel(camino_nivel_t caminos_nivel[MAX_NIVELES]){
    for(int nivel=0; nivel < MAX_NIVELES ; nivel++){
        bool hay_camino_1 = false;
        bool hay_camino_2 = false;

		caminos_nivel[nivel].tope_camino_1 = 0;
		caminos_nivel[nivel].tope_camino_2 = 0;

        if(nivel != NIVEL_2){
			system("clear");
			mostrar_crear_camino(caminos_nivel[nivel],nivel);
			printf("Por favor Ingrese las coordenadas de la Entrada 1:");
			pedir_coordenada(&(caminos_nivel[nivel].camino_1[0]),nivel);
			caminos_nivel[nivel].tope_camino_1 ++;

			printf("Por favor Ingrese las coordenadas de la Torre 1:");
			pedir_coordenada( &(caminos_nivel[nivel].torre_1), nivel);
            hay_camino_1 = true;
        }
        if(nivel != NIVEL_1){
			system("clear");
			mostrar_crear_camino(caminos_nivel[nivel],nivel);
			printf("Por favor Ingrese las coordenadas de la Entrada 2:");
			pedir_coordenada(&(caminos_nivel[nivel].camino_2[0]),nivel);
			caminos_nivel[nivel].tope_camino_2 ++;

			printf("Por favor Ingrese las coordenadas de la Torre 2:");
			pedir_coordenada( &(caminos_nivel[nivel].torre_2) , nivel);
			hay_camino_2 = true;
		}

		if(hay_camino_1){
			while(!llego_final_camino(caminos_nivel[nivel].camino_1[caminos_nivel[nivel].tope_camino_1-1],caminos_nivel[nivel].torre_1)){
				system("clear");
				mostrar_crear_camino(caminos_nivel[nivel],nivel);
				printf("Se esta moviendo el Camino 1:\n");
				mover_camino(caminos_nivel[nivel].camino_1,&(caminos_nivel[nivel].tope_camino_1),nivel);
			}
		}

		if(hay_camino_2){
			while(!llego_final_camino(caminos_nivel[nivel].camino_2[caminos_nivel[nivel].tope_camino_2-1],caminos_nivel[nivel].torre_2)){
				system("clear");
				mostrar_crear_camino(caminos_nivel[nivel],nivel);
				printf("Se esta moviendo el Camino 2:\n");
				mover_camino(caminos_nivel[nivel].camino_2,&(caminos_nivel[nivel].tope_camino_2),nivel);
			}
		}
	}
}

/* 
* Pre: Que el jugador haya ingresado los comandos correctos
*      ->Recive: Un nombre para los caminos custom sin extension
*
* Post: Crea un archivo con los caminos custom
*/
void crear_caminos_custom(char ruta_camino[MAX_RUTA_ARCHIVO]){
	FILE* archivo_caminos; 
	camino_nivel_t caminos_nivel[MAX_NIVELES];
	
	crear_camino_por_nivel(caminos_nivel);
	strcat(ruta_camino, ".txt");

	archivo_caminos = fopen(ruta_camino, "w");
	if(!archivo_caminos){
 		printf("No se pudo abrir el archivo para escritura");
		return;
    }

	for(int nivel=0; nivel < MAX_NIVELES; nivel++){
		fprintf(archivo_caminos,"NIVEL=%i\n",(nivel+1));
		if(caminos_nivel[nivel].tope_camino_1 > 0){
			fprintf(archivo_caminos,"CAMINO=1\n");
			for(int i=0; i < caminos_nivel[nivel].tope_camino_1; i++){
				fprintf(archivo_caminos,"%i;%i\n", caminos_nivel[nivel].camino_1[i].fil, caminos_nivel[nivel].camino_1[i].col);
			}
		}
		if(caminos_nivel[nivel].tope_camino_2 > 0){
			fprintf(archivo_caminos,"CAMINO=2\n");
			for(int i=0; i < caminos_nivel[nivel].tope_camino_2; i++){
				fprintf(archivo_caminos,"%i;%i\n", (caminos_nivel[nivel].camino_2[i].fil), (caminos_nivel[nivel].camino_2[i].col));
			}
		}      
    }

    fclose(archivo_caminos);
}

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
int leer_caminos(char ruta_camino[MAX_RUTA_ARCHIVO],camino_nivel_t caminos_nivel[MAX_NIVELES]){
	FILE* archivo_camino;
	int valor;
	int tope;
	int nivel;
	char aux[40];
	int leidos;
	
	strcat(ruta_camino, ".txt");
	archivo_camino = fopen(ruta_camino, "r");
	if(!archivo_camino){
		return NO_EXISTE_ARCHIVO;
	}

	leidos = fscanf(archivo_camino,"%[^=]=%i\n",aux,&valor);

	while(leidos == 2){
		if(strcmp(aux,"NIVEL")==0){
			nivel = valor-1;	
			caminos_nivel[nivel].tope_camino_1 = 0;
			caminos_nivel[nivel].tope_camino_2 = 0;
		}else if(strcmp(aux,"CAMINO")==0){
			switch (valor){
				case CAMINO_1:
					tope=0;

					do{
						leidos=fscanf(archivo_camino,"%i;%i\n",&(caminos_nivel[nivel].camino_1[tope].fil),&(caminos_nivel[nivel].camino_1[tope].col));
						tope++;
					}while(leidos == 2);
					caminos_nivel[nivel].tope_camino_1 =(tope-1);
					break;
				case CAMINO_2:
					tope=0;

					do{
						leidos=fscanf(archivo_camino,"%i;%i\n",&(caminos_nivel[nivel].camino_2[tope].fil),&(caminos_nivel[nivel].camino_2[tope].col));
						tope++;
					}while(leidos == 2);
					caminos_nivel[nivel].tope_camino_2=(tope-1);
					break;
			}
		}
		leidos = fscanf(archivo_camino,"%[^=]=%i\n",aux,&valor);
	}
		
	fclose(archivo_camino);
	return EXISTE_ARCHIVO;
}


/*     Parte: GRABACION      */


/* Pre: Recibe una ruta de la partida grabada con extension y a la velocidad que se quiere mostrar la repe
*
*  Procedimiento: -> Se verifica si el archivo existe
*                 -> Si existe se lee el archivo, carga en juego_t y se lo muestra hata que termine el archivo
*/
void mostrar_video_partida(char ruta_grabacion[MAX_RUTA_ARCHIVO],float velocidad){
	juego_t juego;

	FILE* archivo_partida = fopen(ruta_grabacion, "rb");
	if(!archivo_partida){
		printf("Che no exist el archivo");
		return;
	}

	fread(&juego,sizeof(juego_t),1,archivo_partida);

	while (!feof(archivo_partida)){
		system("clear");
		mostrar_juego(juego);
		detener_el_tiempo(velocidad);

		fread(&juego,sizeof(juego_t),1,archivo_partida);
	}
	system("clear");
	fclose(archivo_partida);	
}


/*     Parte: RANKING      */

/*
* Pre: Que no exista el ranking
* Recibe: -> La ruta del ranking con extension.
*         -> Una estructura juegador_t valida
*
* Post:-> SCrea un nuevo ranking con los datos de jugador_t.
*/
void crear_ranking(char ruta_config[MAX_RUTA_ARCHIVO],jugador_t jugador){
	FILE* archivo_ranking = fopen(ruta_config, "w");
	if(!archivo_ranking){
		return;
	}

	fprintf(archivo_ranking,"%s;%i\n",jugador.nombre,jugador.puntaje);

	fclose(archivo_ranking);
}

/*
* Pre: Que haya terminado el juego
* Recibe: -> La ruta del ranking sin extension(El mismo nombre de la configuracion).
*         -> Una estructura juegador_t valida
*
* Post:-> Si el ranking existe se lo agregara al ranking de forma ordenada
*	   -> Si no existe el ranking se crea un nuevo ranking que contiene el nuevo jugador
*/
void agregar_ranking(char ruta_ranking[MAX_RUTA_ARCHIVO],jugador_t jugador){
	FILE* ranking_viejo;
	FILE* ranking_nuevo;
	int leidos;
	char nombre_jugador[MAX_NOMBRE];
	int puntos_jugador;
	bool ordenado = false;

	strcat(ruta_ranking,".csv");

	ranking_viejo = fopen(ruta_ranking, "r");
	if(!ranking_viejo){
		crear_ranking(ruta_ranking,jugador);
		return;
	}

	ranking_nuevo = fopen("ranking_nuevo","w");
	if(!ranking_nuevo){
		fclose(ranking_viejo);
		return;
	}

	leidos = fscanf(ranking_viejo,"%[^;];%i\n",nombre_jugador,&puntos_jugador);

	while((leidos == 2)&&(!ordenado)){
		if(puntos_jugador > jugador.puntaje){
			fprintf(ranking_nuevo,"%s;%i\n",nombre_jugador,puntos_jugador);
		}else if(puntos_jugador < jugador.puntaje){
			fprintf(ranking_nuevo,"%s;%i\n",jugador.nombre,jugador.puntaje);
			fprintf(ranking_nuevo,"%s;%i\n",nombre_jugador,puntos_jugador);
			ordenado = true;
		}else{
			if(strcmp(jugador.nombre,nombre_jugador) >= 0){
				fprintf(ranking_nuevo,"%s;%i\n",nombre_jugador,puntos_jugador);
				fprintf(ranking_nuevo,"%s;%i\n",jugador.nombre,jugador.puntaje);
			}else{
				fprintf(ranking_nuevo,"%s;%i\n",nombre_jugador,puntos_jugador);
				fprintf(ranking_nuevo,"%s;%i\n",jugador.nombre,jugador.puntaje);
			}
			ordenado = true;
		}
		leidos = fscanf(ranking_viejo,"%[^;];%i\n",nombre_jugador,&puntos_jugador);
	}
	while(leidos == 2){
		fprintf(ranking_nuevo,"%s;%i\n",nombre_jugador,puntos_jugador);
		leidos = fscanf(ranking_viejo,"%[^;];%i\n",nombre_jugador,&puntos_jugador);
	}
	if(!ordenado){
		fprintf(ranking_nuevo,"%s;%i\n",jugador.nombre,jugador.puntaje);
	}

	fclose(ranking_viejo);
	fclose(ranking_nuevo);
	rename("ranking_nuevo",ruta_ranking);
}

/* 
* Recibe: -> La ruta del ranking sin extension(El nombre de la configuracion)
*         -> La cantidad de jugadores del ranking a listar(si recibe el default(-1) se listan todos)
*
* Post: Imprime los jugadores del ranking solicitado si el archivo existe
 */
void mostrar_ranking(char ruta_ranking[MAX_RUTA_ARCHIVO],int listar){
	int leidos;
	int i=0;
	char nombre_jugador[MAX_NOMBRE];
	int puntos_jugador;
	
	strcat(ruta_ranking,".csv");
	FILE* archivo_ranking = fopen(ruta_ranking, "r");
	if(!archivo_ranking){
		printf("No existe ese ranking mi rey");
		return;
	}

	if(listar == DEFAULT){
		leidos = fscanf(archivo_ranking,"%[^;];%i\n",nombre_jugador,&puntos_jugador);
		while(leidos == 2){
			printf("Nombre:%s               Puntaje: %i\n",nombre_jugador,puntos_jugador);
			leidos = fscanf(archivo_ranking,"%[^;];%i\n",nombre_jugador,&puntos_jugador);
		}
	}else{
		leidos = fscanf(archivo_ranking,"%[^;];%i\n",nombre_jugador,&puntos_jugador);
		while((leidos == 2)&&(i < listar)){
			printf("Nombre:%s               Puntaje: %i\n",nombre_jugador,puntos_jugador);
			leidos = fscanf(archivo_ranking,"%[^;];%i\n",nombre_jugador,&puntos_jugador);
			i++;
		}
	}

	fclose(archivo_ranking);
}