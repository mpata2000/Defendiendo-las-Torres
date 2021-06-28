#include "defendiendo_torres.h"


#define TOPE_NIVEL_CHICO 15
#define TOPE_NIVEL_GRANDE 20

static const char ANIMO_REGULAR = 'R';
static const char ANIMO_BUENO = 'B';
const int ATAQUE_CRITICO_BAJO = 0;
const int ATAQUE_CRITICO_MEDIO = 10;
const int ATAQUE_CRITICO_ALTO = 25;
static const char ELFO  = 'L';
static const char ENANO = 'G';
static const char ORCOS = 'O';
static const int VIDA_BASE_ORCO = 200;
static const int VIDA_EXTRA_ORCO = 101;
static const int ATAQUE_BASE_ENANO = 60;
static const int ATAQUE_CRITICO_ENANO = 100;
static const int ATAQUE_BASE_ELFO = 30;
static const int ATAQUE_CRITICO_ELFO = 70;
const int ULTIMO_NIVEL = 3;
const char CAMINO_UNO = '#';
const char CAMINO_DOS = '&';
const char DOS_CAMINOS = 'C';
const char ENTRADA_1 = 'P';
const char ENTRADA_2 = 'E';
const char TORRE_1 = 'Y';
const char TORRE_2 = 'T';
const char VACIO = '-';
const char ORCOS_CHICA_VIDA = 'M';
const char ORCOS_VIDA_MEDIA = 'o';
const int CAMINO_1 = 1;
const int CAMINO_2 = 2;
static const int JUGANDO = 0;
static const int PERDIO = -1;
static const int GANO =  1 ;
const int SE_PUDO_AGREGAR = 0;
static const int NO_SE_PUDO_AGREGAR = -1;
const int DISTANCIA_MAX_ENANO = 1;
const int DISTANCIA_MAX_AL_CAMINO = 1;
const int DISTANCIA_MAX_ELFO = 3;
static const int DEFAULT = -1;


/* Iniciliza la resistencia de las torres y le agrega sus defensores extra */
void incializar_torres(torres_t* torres, configuracion_t configuracion){
	(*torres).resistencia_torre_1 = configuracion.resistencia_torre[0];
	(*torres).resistencia_torre_2 = configuracion.resistencia_torre[1];
	(*torres).enanos_extra = configuracion.enanos_extra;
	(*torres).elfos_extra = configuracion.elfos_extra;
}
//Pre: Recibe un viento valido
//Post devuelve la mitad del viento
int calculo_fallo_legolas(int viento){
	return (viento/2);	
}
//Pre: Recibe una humedad valido
//Post devuelve la mitad de la humedad
int calculo_fallo_gimli(int humedad){
	return (humedad/2);	
}
//Pre Recibe un animo valido
//Post: Devuelve un la chances de ataque critico correspondiente al animo
int calculo_ataque_critico_animo(char animo_personaje){
	if(animo_personaje == ANIMO_BUENO){
		return ATAQUE_CRITICO_ALTO;
	}else if(animo_personaje == ANIMO_REGULAR){
		return ATAQUE_CRITICO_MEDIO;
	}else{
		return ATAQUE_CRITICO_BAJO;
	}
}

/*
 * Inicializará el juego, cargando la informacion de las torres y
 * los ataques críticos y fallo de Legolas y Gimli.
 * NO inicializará el primer nivel.
 */
void inicializar_juego(juego_t* juego,configuracion_t configuracion, int viento, int humedad, char animo_legolas, char animo_gimli){
	incializar_torres(&(*juego).torres,configuracion);
	
	if(configuracion.critico_elfo == DEFAULT){
		juego->critico_legolas = calculo_ataque_critico_animo(animo_legolas);
	}else{
		juego->critico_legolas = configuracion.critico_elfo;
	}
	if(configuracion.critico_enano == DEFAULT){
		juego->critico_gimli = calculo_ataque_critico_animo(animo_gimli);
	}else{
		juego->critico_gimli = configuracion.critico_enano;
	}
	if(configuracion.fallo_elfo == DEFAULT){
		juego->fallo_legolas = calculo_fallo_legolas(viento);
	}else{
		juego->fallo_legolas = configuracion.fallo_elfo;
	}
	if(configuracion.fallo_enano == DEFAULT){
		juego->fallo_gimli = calculo_fallo_gimli(humedad);
	}else{
		juego->fallo_gimli = configuracion.fallo_enano;
	}
	

	juego->nivel_actual = -1;	
}

/*
 * Recibe un juego con todas sus estructuras válidas. 
 * El juego se dará por ganado si el juego está en el ultimo nivel y éste ha sido terminado.
 * El juego se dará por perdido, si alguna de las torres llega a 0 en su resistencia.
 * Devolverá:
 * >  0 si el estado es jugando.
 * > -1 si el estado es perdido.
 * >  1 si el estado es ganado.
 */
int estado_juego(juego_t juego){

	if((juego.torres.resistencia_torre_1 <= 0)||(juego.torres.resistencia_torre_2 <= 0)){
		return PERDIO;
	}
	if(juego.nivel_actual == ULTIMO_NIVEL){
		return estado_nivel(juego.nivel);
	}

	return JUGANDO;
}

/*
 * Recibe un nivel con todas sus estructuras válidas. 
 * El nivel se dará por ganado cuando estén TODOS los orcos de ese 
 * nivel muertos (esto es, con vida menor o igual a 0).
 * Devolverá:
 * >  0 si el estado es jugando.
 * >  1 si el estado es ganado.
 */
int estado_nivel(nivel_t nivel){
	int i=0;
	
	if(nivel.tope_enemigos < nivel.max_enemigos_nivel){
		return JUGANDO;
	}

	if(nivel.tope_enemigos >= nivel.max_enemigos_nivel){
		while(i < nivel.tope_enemigos){
			if(nivel.enemigos[i].vida > 0){
				return JUGANDO;
			}
			i++;
		}
	}

	return GANO;
}

//Pre: Recibe una posicion y la estructura nivel
//Post: Devuelve true si la posicion es la misma que alguna posicion del camino 2
bool esta_en_camino(coordenada_t camino[MAX_LONGITUD_CAMINO], coordenada_t posicion,int tope){
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

//Pre: Recibe un nivel calido y una coordenada
//Post: Devuelve true si la coordenada es igual a algun otra que
bool esta_en_defensor(nivel_t nivel, coordenada_t posicion){
	int i = 0;
	bool en_defensor = false;

	while((i < nivel.tope_defensores) && (!en_defensor)){
		if((posicion.fil == nivel.defensores[i].posicion.fil) && (posicion.col == nivel.defensores[i].posicion.col)){
			en_defensor = true;
		}
		i++;
	}
	return en_defensor;
}

//Pre: Recibe un nivel valido y una funcion
//Post: Devuelve true si se puede colocar el nuevo defensor
bool posicion_defensor_valida(nivel_t nivel, coordenada_t posicion){
	return ((!esta_en_camino(nivel.camino_1, posicion, nivel.tope_camino_1) && !esta_en_camino(nivel.camino_2, posicion, nivel.tope_camino_2)) && (!esta_en_defensor(nivel , posicion)));
}
/* 
 * Agregará un defensor en el nivel recibido como parametro.
 * Devolverá:
 * >  0 si pudo agregar el defensor correctamente.
 * > -1 si no pudo (la coordenada es parte del camino de ese nivel, 
 * existe otro defensor, etc.)
 */
int agregar_defensor(nivel_t* nivel, coordenada_t posicion, char tipo){

	if(posicion_defensor_valida(*nivel, posicion)){
		(*nivel).defensores[(*nivel).tope_defensores].tipo = tipo;

		if((*nivel).defensores[(*nivel).tope_defensores].tipo == ELFO){
			(*nivel).defensores[(*nivel).tope_defensores].fuerza_ataque = ATAQUE_BASE_ELFO;
		}else{
			(*nivel).defensores[(*nivel).tope_defensores].fuerza_ataque = ATAQUE_BASE_ENANO;
		}

		(*nivel).defensores[(*nivel).tope_defensores].posicion.fil = posicion.fil;
		(*nivel).defensores[(*nivel).tope_defensores].posicion.col = posicion.col;

		(*nivel).tope_defensores++;

		return SE_PUDO_AGREGAR;
	}else{
		return NO_SE_PUDO_AGREGAR;
	}
}



//Pre: Recibe un "porcentaje" de fallo y de ataque critico de los enanos
//Post: Devuelve la fuerza correspondiente segun la chance generada
int fuerza_ataque_defensor(int fallo, int critico,char tipo){
	int chance = rand() % 100;
	int fuerza;

	if (chance < critico){
		if(tipo == ENANO){
			fuerza = ATAQUE_CRITICO_ENANO;
		}else if(tipo == ELFO){
			fuerza = ATAQUE_CRITICO_ELFO;
		}
	}else{
		if(tipo == ENANO){
			fuerza = ATAQUE_BASE_ENANO;
		}else if(tipo == ELFO){
			fuerza = ATAQUE_BASE_ELFO;
		}
	}

	chance = rand() % 100;

	if(chance < fallo){
		fuerza = 0;
	}

	return fuerza;
}

//Pre: Recibe una coordenada del enano que esta atacando y del enemigo que esta siendo atacado
//Post: Devuelve true si el enemigo esta en una coordenada alrededor del enano
bool esta_en_rago_enano(coordenada_t posicion_enano, coordenada_t posicion_enemigo){
	return ((abs(posicion_enano.fil - posicion_enemigo.fil) <= DISTANCIA_MAX_ENANO) && (abs(posicion_enano.col - posicion_enemigo.col) <= DISTANCIA_MAX_ENANO));
}

/*
* Recibe un enano y un nivel valido
* Hace que el enano le pegue a un solo enemigo en un rango valido
*/
void turno_enano(defensor_t enano, nivel_t* nivel){
	int num_orco = 0;
	bool enano_golpeo = false;

	while((num_orco < (*nivel).tope_enemigos) && (!enano_golpeo)){
		if((*nivel).enemigos[num_orco].camino == CAMINO_1){
			if(esta_en_rago_enano(enano.posicion, (*nivel).camino_1[(*nivel).enemigos[num_orco].pos_en_camino]) && ((*nivel).enemigos[num_orco].vida > 0)){
				enano_golpeo=true;

				(*nivel).enemigos[num_orco].vida -= enano.fuerza_ataque;
				
				if((*nivel).enemigos[num_orco].vida < 0){
					(*nivel).enemigos[num_orco].vida = 0;
				}
			}
		}else{
			if(esta_en_rago_enano(enano.posicion, (*nivel).camino_2[(*nivel).enemigos[num_orco].pos_en_camino]) && ((*nivel).enemigos[num_orco].vida > 0)){
				enano_golpeo=true;
				(*nivel).enemigos[num_orco].vida -= enano.fuerza_ataque;

				if((*nivel).enemigos[num_orco].vida < 0){
					(*nivel).enemigos[num_orco].vida = 0;
				}
			}
		}	
		num_orco++;
	}
}


//Pre: Recibe una coordenada del elfo que esta atacando y del enemigo que esta siendo atacado
//Post: Devuelve true si el enemigo esta en distancia Manhattan de 3
bool esta_en_rango_elfo(coordenada_t pos_elfo, coordenada_t pos_enemigo){
	int diferencia_fila;
	int diferencia_columna;

	diferencia_fila = abs(pos_enemigo.fil - pos_elfo.fil);
	diferencia_columna = abs(pos_enemigo.col - pos_elfo.col);


	return ((diferencia_fila + diferencia_columna) <= DISTANCIA_MAX_ELFO);
	
}

/*
* Recibe un elfo y un nivel valido
* Hace que el elfo le pegue a todos enemigos en un rango valido
*/
void turno_elfo(defensor_t elfo, nivel_t* nivel){
	int num_orco;

	for(num_orco=0; num_orco<(nivel->tope_enemigos) ;num_orco++){
		if(nivel->enemigos[num_orco].camino == CAMINO_1){
			if(esta_en_rango_elfo(elfo.posicion, nivel->camino_1[nivel->enemigos[num_orco].pos_en_camino])&&(nivel->enemigos[num_orco].vida > 0)){
				(*nivel).enemigos[num_orco].vida -= elfo.fuerza_ataque;
				
				if((*nivel).enemigos[num_orco].vida < 0){
					(*nivel).enemigos[num_orco].vida = 0;
				}
			}
		}else{
			if(esta_en_rango_elfo(elfo.posicion, nivel->camino_2[nivel->enemigos[num_orco].pos_en_camino])&&(nivel->enemigos[num_orco].vida > 0)){
				(*nivel).enemigos[num_orco].vida -= elfo.fuerza_ataque;

				if((*nivel).enemigos[num_orco].vida < 0){
					(*nivel).enemigos[num_orco].vida = 0;
				}
			}
		}
	}

}

/*
* Recibe un juego valido
* -> Hace todos los movimientos de los defensores
*/
void turno_defensores(juego_t* juego){
	for(int i=0; i < juego->nivel.tope_defensores ; i++){
		if(juego->nivel.defensores[i].tipo == ENANO){
			juego->nivel.defensores[i].fuerza_ataque = fuerza_ataque_defensor(juego->fallo_gimli, juego->critico_gimli, ENANO);
			turno_enano(juego->nivel.defensores[i], &(juego->nivel));
		}else{
			juego->nivel.defensores[i].fuerza_ataque = fuerza_ataque_defensor(juego->fallo_legolas, juego->critico_legolas, ELFO);
			turno_elfo(juego->nivel.defensores[i], &(juego->nivel));
		}
	}

}

/*Parte: Turno Orcos*/

//Pre: Recibe el ultimo orco del vector enemigos_t
//Post: Le asigna vida al orco(Como minimo VIDA_BASE_ORCO, como maximo VIDA_BASE_ORCO+VIDA_EXTRA_ORCO-1)
void generar_vida_orco(enemigo_t* enemigos){
	(*enemigos).vida = VIDA_BASE_ORCO + rand() % VIDA_EXTRA_ORCO;
}
//Pre:Recibe el numero de camino y Se pueden agragar mas orcos 
//Post: Agrega un orco al camino
void agregar_orco(nivel_t* nivel,int camino){

	generar_vida_orco(&((*nivel).enemigos[(*nivel).tope_enemigos]));

	(*nivel).enemigos[(*nivel).tope_enemigos].camino = camino;
	(*nivel).enemigos[(*nivel).tope_enemigos].pos_en_camino = 0;
	(*nivel).tope_enemigos++;
}
//Pre: Recibe un orco con vida, el camino que esta y el numero de orco que es
//Post: Devuelve true si el orco llega al final del camino 1
bool orco_llego_torre(nivel_t nivel,int camino,int num_orco){

	if(camino == CAMINO_1){
		return (nivel.enemigos[num_orco].pos_en_camino == (nivel.tope_camino_1 - 1));
	}else if(camino == CAMINO_2){
		return (nivel.enemigos[num_orco].pos_en_camino == (nivel.tope_camino_2 - 1));
	}else{
		return false;
	}
}

/*
* Recibe un nivel con un camino y el numero de ese camino
* ->Mueve los orcos con vida
* ->Si el orco llega a la torre le saca la vida restante del orco
* ->Genera un orco en el camino
*/ 
void turno_orcos_un_camino(juego_t* juego,int camino){
	int i;

	for(i=0; i<(*juego).nivel.tope_enemigos;i++){
		if((*juego).nivel.enemigos[i].vida > 0){
			(*juego).nivel.enemigos[i].pos_en_camino++;
		}
		if(orco_llego_torre(((*juego).nivel),(*juego).nivel.enemigos[i].camino,i)&&((*juego).nivel.enemigos[i].vida > 0)){
			if((*juego).nivel.enemigos[i].camino == CAMINO_1){	
				(*juego).torres.resistencia_torre_1 -= (*juego).nivel.enemigos[i].vida;
				(*juego).nivel.enemigos[i].vida = 0;
				if((*juego).torres.resistencia_torre_1 < 0){
					(*juego).torres.resistencia_torre_1 = 0;
				}
			}else{
				(*juego).torres.resistencia_torre_2 -= (*juego).nivel.enemigos[i].vida;
				(*juego).nivel.enemigos[i].vida = 0;
				if((*juego).torres.resistencia_torre_2 < 0){
					(*juego).torres.resistencia_torre_2 = 0;
				}
			}
		}
	}
	
	if((*juego).nivel.tope_enemigos < (*juego).nivel.max_enemigos_nivel){
		agregar_orco(&((*juego).nivel), camino);
	}
}
/*
* Recibe un nivel con dos caminos
* ->Mueve los orcos con vida
* ->Si el orco llega a la torre le saca la vida restante del orco
* ->Genera dos orcos cada uno en uno de los caminos
*/ 
void turno_orcos_dos_camino(juego_t* juego){
	int num_orco;
	
	for(num_orco=0; num_orco<(*juego).nivel.tope_enemigos;num_orco++){
		if((*juego).nivel.enemigos[num_orco].vida > 0){
			(*juego).nivel.enemigos[num_orco].pos_en_camino++;
		}
		if(orco_llego_torre(((*juego).nivel),(*juego).nivel.enemigos[num_orco].camino,num_orco)&&((*juego).nivel.enemigos[num_orco].vida > 0)){
			if((*juego).nivel.enemigos[num_orco].camino == CAMINO_1){	
				(*juego).torres.resistencia_torre_1 -= (*juego).nivel.enemigos[num_orco].vida;
				(*juego).nivel.enemigos[num_orco].vida = 0;
				if((*juego).torres.resistencia_torre_1 < 0){
					(*juego).torres.resistencia_torre_1 = 0;
				}
			}else{
				(*juego).torres.resistencia_torre_2 -= (*juego).nivel.enemigos[num_orco].vida;
				(*juego).nivel.enemigos[num_orco].vida = 0;
				if((*juego).torres.resistencia_torre_2 < 0){
					(*juego).torres.resistencia_torre_2 = 0;
				}
			}
		}
	}
	if((*juego).nivel.tope_enemigos < (*juego).nivel.max_enemigos_nivel){
		agregar_orco(&((*juego).nivel), CAMINO_1);
		agregar_orco(&((*juego).nivel), CAMINO_2);
	}

}

/*
 * Jugará un turno y dejará el juego en el estado correspondiente.
 * Harán su jugada enanos, elfos y orcos en ese orden.
 */
void jugar_turno(juego_t* juego){
	turno_defensores(juego);
	
	if ((*juego).nivel_actual == NIVEL_1){
		turno_orcos_un_camino(juego, CAMINO_1);
	}else if((*juego).nivel_actual == NIVEL_2){
		turno_orcos_un_camino(juego, CAMINO_2);
	}else{
		turno_orcos_dos_camino(juego);
	}
}


/*Parte: Mostrar Juego*/


static void verde(){
	printf("\033[0;32m");
}

static void bold_amarillo(){
	printf("\033[1;33m");
}
static void bold_rojo(){
	printf("\033[1;31m");
}
static void blanco(){
	printf("\033[0m");
}
static void bold_magenta(){
	printf("\033[1;35m");
}

void mostrar_presentacion_nivel_chico(juego_t juego){
	int enemigos_muetos=0;
	for(int i=0;i<juego.nivel.tope_enemigos;i++){
		if(juego.nivel.enemigos[i].vida <= 0){
			enemigos_muetos++;
		}
	}

	printf("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
	printf("║                            Defendiendo las Torres                             ║\n");
	printf("╠═══════════════════════════════════════════════════════════════════════════════╣\n");
	if(enemigos_muetos > 9 && enemigos_muetos <= 99){
		printf("║   Nivel: %i                                     Enemigos Muertos: %i / %i     ║\n",juego.nivel_actual+1, enemigos_muetos,juego.nivel.max_enemigos_nivel);
	}else if(enemigos_muetos > 99){
		printf("║   Nivel: %i                                     Enemigos Muertos: %i / %i    ║\n",juego.nivel_actual+1, enemigos_muetos,juego.nivel.max_enemigos_nivel);
		
	}else{
		printf("║   Nivel: %i                                       Enemigos Muertos: %i / %i    ║\n",juego.nivel_actual+1, enemigos_muetos,juego.nivel.max_enemigos_nivel);
	}
	printf("║                                                                               ║\n");
	if(juego.nivel_actual == NIVEL_1){
		if(juego.torres.enanos_extra <10){
			if(juego.torres.resistencia_torre_1 > 99){
				printf("║   Resistencia Torre 1: %i                       Enanos extra Restantes: %i    ║\n",juego.torres.resistencia_torre_1,juego.torres.enanos_extra);
			}else if(juego.torres.resistencia_torre_1 > 9){
				printf("║   Resistencia Torre 1: %i                       Enanos extra Restantes: %i     ║\n",juego.torres.resistencia_torre_1,juego.torres.enanos_extra);
			}else{
				printf("║   Resistencia Torre 1: %i                       Enanos extra Restantes: %i      ║\n",juego.torres.resistencia_torre_1,juego.torres.enanos_extra);
			}
		}else{
			if(juego.torres.resistencia_torre_1 > 99){
				printf("║   Resistencia Torre 1: %i                       Enanos extra Restantes: %i   ║\n",juego.torres.resistencia_torre_1,juego.torres.enanos_extra);
			}else if(juego.torres.resistencia_torre_1 > 9){
				printf("║   Resistencia Torre 1: %i                       Enanos extra Restantes: %i    ║\n",juego.torres.resistencia_torre_1,juego.torres.enanos_extra);
			}else{
				printf("║   Resistencia Torre 1: %i                       Enanos extra Restantes: %i     ║\n",juego.torres.resistencia_torre_1,juego.torres.enanos_extra);
			}
		}
	}else{
		if(juego.torres.elfos_extra <10){
			if(juego.torres.resistencia_torre_2 > 99){
				printf("║   Resistencia Torre 2: %i                       Elfos extra Restantes: %i     ║\n",juego.torres.resistencia_torre_2,juego.torres.elfos_extra);
			}else if(juego.torres.resistencia_torre_2 > 9){
				printf("║   Resistencia Torre 2: %i                       Elfos extra Restantes: %i      ║\n",juego.torres.resistencia_torre_2,juego.torres.elfos_extra);
			}else{
				printf("║   Resistencia Torre 2: %i                       Elfos extra Restantes: %i       ║\n",juego.torres.resistencia_torre_2,juego.torres.elfos_extra);
			}
		}else{
			if(juego.torres.resistencia_torre_2 > 99){
				printf("║   Resistencia Torre 2: %i                       Elfos extra Restantes: %i    ║\n",juego.torres.resistencia_torre_2,juego.torres.elfos_extra);
			}else if(juego.torres.resistencia_torre_2 > 9){
				printf("║   Resistencia Torre 2: %i                       Elfos extra Restantes: %i     ║\n",juego.torres.resistencia_torre_2,juego.torres.elfos_extra);
			}else{
				printf("║   Resistencia Torre 2: %i                       Elfos extra Restantes: %i      ║\n",juego.torres.resistencia_torre_2,juego.torres.elfos_extra);
			}
		}
	}
	printf("╠═══╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦═════╣\n");
}

void mostrar_presentacion_nivel_grande(juego_t juego){
	int enemigos_muetos=0;
	for(int i=0;i<juego.nivel.tope_enemigos;i++){
		if(juego.nivel.enemigos[i].vida <= 0){
			enemigos_muetos++;
		}
	}

	printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
	printf("║                                       Defendiendo las Torres                                           ║\n");
	printf("╠════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
	if(enemigos_muetos > 9 && enemigos_muetos <= 99){
		printf("║   Nivel: %i                                                              Enemigos Muertos: %i / %i     ║\n", juego.nivel_actual+1, enemigos_muetos,juego.nivel.max_enemigos_nivel);
	}else if(enemigos_muetos > 99){
		printf("║   Nivel: %i                                                              Enemigos Muertos: %i / %i    ║\n", juego.nivel_actual+1, enemigos_muetos,juego.nivel.max_enemigos_nivel);
	}else{
		printf("║   Nivel: %i                                                              Enemigos Muertos: %i / %i      ║\n", juego.nivel_actual+1, enemigos_muetos,juego.nivel.max_enemigos_nivel);
	}
	printf("║                                                                                                        ║\n");

	if(juego.torres.enanos_extra < 10){
		if(juego.torres.resistencia_torre_1 > 99){
			printf("║   Resistencia Torre 1: %i                                                Enanos extra Restantes: %i    ║\n",juego.torres.resistencia_torre_1,juego.torres.enanos_extra);
		}else if(juego.torres.resistencia_torre_1 > 9){
			printf("║   Resistencia Torre 1: %i                                                Enanos extra Restantes: %i     ║\n",juego.torres.resistencia_torre_1,juego.torres.enanos_extra);
		}else{
			printf("║   Resistencia Torre 1: %i                                                Enanos extra Restantes: %i      ║\n",juego.torres.resistencia_torre_1,juego.torres.enanos_extra);
		}
	}else{
		if(juego.torres.resistencia_torre_1 > 99){
			printf("║   Resistencia Torre 1: %i                                                Enanos extra Restantes: %i   ║\n",juego.torres.resistencia_torre_1,juego.torres.enanos_extra);
		}else if(juego.torres.resistencia_torre_1 > 9){
			printf("║   Resistencia Torre 1: %i                                                Enanos extra Restantes: %i    ║\n",juego.torres.resistencia_torre_1,juego.torres.enanos_extra);
		}else{
			printf("║   Resistencia Torre 1: %i                                                Enanos extra Restantes: %i     ║\n",juego.torres.resistencia_torre_1,juego.torres.enanos_extra);
		}
	}
	if(juego.torres.elfos_extra < 10){
			if(juego.torres.resistencia_torre_2 > 99){
				printf("║   Resistencia Torre 2: %i                                                Elfos extra Restantes: %i     ║\n",juego.torres.resistencia_torre_2,juego.torres.elfos_extra);
			}else if(juego.torres.resistencia_torre_2 > 9){
				printf("║   Resistencia Torre 2: %i                                                Elfos extra Restantes: %i      ║\n",juego.torres.resistencia_torre_2,juego.torres.elfos_extra);
			}else{
				printf("║   Resistencia Torre 2: %i                                                Elfos extra Restantes: %i       ║\n",juego.torres.resistencia_torre_2,juego.torres.elfos_extra);
			}
		}else{
			if(juego.torres.resistencia_torre_2 > 99){
				printf("║   Resistencia Torre 2: %i                                                Elfos extra Restantes: %i    ║\n",juego.torres.resistencia_torre_2,juego.torres.elfos_extra);
			}else if(juego.torres.resistencia_torre_2 > 9){
				printf("║   Resistencia Torre 2: %i                                                Elfos extra Restantes: %i     ║\n",juego.torres.resistencia_torre_2,juego.torres.elfos_extra);
			}else{
				printf("║   Resistencia Torre 2: %i                                                Elfos extra Restantes: %i      ║\n",juego.torres.resistencia_torre_2,juego.torres.elfos_extra);
			}
		}
	printf("╠═══╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦═════╣\n");
}

void inicializar_matriz(char matriz[MAX_FILAS][MAX_COLUMNAS]){
	for(int i=0; i < MAX_FILAS; i++){
		for(int j=0; j < MAX_COLUMNAS; j++){
			matriz[i][j] = VACIO;
		}
	}
}

void llenar_defensores(char matriz[MAX_FILAS][MAX_COLUMNAS], juego_t juego){
	for(int i=0; i < juego.nivel.tope_defensores; i++){
		if(juego.nivel.defensores[i].tipo == ENANO){
			matriz[juego.nivel.defensores[i].posicion.fil][juego.nivel.defensores[i].posicion.col] = ENANO;
		}
		if(juego.nivel.defensores[i].tipo == ELFO){
			matriz[juego.nivel.defensores[i].posicion.fil][juego.nivel.defensores[i].posicion.col] = ELFO;
		}
	}
}

void llenar_orcos(char matriz[MAX_FILAS][MAX_COLUMNAS], juego_t juego){
	for(int i=0; i < juego.nivel.tope_enemigos; i++){
		if(juego.nivel.enemigos[i].vida > 0){
			if(juego.nivel.enemigos[i].camino == CAMINO_1){
				if(juego.nivel.enemigos[i].vida > 199){
					matriz[juego.nivel.camino_1[juego.nivel.enemigos[i].pos_en_camino].fil][juego.nivel.camino_1[juego.nivel.enemigos[i].pos_en_camino].col] = ORCOS;
				}else if(juego.nivel.enemigos[i].vida > 99){
					matriz[juego.nivel.camino_1[juego.nivel.enemigos[i].pos_en_camino].fil][juego.nivel.camino_1[juego.nivel.enemigos[i].pos_en_camino].col] = ORCOS_VIDA_MEDIA;
				}else{
					matriz[juego.nivel.camino_1[juego.nivel.enemigos[i].pos_en_camino].fil][juego.nivel.camino_1[juego.nivel.enemigos[i].pos_en_camino].col] = ORCOS_CHICA_VIDA;
				}
			}else{
				if(juego.nivel.enemigos[i].vida > 199){
					matriz[juego.nivel.camino_2[juego.nivel.enemigos[i].pos_en_camino].fil][juego.nivel.camino_2[juego.nivel.enemigos[i].pos_en_camino].col]  = ORCOS;
				}else if(juego.nivel.enemigos[i].vida > 99){
					matriz[juego.nivel.camino_2[juego.nivel.enemigos[i].pos_en_camino].fil][juego.nivel.camino_2[juego.nivel.enemigos[i].pos_en_camino].col] = ORCOS_VIDA_MEDIA;
				}else{
					matriz[juego.nivel.camino_2[juego.nivel.enemigos[i].pos_en_camino].fil][juego.nivel.camino_2[juego.nivel.enemigos[i].pos_en_camino].col]  = ORCOS_CHICA_VIDA;
				}
			}
		}	
	}
}

void llenar_torres_y_entradas(char matriz[MAX_FILAS][MAX_COLUMNAS], juego_t juego){
	if(juego.nivel.tope_camino_1 > 0){
		matriz[juego.nivel.camino_1[0].fil][juego.nivel.camino_1[0].col] = ENTRADA_1;
		matriz[juego.nivel.camino_1[juego.nivel.tope_camino_1 - 1].fil][juego.nivel.camino_1[juego.nivel.tope_camino_1 - 1].col] = TORRE_1;
	}
	if(juego.nivel.tope_camino_2 > 0){
		matriz[juego.nivel.camino_2[0].fil][juego.nivel.camino_2[0].col] = ENTRADA_2;
		matriz[juego.nivel.camino_2[juego.nivel.tope_camino_2 - 1].fil][juego.nivel.camino_2[juego.nivel.tope_camino_2 - 1].col] = TORRE_2;
	}
}

void llenar_caminos(char matriz[MAX_FILAS][MAX_COLUMNAS], juego_t juego){
	for(int i=0; i < juego.nivel.tope_camino_1; i++){
		matriz[juego.nivel.camino_1[i].fil][juego.nivel.camino_1[i].col] = CAMINO_UNO;
	
	}
	for(int i=0; i < juego.nivel.tope_camino_2; i++){
		if(matriz[juego.nivel.camino_2[i].fil][juego.nivel.camino_2[i].col] == CAMINO_UNO){
			matriz[juego.nivel.camino_2[i].fil][juego.nivel.camino_2[i].col] = DOS_CAMINOS;
		}else{
			matriz[juego.nivel.camino_2[i].fil][juego.nivel.camino_2[i].col] = CAMINO_DOS;
		}
	
	}
}

void mostrar_mapa(char matriz[MAX_FILAS][MAX_COLUMNAS], int tope){
	printf("\n");

	for(int i=0; i < tope; i++){
		if(i<10){
			printf("║ 0%i║",i );
		}else{
			printf("║ %i║",i );
		}
		for(int j=0; j < tope; j++){
			if(matriz[i][j] == CAMINO_UNO){
				verde();
				printf("`¸'`,");
				blanco();
			}else if(matriz[i][j] == CAMINO_DOS){
				bold_amarillo();
				printf("`¸'`,");
				blanco();
			}else if(matriz[i][j] == DOS_CAMINOS){
				printf("`¸'`,");
			}else if(matriz[i][j] == ORCOS){
				printf("  ");
				verde();
				printf("O");
				blanco();
				printf("  ");
			}else if(matriz[i][j] == ORCOS_VIDA_MEDIA){
				printf("  ");
				bold_amarillo();
				printf("O");
				blanco();
				printf("  ");
			}else if(matriz[i][j] == ORCOS_CHICA_VIDA){
				printf("  ");
				bold_rojo();
				printf("O");
				blanco();
				printf("  ");
			}else if(matriz[i][j] == ENANO){
				bold_magenta();
				printf("░[G]░");
				blanco();
			}else if(matriz[i][j] == ELFO){
				bold_magenta();
				printf("░[L]░");
				blanco();
			}else if(matriz[i][j] == ENTRADA_1){
				printf("[E-1]");
			}else if(matriz[i][j] == ENTRADA_2){
				printf("[E-2]");
			}else if(matriz[i][j] == TORRE_1){
				printf("[T-1]");
			}else if(matriz[i][j] == TORRE_2){
				printf("[T-2]");
			}else{
				printf("▒▒▒▒▒");
			}
		}
		printf("║\n");
	}
}

//Pre: Recibe un nivel 15x15
//Post: Muestra el nivel 15x15
void mostrar_nivel_chico(juego_t juego){
	char matriz[MAX_FILAS][MAX_COLUMNAS];
	int i;

	inicializar_matriz(matriz);

	llenar_caminos(matriz, juego);

	llenar_defensores(matriz, juego);

	llenar_orcos(matriz, juego);

	llenar_torres_y_entradas(matriz, juego);

	printf("║###║");
	for(i=0; i<TOPE_NIVEL_CHICO;i++){
		if(i==14){
			printf(" %i  ║",i);
		}else if(i<10){
			printf(" 0%i ║",i );
		}else{
			printf(" %i ║",i );
		}
	}
	printf("\n");

	printf("╠═══╬");
	for(i=0; i<TOPE_NIVEL_CHICO;i++){
		if(i==14){
			printf("═════╣");
		}else{
			printf("════╩");
		}
	}

	mostrar_mapa(matriz, TOPE_NIVEL_CHICO);
	
	printf("╠═══╩═══════════════════════════════════════════════════════════════════════════╣\n");
}

//Pre: Recibe un nivel 20x20
//Post: Muestra el nivel 20x20
void mostrar_nivel_grande(juego_t juego){
	char matriz[MAX_FILAS][MAX_COLUMNAS];
	int i;

	inicializar_matriz(matriz);

	llenar_defensores(matriz, juego);
	
	llenar_caminos(matriz, juego);

	llenar_orcos(matriz, juego);

	llenar_torres_y_entradas(matriz, juego);
	
	printf("║###║");
	for(i=0; i<TOPE_NIVEL_GRANDE;i++){
		if(i==19){
			printf(" %i  ║",i);
		}else if(i<10){
			printf(" 0%i ║",i );
		}else{
			printf(" %i ║",i );
		}
	}
	printf("\n");

	printf("╠═══╬");
	for(i=0; i<TOPE_NIVEL_GRANDE;i++){
		if(i==19){
			printf("═════╣");
		}else{
			printf("════╩");
		}
	}
	
	mostrar_mapa(matriz, TOPE_NIVEL_GRANDE);
	
	printf("╠═══╩════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
}

/* 
 * Mostrará el mapa dependiendo del nivel en que se encuentra el jugador.
 */
void mostrar_juego(juego_t juego){
	switch(juego.nivel_actual){
		case NIVEL_1:
			mostrar_presentacion_nivel_chico(juego);
			mostrar_nivel_chico(juego);
			break;
		case NIVEL_2:
			mostrar_presentacion_nivel_chico(juego);
			mostrar_nivel_chico(juego);
			break;
		case NIVEL_3:
			mostrar_presentacion_nivel_grande(juego);
			mostrar_nivel_grande(juego);
			break;
		case NIVEL_4:
			mostrar_presentacion_nivel_grande(juego);
			mostrar_nivel_grande(juego);
			break;
	}
}