#include "graficos.h"
#include "utiles.h"


static const int MENU = 0;
const int CARACT_DEFENSOR = 1;
const int CARACT_ENEMIGOS = 2;
const int CARACT_TORRES = 3;
const int CONVENCIONES = 4; 
static const int EMPEZAR_JUEGO_SIN_ANIMOS = 5;
static const int EMPEZAR_JUEGO_CON_ANIMOS = 6;
static const int VALOR_DEFENSOR_EXTRA = 50;
static const int ATAQUE_BASE_ENANO = 60;
static const int ATAQUE_CRITICO_ENANO = 100;
static const int ATAQUE_BASE_ELFO = 30;
static const int ATAQUE_CRITICO_ELFO = 70;
static const int VIDA_BASE_ORCO = 200;
static const int VIDA_EXTRA_ORCO = 101;
static const int RESISTENCIA_BASE_TORRES = 600;
static const int DEFENSORES_EXTRA_ENANOS = 10;
static const int DEFENSORES_EXTRA_ELFOS = 10;
static const int VIENTO_BASE = 50;
static const int HUMEDAD_BASE = 50;
static const char ANIMO_GIMLI_BASE = 'R';
static const char ANIMO_LEGOLAS_BASE = 'R';
static const char ELFO  = 'L';
static const char ENANO = 'G';
static const char ORCOS = 'O';
static const char TORRE = 'T';
static const char ENTRADA = 'E';

static const int PERDIO = -1;
static const int GANO =  1 ;

static const char CAMINO_UNO = '#';
static const char CAMINO_DOS = '&';
static const char DOS_CAMINOS = 'C';
static const char ENTRADA_1 = 'P';
static const char ENTRADA_2 = 'E';
static const char TORRE_1 = 'Y';
static const char TORRE_2 = 'T';
static const char VACIO = '-';


/* Parte: Funciones color */

void static amarillo(){
	printf("\033[1;33m");
}
void static verde(){
	printf("\033[0;32m");
}
void static blanco(){
	printf("\033[0m");
}
static void bold_amarillo(){
	printf("\033[1;33m");
}
void blanco_remarcado(){
	printf("\033[7;37m");
}

/*          Parte: PRESENTACION         */


//Post: Imprime el menu:
void mostrar_menu(){
	printf("#######################################################################################################################################\n");
	printf("#                                                                                                                                     #\n");
	printf("#                                                 Defendiendo las Torres: MENU                                                        #\n");
	printf("#                                                                                                                                     #\n");
	printf("#######################################################################################################################################\n");
	printf("#                                                                                                                                     #\n");
	printf("#                                                                                                                                     #\n");
	printf("#   Este juego consiste en defender dos torres de ordas de orcos, los defensores pueden ser enanos conducidos Gimli y elfos           #\n");
	printf("#   conducidos por Legolas. El juego tiene 4 niveles que consite  en las cuatro entradas hacia las torres por cada punto cardinal:    #\n");
	printf("#                                                                                                                                     #\n");
	printf("#      »Entrada Este: Posee un camino que conduce a la Torre 1, la defensa fue asignada a Gimli y sus equipo de enanos.               #\n");
	printf("#                     »Tamaño horda: 100 orcos(Cada 25 orcos se podra colocar un enano extra)                                         #\n");
	printf("#                                                                                                                                     #\n");
	printf("#      »Entrada Oeste: Posee un camino que conduce a la Torre 2, la defensa fue asignada a Legolas y sus equipo de elfos.             #\n");
	printf("#                      »Tamaño horda: 200 orcos(Cada 50 orcos se podra colocar un enano extra)                                        #\n");
	printf("#                                                                                                                                     #\n");
	printf("#      »Entrada Norte: Posee dos caminos que uno conuce a la Torre 1 y el otro a la Torre 2. La defensa fue asignada a Legolas y  a   #\n");
	printf("#                      Gimli que combinaron sus equipos para defender las torres.                                                     #\n");
	printf("#                      »Tamaño horda: 150 orcos por cada camino.(Cada 50 orcos se podra colocar un enano extra)                       #\n");
	printf("#                                                                                                                                     #\n");
	printf("#      »Entrada Sur: Posee dos caminos que uno conuce a la Torre 1 y el otro a la Torre 2. La defensa fue asignada a Legolas y  a     #\n");
	printf("#                    Gimli que combinaron sus equipos para defender las torres.                                                       #\n");
	printf("#                      »Tamaño horda: 250 orcos por cada camino.(Cada 50 orcos se podra colocar un enano extra)                       #\n");
	printf("#                                                                                                                                     #\n");
	printf("#                                                                                                                                     #\n");
	printf("#   El juego se ganara si se mata a la horda de la entrada sur sin que ninguna de las torres haya sido destruida, si alguna de las    #\n");
	printf("#   torres es destruida se perdera el juego.                                                                                          #\n");
	printf("#   Para evitarlo usted podra colocar los defensores que defienden cada entrada alrededor del camino de las hordas.                   #\n");
	printf("#                           (No se podra colocar un defensor sobre otro o sobre el camino!!!)                                         #\n");
	printf("#                                                                                                                                     #\n");
	printf("#######################################################################################################################################\n");
	
}  
//Post Imprime la caracteristicass de los defensores                               
void mostrar_defensores(){
	printf("#######################################################################################################################################\n");
	printf("#                                                                                                                                     #\n");
	printf("#                                      Defendiendo las Torres: Caracteristicas Defensores.                                            #\n");
	printf("#                                                                                                                                     #\n");
	printf("#######################################################################################################################################\n");
	printf("#                                                                                                                                     #\n");
	printf("#  ENANO                                                                                                                              #\n");
	printf("#  -> Rango de ataque: todos los casilleros alrededor                                                                                 #\n");
	printf("#  -> Ataque base: %i                                                                                                                 #\n",ATAQUE_BASE_ENANO);
	printf("#  -> Ataque critico: %i                                                                                                             #\n",ATAQUE_CRITICO_ENANO);
	printf("#  -> Porcentaje de fallo: Mitad de la humedad                                                                                        #\n");
	printf("#  -> Porcentaje de critico: Depende del animo de Gimli                                                                               #\n");
	printf("#                                                                                                                                     #\n");
	printf("#  ELFO                                                                                                                               #\n");
	printf("#  -> Rango de ataque: 3 casilleros de distancia (Distancia Taxi)                                                                     #\n");
	printf("#  -> Ataque base: %i                                                                                                                 #\n",ATAQUE_BASE_ELFO);
	printf("#  -> Ataque critico: %i                                                                                                              #\n",ATAQUE_CRITICO_ELFO);
	printf("#  -> Porcentaje de fallo: Mitad del viento                                                                                           #\n");
	printf("#  -> Porcentaje de critico: Depende del animo de Legolas                                                                             #\n");
	printf("#                                                                                                                                     #\n");
	printf("#  INFLUENCIA ANIMO                                                                                                                   #\n");
	printf("#    -> Animo Malo: 0%% ataques critico                                                                                                #\n");
	printf("#    -> Animo Regolar: 10%% ataques critico                                                                                            #\n");
	printf("#    -> Animo Bueno: 25%% ataques critico                                                                                              #\n");
	printf("#                                                                                                                                     #\n");
	printf("#######################################################################################################################################\n");
}
//Post Imprime la caracteristicass de los enemigos
void mostrar_enemigos(){
	printf("#######################################################################################################################################\n");
	printf("#                                                                                                                                     #\n");
	printf("#                                              Defendiendo las Torres: Enemigos                                                       #\n");
	printf("#                                                                                                                                     #\n");
	printf("#######################################################################################################################################\n");
	printf("#                                                                                                                                     #\n");
	printf("#  ORCO                                                                                                                               #\n");
	printf("#  -> Vida Base: %i                                                                                                                  #\n",VIDA_BASE_ORCO);
	printf("#  -> Vida Extra: entre 0 y %i                                                                                                       #\n",(VIDA_EXTRA_ORCO-1));
	printf("#  -> Vida Total: Vida base + Vida Extra.                                                                                             #\n");
	printf("#  -> Los orcos no atacan los defensores solo caminan por el camino hasta llegar a la torre o morir en el intento.                    #\n");
	printf("#  -> Si el orco llega a la torre le sacara la vida restante del orco                                                                 #\n");
	printf("#                                                                                                                                     #\n");
	printf("#######################################################################################################################################\n");
}
//Post Imprime la caracteristicass de las torres
void mostrar_torres(){
	printf("#######################################################################################################################################\n");
	printf("#                                                                                                                                     #\n");
	printf("#                                                  Defendiendo las Torres: Torres                                                     #\n");
	printf("#                                                                                                                                     #\n");
	printf("#######################################################################################################################################\n");
	printf("#                                                                                                                                     #\n");
	printf("#  TORRE 1                                                                                                                            #\n");
	printf("#  -> Estara al final del camino 1                                                                                                    #\n");
	printf("#  -> Resistencia base: %i                                                                                                           #\n",RESISTENCIA_BASE_TORRES);
	printf("#  -> Defensor extra: %i Enanos                                                                                                       #\n",DEFENSORES_EXTRA_ENANOS);
	printf("#  -> Cada defensor extra costara %i                                                                                                  #\n", VALOR_DEFENSOR_EXTRA);
	printf("#                                                                                                                                     #\n");
	printf("#  TORRE 2                                                                                                                            #\n");
	printf("#  -> Estara al final del camino 2                                                                                                    #\n");
	printf("#  -> Resistencia base: %i                                                                                                           #\n",RESISTENCIA_BASE_TORRES);
	printf("#  -> Defensor extra: %i Elfos                                                                                                        #\n",DEFENSORES_EXTRA_ELFOS);
	printf("#  -> Cada defensor extra costara %i                                                                                                  #\n", VALOR_DEFENSOR_EXTRA);
	printf("#                                                                                                                                     #\n");
	printf("#######################################################################################################################################\n");
}
//Post Imprime las convenciones
void mostrar_convenciones(){
	printf("#######################################################################################################################################\n");
	printf("#                                                                                                                                     #\n");
	printf("#                                                  Defendiendo las Torres: Convenciones                                               #\n");
	printf("#                                                                                                                                     #\n");
	printf("#######################################################################################################################################\n");
	printf("#                                                                                                                                     #\n");
	printf("# »Elfos: %c                                                                                                                           #\n",ELFO);
	printf("# »Enanos: %c                                                                                                                          #\n",ENANO);
	printf("# »Orcos: %c                                                                                                                           #\n",ORCOS);
	printf("# »Torres: %c                                                                                                                          #\n",TORRE);
	printf("# »Entradas: %c                                                                                                                        #\n",ENTRADA);
	printf("#                                                                                                                                     #\n");
	printf("# ANIMOS BASE:                                                                                                                        #\n");
	printf("#    »Viento: %i                                                                                                                      #\n",VIENTO_BASE);
	printf("#    »Humedad: %i                                                                                                                     #\n",HUMEDAD_BASE);
	printf("#    »Animo Legolas: %c                                                                                                                #\n",ANIMO_LEGOLAS_BASE);
	printf("#    »Animo Gimli: %c                                                                                                                  #\n",ANIMO_GIMLI_BASE);
	printf("#                                                                                                                                     #\n");
	printf("#######################################################################################################################################\n");
}



void mostrar_caracteristicas_juego(int* selector){
	while(*selector != EMPEZAR_JUEGO_CON_ANIMOS && *selector != EMPEZAR_JUEGO_SIN_ANIMOS){
		if(*selector == MENU){
			mostrar_menu();
		}else if(*selector == CARACT_DEFENSOR){
			mostrar_defensores();
		}else if(*selector == CARACT_ENEMIGOS){
			mostrar_enemigos();
		}else if(*selector == CARACT_TORRES){
			mostrar_torres();
		}else if(*selector == CONVENCIONES){
			mostrar_convenciones();
		}else{
			printf("#######################################################################################################################################\n");
			printf("#                                                                                                                                     #\n");
			printf("#   Parece que se equivoco de numero                                                                                                  #\n");
		}
		
		printf("#                                                                                                                                     #\n");
		printf("#  Presione:                                                                                                                          #\n");
		printf("#      » ");
		if(*selector == MENU){
			blanco_remarcado();
		}	
		printf("0 para ir al menu.");
		blanco();
		printf("                                                                                                           #\n");
		printf("#      » ");
		if(*selector == CARACT_DEFENSOR){
			blanco_remarcado();
		}	
		printf("1 para ir a caracteristicas de los defensores.");
		blanco();
		printf("                                                                               #\n");
		printf("#      » ");
		if(*selector == CARACT_ENEMIGOS){
			blanco_remarcado();
		}	
		printf("2 para ir a caracteristicas de los enemigos.");
		blanco();
		printf("                                                                                 #\n");
		printf("#      » ");
		if(*selector == CARACT_TORRES){
			blanco_remarcado();
		}	
		printf("3 para ir a caracteristicas Torres.");
		blanco();
		printf("                                                                                          #\n");
		printf("#      » ");
		if(*selector == CONVENCIONES){
			blanco_remarcado();
		}	
		printf("4 para ir Convenciones.");
		blanco();
		printf("                                                                                                      #\n");
		printf("#      » 5 para inicializar el juego con animos base(Mirar convenciones).                                                             #\n");
		printf("#      » 6 para inicializar el juego eligiendo animos.                                                                                #\n");
		printf("#                                                                                                                                     #\n");
		printf("#######################################################################################################################################\n");
		scanf("%i",selector);
		system("clear");
	}

}
void mostrar_carga_presentacion(){
	int i;
	char carga[110];

	system("clear");
	
	for(i=0; i<101; i++){
		carga[i]= '.';
	}
	for(i=0; i<101; i++){
		printf("                                          ___ . .  _                                                                                                     \n");
		printf("                                 'T$$$P'   |  |_| |_                                                                                                     \n");
		printf("                                  :$$$     |  | | |_                                                                                                     \n");
		printf("                                  :$$$                                                      'T$$$$$$$b.                                                  \n");
		printf("                                  :$$$     .g$$$$$p.   T$$$$b.    T$$$$$bp.                   BUG    'Tb      T$b      T$P   .g$P^^T$$  ,gP^^T$$         \n");
		printf("                                   $$$    d^'     '^b   $$  'Tb    $$    'Tb    .s^s. :sssp   $$$     :$; T$$P $^b.     $   dP'     `T :$P    `T         \n");
		printf("                                   :$$   dP         Tb  $$   :$;   $$      Tb  d'   `b $      $$$     :$;  $$  $ `Tp    $  d$           Tbp.             \n");
		printf("                                   :$$  :$;         :$; $$   :$;   $$      :$; T.   .P $^^    $$$    .dP   $$  $   ^b.  $ :$;            'T$$p.          \n");
		printf("                                   $$$  :$;         :$; $$...dP    $$      :$;  `^s^' .$.     $$$...dP'    $$  $    `Tp $ :$;     \"T$$      \"T$b       \n");
		printf("                                   $$$   Tb.       ,dP  $$\"\"\"Tb    $$      dP \"\"$\"\"$\" \"$\"$^^  $$$\"\"T$b     $$  $      ^b$  T$       T$ ;      $$;      \n");
		printf("                                   $$$    Tp._   _,gP   $$   `Tb.  $$    ,dP    $  $...$ $..  $$$   T$b    :$  $       `$   Tb.     :$ T.    ,dP       \n");
		printf("                                   $$$;    \"^$$$$$^\"   d$$     `T.d$$$$$P^\"     $  $\"\"\"$ $\"\", $$$    T$b  d$$bd$b      d$b   \"^TbsssP\" 'T$bgd$P        \n");   
		printf("                                   $$$b.____.dP                                 $ .$. .$.$ss,d$$$b.   T$b.                                               \n");
		printf("                                .d$$$$$$$$$$P                                                         `T$b.                                             \n");
		printf("                                                                                                                                                              \n");
		printf("                                                                                                                                                              \n");
		printf("                               oooooooooo.              .o88o.                             .o8   o8o                              .o8                             \n");
		printf("                               `888'   `Y8b             888 `\"                            \"888   `\"'                             \"888                             \n");
		printf("                                888      888  .ooooo.  o888oo   .ooooo.  ooo. .oo.    .oooo888  oooo   .ooooo.  ooo. .oo.    .oooo888   .ooooo.                   \n");
		printf("                                888      888 d88' `88b  888    d88' `88b `888P\"Y88b  d88' `888  `888  d88' `88b `888P\"Y88b  d88' `888  d88' `88b                  \n");
		printf("                                888      888 888ooo888  888    888ooo888  888   888  888   888   888  888ooo888  888   888  888   888  888   888                  \n");
		printf("                                888     d88' 888    .o  888    888    .o  888   888  888   888   888  888    .o  888   888  888   888  888   888                  \n");
		printf("                               o888bood8P'   `Y8bod8P' o888o   `Y8bod8P' o888o o888o `Y8bod88P\" o888o `Y8bod8P' o888o o888o `Y8bod88P\" `Y8bod8P'                  \n");
		printf("                                                                                                                                                                  \n");
		printf("                                                                             oooo                                                                                 \n"); 
		printf("                                                                             `888                                                                                 \n"); 
		printf("                                                                              888   .oooo.    .oooo.o                                                             \n"); 
		printf("                                                                              888  `P  )88b  d88(  \"8                                                             \n");
		printf("                                                                              888   .oP\"888  `\"Y88b.                                                              \n");
		printf("                                                                              888  d8(  888  o.  )88b                                                             \n");
		printf("                                                                             o888o `Y888\"\"8o 8\"\"888P'                                                             \n");
		printf("                                                                                                                                                                  \n");
		printf("                                                          ooooooooooooo                                                                                           \n");
		printf("                                                          8'   888   `8                                                                                           \n");
		printf("                                                               888       .ooooo.  oooo d8b oooo d8b  .ooooo.   .oooo.o                                            \n");
		printf("                                                               888      d88' `88b `888\"\"8P `888\"\"8P d88' `88b d88(  \"8                                            \n");
		printf("                                                               888      888   888  888      888     888ooo888 `\"Y88b.                                             \n");
		printf("                                                               888      888   888  888      888     888    .o o.  )88b                                            \n");
		printf("                                                              o888o     `Y8bod8P' d888b    d888b    `Y8bod8P' 8\"\"888P'                                            \n");
		printf("                                                                                                                                                                  \n");
		printf("                                                                                                                                                              \n");
		printf("                                                                                                                                                              \n");
		printf("                                    |");

		for(int j=0; j<100; j++){
			if(carga[j] == '#'){
				verde();
				printf("%c",carga[j]);
				blanco();
			}else{
				printf("%c",carga[j]);
			}	
		}	
		
		printf("|  %i%%\n",i);
		detener_el_tiempo(0.1f);
		carga[i]= '#';
		system("clear");
	}	
}



/*       Parte: MOSTRAR CARGA NIVEL */



void mostrar_carga_nivel_1(){
	int i;
	char carga[110];

	system("clear");
	
	for(i=0; i<101; i++){
		carga[i]= '.';
	}
	for(i=0; i<101; i++){

		printf("\n                                                                                                                                                          \n");
		printf("                                                                                                                             _.-;-._                      \n");
		printf("                                                                                                                            ;_.JL___;                     \n");
		printf("                             ____        __                _ _                _                                             F\"-/\\_-7L                     \n");
		printf("                            |  _ \\  ___ / _| ___ _ __   __| (_) ___ _ __   __| | ___                                        | a/ e | \\                    \n");
		printf("                            | | | |/ _ \\ |_ / _ \\ '_ \\ / _` | |/ _ \\ '_ \\ / _` |/ _ \\                                      ,L,c;,.='/;,                   \n");
		printf("                            | |_| |  __/  _|  __/ | | | (_| | |  __/ | | | (_| | (_) |                                  _,-;;S:;:S;;:' '--._              \n");
		printf("                            |____/ \\___|_|  \\___|_| |_|\\__,_|_|\\___|_| |_|\\__,_|\\___/                                  ;. \\;;s:::s;;: .'   /\\             \n");
		printf("                                                   _                                                                  /  \\  ;::::;;  /    /  \\            \n");
		printf("                                                  | | __ _ ___                                                       / ,  k ;S';;'S.'    j __,l           \n");
		printf("                                                  | |/ _` / __|                                                   ,---/| /  /S   /S '.   |'   ;           \n");
		printf("                                                  | | (_| \\__ \\                                                  ,Ljjj |/|.' s .' s   \\  L    |           \n");
		printf("                                                  |_|\\__,_|___/                                                  LL,_ ]( \\    /    '.  '.||   ;           \n");
		printf("                                          _____                                                                  ||\\ > /  ;-.'_.-.___\\.-'(|==\"(           \n");
		printf("                                         |_   _|__  _ __ _ __ ___  ___                                           JJ,\" /   |_  [   ]     _]|   /           \n");
		printf("                                           | |/ _ \\| '__| '__/ _ \\/ __|                                           LL\\/   ,' '--'-'-----'  \\  (            \n");
		printf("                                           | | (_) | |  | | |  __/\\__ \\                                           ||     ;      |          |  >           \n");
		printf("                                           |_|\\___/|_|  |_|  \\___||___/                                           JJ     |      |\\         |,/            \n");
		printf("                                                                                                                   LL    |      ||       ' |              \n");
		printf("                                                                                                                   ||    |      ||       . |              \n");
		printf("                                                                                                                   JJ    /_     ||       ;_|              \n");
		printf("                                            _   _ _           _   __                                                LL   L \"==='|i======='_|              \n");
		printf("                                           | \\ | (_)         | | /  |                                               ||    i----' '-------';               \n");
		printf("                                           |  \\| |___   _____| | `| |                                               JJ    ';-----.------,-'               \n");
		printf("                                           | . ` | \\ \\ / / _ \\ |  | |                                                LL     L_.__J,'---;'                 \n");
		printf("                                           | |\\  | |\\ V /  __/ | _| |_                                               ||      |   ,|    (                  \n");
		printf("                                           |_| \\_|_| \\_/ \\___|_| \\___/                                               JJ     .'=  (|  ,_|                  \n");
		printf("                                                                                                                      LL   /    .'L_    \\                 \n");
		printf("                                                                                                                snd   ||   '---'    '.___>                \n");
		printf("                                                                                                                                                          \n");
		printf("                   	                                                                                                                                    \n");
		printf("                                                                                                                                                          \n");
		printf("          |");

		for(int j=0; j<100; j++){
			if(carga[j] == '#'){
				verde();
				printf("%c",carga[j]);
				blanco();
			}else{
				printf("%c",carga[j]);
			}	
		}	
		
		printf("|  %i%%\n",i);
		detener_el_tiempo(0.1f);
		carga[i]= '#';
		system("clear");
	}	
}

void mostrar_carga_nivel_2(){
	int i;
	char carga[110];
	system("clear");
	
	for(i=0; i<101; i++){
		carga[i]= '.';
	}
	for(i=0; i<101; i++){
		printf("\n\n                             .;;,.                                                                                                         \n");
		printf("                            ; '\" ;\\ \\//                                                                                                     \n");
		printf("                           \\|> (<|7 \\//                                                                                                      \n");
		printf("                           j| ..  | ||/                                                                                                        \n");
		printf("                          //'.--.')\\-,/                                                                                                       \n");
		printf("                        .-||- '' ||/  `-.                               ____        __                _ _                _                     \n");
		printf("                       ;  | \\ |/ |/ L.  ,|                             |  _ \\  ___ / _| ___ _ __   __| (_) ___ _ __   __| | ___              \n");
		printf("                       f\\ |\\| Y  || \\ '._\\                             | | | |/ _ \\ |_ / _ \\ '_ \\ / _` | |/ _ \\ '_ \\ / _` |/ _ \\     \n");
		printf("                      j | \\|     (| |   | |                            | |_| |  __/  _|  __/ | | | (_| | |  __/ | | | (_| | (_) |             \n");
		printf("                     |  L_\\         L.__: |                            |____/ \\___|_|  \\___|_| |_|\\__,_|_|\\___|_| |_|\\__,_|\\___/        \n");
		printf("                      \\(  '-.,-,    |   ; |                                                   _                                               \n");
		printf("                       |'-.'.L_rr>  f--f  |                                                  | | __ _ ___                                      \n");
		printf("          .-=,,______,--------- J-. ;  ;__                        	                     | |/ _` / __|                                     \n");
		printf("             ``\"-,__   |  |      h  |  f  '--.__                                             | | (_| \\__ \\                                  \n");
		printf("                 `--;;--,_       h  f-j   |   __;==-.             	                     |_|\\__,_|___/                                      \n");
		printf("                      / `-''-,,__J,'  \\_..--:'-'     '                              _____                                                     \n");
		printf("                      | |    `' --L7//'-'`|                                        |_   _|__  _ __ _ __ ___  ___                               \n");
		printf("                      | ,     ||  h    |  (                                          | |/ _ \\| '__| '__/ _ \\/ __|                            \n");
		printf("                      | ;     | \\ J    j   |                                         | | (_) | |  | | |  __/\\__ \\                           \n");
		printf("                      | L__   | |  L_.'    |                                         |_|\\___/|_|  |_|  \\___||___/                            \n");
		printf("                      |   |'-.| L.'h  |  : |                                                                                                   \n");
		printf("                      |;  \\     |  J ; : : |                                                                                                  \n");
		printf("                      | :  (    \\  'L| : : |                                         _   _ _           _   _____                              \n");
		printf("                      | ;   \'.--|    \\  : |                                         | \\ | (_)         | | / __  \\                          \n");
		printf("                      | | : \\    \\-, /`\\ : |                                        |  \\| |___   _____| | `' / /'                          \n");
		printf("                      L-'-;__\\   \\ '  | | |                                         | . ` | \\ \\ / / _ \\ |   / /                           \n");
		printf("                              ;   \\   |'L_j                                         | |\\  | |\\ V /  __/ | ./ /__                            \n");
		printf("                              _>  _|   |                                            |_| \\_|_| \\_/ \\___|_| \\_____/                          \n");
		printf("                       snd   <___/ /-  \\                                                                                                      \n");
		printf("                                  /    /                                                                                                       \n");
		printf("                                  '---'                                                                                                        \n");
		printf("                                                                                                                                               \n");
		printf("                                                                                                                                               \n");
		printf("                            |");
		

		for(int j=0; j<100; j++){
			if(carga[j] == '#'){
				verde();
				printf("%c",carga[j]);
				blanco();
			}else{
				printf("%c",carga[j]);
			}	
		}	
		
		printf("|  %i%%\n",i);
		detener_el_tiempo(0.1f);
		carga[i]= '#';
		system("clear");
	}	
}

void mostrar_carga_nivel_grande(int nivel){
	int i;
	char carga[110];
	system("clear");
	
	for(i=0; i<101; i++){
		carga[i]= '.';
	}
	for(i=0; i<101; i++){
		printf("\n                      .;;,.                                                                                                                                      \n");         
		printf("                     ; '\" ;\\ \\//                                                                                                                                 \n");            
		printf("                    \\|a (a|7 \\//                                                                                                        _.-;-._                  \n");    
		printf("                    j| ..  | ||/                                                                                                       ;_.JL___;                 \n");   
		printf("                   //'.--.')\\-,/                                                                                                       F\"-/\\_-7L                 \n");    
		printf("                 .-||- '' ||/  `-.                    ____        __                _ _                _                               | a/ e | \\                \n");       
		printf("                ;  | \\ |/ |/ L.  ,|                  |  _ \\  ___ / _| ___ _ __   __| (_) ___ _ __   __| | ___                         ,L,c;,.='/;,               \n");       
		printf("                f\\ |\\| Y  || \\ '._\\                  | | | |/ _ \\ |_ / _ \\ '_ \\ / _` | |/ _ \\ '_ \\ / _` |/ _ \\                     _,-;;S:;:S;;:' '--._     \n");           
		printf("               j | \\|     (| |   | |                 | |_| |  __/  _|  __/ | | | (_| | |  __/ | | | (_| | (_) |                   ;. \\;;s:::s;;: .'   /\\         \n");             
		printf("              |  L_\\         L.__: |                 |____/ \\___|_|  \\___|_| |_|\\__,_|_|\\___|_| |_|\\__,_|\\___/                   /  \\  ;::::;;  /    /  \\        \n");              
		printf("               \\(  '-.,-,    |   ; |                                        _                                                   / ,  k ;S';;'S.'    j __,l       \n");              
		printf("                |'-.'.L_rr>  f--f  |                                       | | __ _ ___                                      ,---/| /  /S   /S '.   |'   ;       \n");              
		printf("   .-=,,______,--------- J-. ;  ;__             	                   | |/ _` / __|                                    ,Ljjj |/|.' s .' s   \\  L    |      \n");               
		printf("      ``\"-,__   |  |      h  |  f  '--.__                                  | | (_| \\__ \\                                     LL,_ ]( \\    /    '.  '.||   ;      \n");               
		printf("          `--;;--,_       h  f-j   |   __;==-.  	                   |_|\\__,_|___/                                     ||\\ > /  ;-.'_.-.___\\.-'(|==\"(     \n");                
		printf("               / `-''-,,__J,'  \\_..--:'-'     '                   _____                                                      JJ,\" /   |_  [   ]     _]|   /      \n");               
		printf("               | |    `' --L7//'-'`|                             |_   _|__  _ __ _ __ ___  ___                                LL\\/   ,' '--'-'-----'  \\  (       \n");               
		printf("               | ,     ||  h    |  (                               | |/ _ \\| '__| '__/ _ \\/ __|                               ||     ;      |          |  >      \n");               
		printf("               | ;     | \\ J    j   |                              | | (_) | |  | | |  __/\\__ \\                               JJ     |      |\\         |,/       \n");               
		printf("               | L__   | |  L_.'    |                              |_|\\___/|_|  |_|  \\___||___/                                LL    |      ||       ' |         \n");               
		printf("               |   |'-.| L.'h  |  : |                                                                                          ||    |      ||       . |         \n");               
		printf("               |;  \\     |  J ; : : |                                                                                          JJ    /_     ||       ;_|         \n");               
		
		if(nivel == NIVEL_3){
			printf("                | :  (    \\  'L| : : |                             _   _ _           _   _____                                  LL   L \"==='|i======='_|    \n");     
			printf("                | ;   \'.--|    \\  : |                             | \\ | (_)         | | |____ |                                 ||    i----' '-------';     \n");      
			printf("                | | : \\    \\-, /`\\ : |                            |  \\| |___   _____| |     / /                                 JJ    ';-----.------,-'     \n");   
			printf("                L-'-;__\\   \\ '  | | |                             | . ` | \\ \\ / / _ \\ |     \\ \\                                  LL     L_.__J,'---;'       \n");      
			printf("                        ;   \\   |'L_j                             | |\\  | |\\ V /  __/ | .___/ /                                  ||      |   ,|    (        \n");     
			printf("                        _>  _|   |                                |_| \\_|_| \\_/ \\___|_| \\____/                                   JJ     .'=  (|  ,_|        \n");  
			printf("                 snd   <___/ /-  \\                                                                                                LL   /    .'L_    \\       \n");            
			printf("                            /    /                                                                                          snd   ||   '---'    '.___>      \n");      
			printf("                            '---'                                                                                                                            \n");
		}else{
			printf("               | :  (    \\  'L| : : |                              _   _ _           _     ___                                 LL   L \"==='|i======='_|  \n");  
			printf("               | ;   \'.--|    \\  : |                              | \\ | (_)         | |   /   |                                ||    i----' '-------';   \n");        
			printf("               | | : \\    \\-, /`\\ : |                             |  \\| |___   _____| |  / /| |                                JJ    ';-----.------,-'   \n");     
			printf("               L-'-;__\\   \\ '  | | |                              | . ` | \\ \\ / / _ \\ | / /_| |                                 LL     L_.__J,'---;'     \n");        
			printf("                       ;   \\   |'L_j                              | |\\  | |\\ V /  __/ | \\___  |                                 ||      |   ,|    (      \n");       
			printf("                       _>  _|   |                                 |_| \\_/_| \\_/ \\___|_|     |_/                                 JJ     .'=  (|  ,_|      \n");  
			printf("                snd   <___/ /-  \\                                                                                                LL   /    .'L_    \\     \n");              
			printf("                           /    /                                                                                          snd   ||   '---'    '.___>    \n");        
			printf("                           '---'                                                                                                                          \n");        
		}                                                                                                                                     
		
		printf("                                                                                                                                                           \n");
		printf("                                                                                                                                                           \n");
		printf("                               |");
	                                                                                                                             
		for(int j=0; j<100; j++){
			if(carga[j] == '#'){
				verde();
				printf("%c",carga[j]);
				blanco();
			}else{
				printf("%c",carga[j]);
			}	
		}	
		
		printf("|  %i%%\n",i);
		detener_el_tiempo(0.1f);
		carga[i]= '#';
		system("clear");
	}	
}

void mostrar_carga(int nivel){
	if(nivel == NIVEL_1){
		mostrar_carga_nivel_1();
	}else if(nivel == NIVEL_2){
		mostrar_carga_nivel_2();
	}else{
		mostrar_carga_nivel_grande(nivel);
	}
}


/*    Parte: MOSTRAR FINAL NIVEL */



void mostra_horda_derrotada_nivel_chico(juego_t defendiendo_torres){
	system("clear");
	for(int i=3; i>0; i--){
		mostrar_juego(defendiendo_torres);
		printf("║                                                                               ║\n");
		if(defendiendo_torres.nivel_actual == NIVEL_1){
			printf("║        La primer horda a sido derrotada. Pasando de nivel en %i...             ║\n",i);
		}else{
			printf("║        La segunda horda a sido derrotada. Pasando de nivel en %i...            ║\n",i);
		}
		printf("║                                                                               ║\n");
		printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n");
		detener_el_tiempo(1);
		system("clear");
	}
}

void mostra_horda_derrotada_nivel_grande(juego_t defendiendo_torres){
	system("clear");
	for(int i=3; i>0; i--){
		mostrar_juego(defendiendo_torres);
		printf("║                                                                                                        ║\n");
		printf("║                      La tercer horda a sido derrotada. Pasando de nivel en %i...                        ║\n",i);
		printf("║                                                                                                        ║\n");
		printf("╚════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
		detener_el_tiempo(1);
		system("clear");
	}
} 


/*    Parte: MOSTRAR FINAL JUEGO */


//Pre: Se perdio el juego
//Post: Muestra el una "imagen" de perdiste
void mostrar_perdiste(){
	for(int i=0;i<8;i++){
		amarillo();
		printf("\n\n                            \\ : /                                                            \n"); 
		printf("                         '-: __ :-'                                                          \n"); 
		printf("                         -:  )(_ :--                                                         \n"); 
		blanco();
		printf("                         -' |r-_i'-                                                          \n"); 
		printf("                 ,sSSSSs,   (2-,7                                                            \n"); 
		printf("                 sS';:'`Ss   )-j                    ____              _ _     _              \n"); 
		printf("                ;K e (e s7  /  (                   |  _ \\ ___ _ __ __| (_)___| |_ ___        \n"); 
		printf("                 S, ''  SJ (  ;/                   | |_) / _ \\ '__/ _` | / __| __/ _ \\       \n"); 
		printf("                 sL_~~_;(S_)  _7                   |  __/  __/ | | (_| | \\__ \\ ||  __/       \n"); 
		printf("     |,          'J)_.-' />'-' `Z                  |_|   \\___|_|  \\__,_|_|___/\\__\\___|       \n"); 
		printf("     j J         /-;-A'-'|'--'-j\\                                                            \n");
		printf("      L L        )  |/   :    /  \\                                                           \n");
		printf("       \\ \\       | | |    '._.'|  L                                                          \n");
		printf("        \\ \\      | | |       | \\  J                   \"One ring to rule them all,            \n"); 
		printf("         \\ \\    _/ | |       |  ',|                      one ring to find them,              \n"); 
		printf("          \\ L.,' | | |       |   |/                    One ring to bring them all            \n");
		printf("         _;-r-<_.| \\=\\    __.;  _/                    and in the darkness bind them.\"        \n"); 
		printf("           {_}\"  L-'  '--'   / /|                                                            \n");
		printf("                 |   ,      |  \\|                                                            \n");
		printf("                 |   |      |   \")                                                           \n");
		printf("                 L   ;|     |   /|                                                           \n");
		printf("                /|    ;     |  / |                     El juego se cerrara en %i ...          \n",(8-i)); 
		printf("               | |    ;     |  ) |                                                           \n");
		printf("              |  |    ;|    | /  |                                                           \n");
		printf("              | ;|    ||    | |  |                                                           \n");
		printf("              L-'|____||    )/   |                                                           \n");
		printf("                  %% %%/ '-,- /    /                                                           \n");
		printf("          snd     |%% |   \\%%/_    |                                                           \n");
		printf("               ___%%  (   )%% |'-; |                                                           \n");
		printf("             C;.---..'   >%%,(   \"'                                                           \n");
		printf("                        /%%%% /                                                                \n");
		printf("                       Cccc'                                                                 \n");

		detener_el_tiempo(1);
		system("clear");
	}
}

//Pre: Se gano el juego
//Post: Muestra el una "imagen" de ganaste
void mostrar_ganaste(){
	for(int i=0;i<8;i++){
      	printf("\n\n                                                                                                           ....                            \n");
      	printf("                                                                                                        .'' .'''                           \n");
      	printf("                                                                        .                             .'   :                               \n");
      	printf("              ____                       _                              \\\\                          .:    :                                \n");
      	printf("             / ___| __ _ _ __   __ _ ___| |_ ___                         \\\\                        _:    :       ..----.._                 \n");
      	printf("            | |  _ / _` | '_ \\ / _` / __| __/ _ \\                         \\\\                    .:::.....:::.. .'         ''.              \n");
      	printf("            | |_| | (_| | | | | (_| \\__ \\ ||  __/                          \\\\                 .'  #-. .-######'     #        '.            \n");
      	printf("             \\____|\\__,_|_| |_|\\__,_|___/\\__\\___|                           \\\\                 '.##'/ ' ################       :           \n");
      	printf("                                                                             \\\\                  #####################         :           \n");
      	printf("                                                                              \\\\               ..##.-.#### .''''###'.._        :           \n");
      	printf("   \"Espera mi llegada con la primera luz del quinto día,                       \\\\             :--:########:            '.    .' :          \n");
      	printf("                                                                                \\\\..__...--.. :--:#######.'   '.         '.     :          \n");
      	printf("                   al alba mira al este.\"                                       :     :  : : '':'-:'':'::        .         '.  .'          \n");
      	printf("                                                                                '---'''..: :    ':    '..'''.      '.        :'            \n");
      	printf("                                                                                   \\\\  :: : :     '      ''''''.     '.      .:            \n");
      	printf("                                                                                    \\\\ ::  : :     '            '.      '      :           \n");
      	printf("                 El juego se cerrara en %i ...                                        \\\\::   : :           ....' ..:       '     '.         \n",(8-i));
      	printf("                                                                                      \\\\::  : :    .....####\\\\ .~~.:.             :        \n");
      	printf("                                                                                       \\\\':.:.:.:'#########.===. ~ |.'-.   . '''.. :       \n");
      	printf("                                                                                        \\\\    .'  ########## \\ \\ _.' '. '-.       '''.     \n");
      	printf("                                                                                        :\\\\  :     ########   \\ \\      '.  '-.        :    \n");
      	printf("                                                                                       :  \\\\'    '   #### :    \\ \\      :.    '-.      :   \n");
      	printf("                                                                                      :  .'\\\\   :'  :     :     \\ \\       :      '-.    :  \n");
      	printf("                                                                                     : .'  .\\\\  '  :      :     :\\ \\       :        '.   : \n");
      	printf("                                                                                     ::   :  \\\\'  :.      :     : \\ \\      :          '. : \n");
      	printf("                                                                                     ::. :    \\\\  : :      :    ;  \\ \\     :           '.: \n");
      	printf("                                                                                      : ':    '\\\\ :  :     :     :  \\:\\     :        ..'   \n");
      	printf("                                                                                         :    ' \\\\ :        :     ;  \\|      :   .'''      \n");
      	printf("                                                                                         '.   '  \\\\:                         :.''          \n");
      	printf("                                                                                          .:..... \\\\:       :            ..''              \n");
      	printf("                                                                                         '._____|'.\\\\......'''''''.:..'''                  \n");
      	printf("                                                                                                    \\\\                                     \n");

      	detener_el_tiempo(1);
      	system("clear");
     }
}



void mostrar_final_juego(juego_t juego){
	if(estado_juego(juego) == PERDIO){
		mostrar_perdiste();
	}
	if(estado_juego(juego) == GANO){
		mostrar_ganaste();
	}
}



/* Parte: MOSTRAR CREANDO CAMINOS */


static void inicializar_matriz(char matriz[MAX_FILAS][MAX_COLUMNAS]){
	for(int i=0; i < MAX_FILAS; i++){
		for(int j=0; j < MAX_COLUMNAS; j++){
			matriz[i][j] = VACIO;
		}
	}
}

void llenar_torres_y_entradas_custom(char matriz[MAX_FILAS][MAX_COLUMNAS], camino_nivel_t caminos){
	if(caminos.tope_camino_1 > 0){
		matriz[caminos.camino_1[0].fil][caminos.camino_1[0].col] = ENTRADA_1;
		matriz[caminos.torre_1.fil][caminos.torre_1.col] = TORRE_1;
	}
	if(caminos.tope_camino_2 > 0){
		matriz[caminos.camino_2[0].fil][caminos.camino_2[0].col] = ENTRADA_2;
		matriz[caminos.torre_2.fil][caminos.torre_2.col] = TORRE_2;
	}
}

void llenar_caminos_custom(char matriz[MAX_FILAS][MAX_COLUMNAS], camino_nivel_t caminos){
	for(int i=0; i < caminos.tope_camino_1; i++){
		matriz[caminos.camino_1[i].fil][caminos.camino_1[i].col] = CAMINO_UNO;
	
	}
	for(int i=0; i < caminos.tope_camino_2; i++){
		if(matriz[caminos.camino_2[i].fil][caminos.camino_2[i].col] == CAMINO_UNO){
			matriz[caminos.camino_2[i].fil][caminos.camino_2[i].col] = DOS_CAMINOS;
		}else{
			matriz[caminos.camino_2[i].fil][caminos.camino_2[i].col] = CAMINO_DOS;
		}
	
	}
}

void mostrar_mapa_caminos(char matriz[MAX_FILAS][MAX_COLUMNAS], int tope){
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
			}else if(matriz[i][j] == TORRE_1){
				printf("[T-1]");
			}else if(matriz[i][j] == TORRE_2){
				printf("[T-2]");
			}else if(matriz[i][j] == ENTRADA_1){
				printf("[E-1]");
			}else if(matriz[i][j] == ENTRADA_2){
				printf("[E-2]");
			}else{
				printf("▒▒▒▒▒");
			}
		}
		printf("║\n");
	}
}


void mostrar_crear_camino(camino_nivel_t caminos, int nivel){
	char matriz[MAX_FILAS][MAX_COLUMNAS];
	int tope;

	inicializar_matriz(matriz);
	llenar_caminos_custom(matriz, caminos);
	llenar_torres_y_entradas_custom(matriz, caminos);

	if(nivel == NIVEL_1 || nivel == NIVEL_2){
		tope = TOPE_NIVEL_CHICO;
		printf("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
		printf("║                            Defendiendo las Torres            NIVEL: %i         ║\n",(nivel+1));
		printf("╠═══╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦═════╣\n");
	}else{
		tope = TOPE_NIVEL_GRANDE;
		printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
		printf("║                               Defendiendo las Torres                            NIVEL: %i               ║\n",(nivel+1));
		printf("╠═══╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦════╦═════╣\n");
	}

	printf("║###║");
	for(int i=0; i<tope;i++){
		if(i==(tope-1)){
			printf(" %i  ║",i);
		}else if(i<10){
			printf(" 0%i ║",i );
		}else{
			printf(" %i ║",i );
		}
	}
	printf("\n");

	printf("╠═══╬");
	for(int i=0; i<tope;i++){
		if(i==(tope-1)){
			printf("═════╣");
		}else{
			printf("════╩");
		}
	}

	mostrar_mapa_caminos(matriz, tope);

	if(nivel == NIVEL_1 || nivel == NIVEL_2){
		printf("╠═══╩═══════════════════════════════════════════════════════════════════════════╣\n");
	}else{
		printf("╠═══╩════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
	}
}



/* Parte: CARACTERISTICAS DEFENSOR */


/*
*Este procedimiento imprime la caracteristicas del defensor
*	que va a ser agregado
*/
void caracteristicas_defensor(juego_t defendiendo_torres,char tipo){
	if(tipo == ENANO){
		if(defendiendo_torres.nivel_actual == NIVEL_1 || defendiendo_torres.nivel_actual == NIVEL_2){
			printf("║Defensor siendo agregado:                                                      ║\n");
			printf("║  -> Tipo: ENANO                                                               ║\n");
			printf("║  -> Ataque base: %i                                                           ║\n",ATAQUE_BASE_ENANO);
			printf("║  -> Ataque critico: %i                                                       ║\n",ATAQUE_CRITICO_ENANO);
			printf("║  -> Porcentaje de fallo: %i%%                                                  ║\n",defendiendo_torres.fallo_gimli);
			printf("║  -> Porcentaje de critico: %i%%                                                ║\n",defendiendo_torres.critico_gimli);
		}else{
			printf("║Defensor siendo agregado:                                                                               ║\n");
			printf("║  -> Tipo: ENANO                                                                                        ║\n");
			printf("║  -> Ataque base: %i                                                                                    ║\n",ATAQUE_BASE_ENANO);
			printf("║  -> Ataque critico: %i                                                                                ║\n",ATAQUE_CRITICO_ENANO);
			printf("║  -> Porcentaje de fallo: %i%%                                                                           ║\n",defendiendo_torres.fallo_gimli);
			printf("║  -> Porcentaje de critico: %i%%                                                                         ║\n",defendiendo_torres.critico_gimli);
		}
	}else{
		if(defendiendo_torres.nivel_actual == NIVEL_1 || defendiendo_torres.nivel_actual == NIVEL_2){
			printf("║Defensor siendo agregado:                                                      ║\n");
			printf("║  -> Tipo: ELFO                                                                ║\n");
			printf("║  -> Ataque base: %i                                                           ║\n",ATAQUE_BASE_ELFO);
			printf("║  -> Ataque critico: %i                                                        ║\n",ATAQUE_CRITICO_ELFO);
			printf("║  -> Porcentaje de fallo: %i%%                                                  ║\n",defendiendo_torres.fallo_legolas);
			printf("║  -> Porcentaje de critico: %i%%                                                ║\n",defendiendo_torres.critico_legolas);
		}else{
			printf("║Defensor siendo agregado:                                                                               ║\n");
			printf("║  -> Tipo: ELFO                                                                                         ║\n");
			printf("║  -> Ataque base: %i                                                                                    ║\n",ATAQUE_BASE_ELFO);
			printf("║  -> Ataque critico: %i                                                                                 ║\n",ATAQUE_CRITICO_ELFO);
			printf("║  -> Porcentaje de fallo: %i%%                                                                           ║\n",defendiendo_torres.fallo_legolas);
			printf("║  -> Porcentaje de critico: %i%%                                                                         ║\n",defendiendo_torres.critico_legolas);
		}
	}
}


void mostrar_defensores_por_agregar(int por_agregar_enano,int por_agregar_elfo,int nivel){
	if((por_agregar_elfo+por_agregar_enano)>0){	
		if(nivel <= NIVEL_2){
			printf("║AGREGAR DEFENSOR                                                               ║\n");
			printf("║»Defensores restantes:                                                         ║\n");
			printf("║             ->Enanos: %i                                                       ║\n",por_agregar_enano);
			printf("║             ->Elfos: %i                                                        ║\n",por_agregar_elfo);
		}else{
			printf("║AGREGAR DEFENSOR                                                                                        ║\n");
			printf("║»Defensores restantes:                                                                                  ║\n");
			printf("║             ->Enanos: %i                                                                                ║\n",por_agregar_enano);
			printf("║             ->Elfos: %i                                                                                 ║\n",por_agregar_elfo);
		}
	}
}


void mostrar_ingresar_nombre(char nombre[MAX_NOMBRE]){
	printf("###################################################\n");
	printf("#                                                 #\n");
	printf("#          Por favor ingrese su nombre            #\n");
	printf("#                                                 #\n");
	printf("###################################################\n");
	printf("Nombre: ");
	scanf(" %[^\n]",nombre);
	system("clear");
}


/*        Parte: Mostrar preguntas configuracion         */

void mostrar_preguntar_resistencia_torres(int numero_torre, int max_resistencia_torres){
	system("clear");
	printf("####################################################\n");
	printf("#                                                  #\n");
	printf("#       Ingrese la resistecia de la Torre %i        #\n",(numero_torre+1));
	printf("#                                                  #\n");
	printf("####################################################\n");
	printf("#                                                  #\n");
	printf("#    »La resistencia debe ser menor a %i.      #\n",max_resistencia_torres);
	printf("#    »La resistencia no puede ser negativa.        #\n");
	printf("#    »Si ingresa -1 se utilizara la resistencia    #\n");
	printf("#      default del juego.                          #\n");
	printf("#                                                  #\n");
	printf("####################################################\n");		
}


void mostrar_preguntar_defensores_nivel(int nivel, char nombre_defensor[MAX_NOMBRE],int max_def_nivel){
	system("clear");
	printf("####################################################\n");
	printf("#                                                  #\n");
	printf("#       Ingrese los %s del nivel %i             #\n",nombre_defensor,(nivel+1));
	printf("#                                                  #\n");
	printf("####################################################\n");
	printf("#                                                  #\n");
	printf("#    »Los %s deben ser menor a %i.               #\n",nombre_defensor,max_def_nivel);
	printf("#    »La cantidad no puede se negativa.            #\n");
	printf("#    »Si ingresa -1 se utilizara los defensores    #\n");
	printf("#      default del nivel.                          #\n");
	printf("#                                                  #\n");
	printf("####################################################\n");	
}


void mostrar_preguntar_defensores_extra(char nombre_defensor_extra[MAX_NOMBRE], int max_coste_def, int max_def_extra){
	system("clear");
	printf("####################################################\n");
	printf("#                                                  #\n");
	printf("#          Ingrese los %s extra                 #\n",nombre_defensor_extra);
	printf("#                                                  #\n");
	printf("####################################################\n");
	printf("#                                                  #\n");
	printf("#    »Los %s deben ser menor a %i.           #\n",nombre_defensor_extra,max_def_extra);
	printf("#    »El coste de las torres tiene que ser menor   #\n");
	printf("#       a %i                                   #\n",max_coste_def);
	printf("#    »La cantidad no puede se negativa.            #\n");
	printf("#    »Si ingresa -1 se utilizara los defensores    #\n");
	printf("#     extra o coste default                        #\n");
	printf("#                                                  #\n");
	printf("####################################################\n");
}


void mostrar_preguntar_animos_defensor(char nombre_defensor_extra[MAX_NOMBRE], int max_animos){
	system("clear");
	printf("####################################################\n");
	printf("#                                                  #\n");
	printf("#        Ingrese el animo de los %s             #\n",nombre_defensor_extra);
	printf("#                                                  #\n");
	printf("####################################################\n");
	printf("#                                                  #\n");
	printf("#    »El fallo y critico de los %s deben ser    #\n",nombre_defensor_extra);
	printf("#        menor igual a %i.                        #\n",max_animos);
	printf("#    »El porcentaje no puede se negativo.          #\n");
	printf("#    »Si ingresa -1 se utilizara los porcentajes   #\n");
	printf("#     default                                      #\n");
	printf("#                                                  #\n");
	printf("####################################################\n");
}


void mostrar_preguntar_velocidad(int max_velocidad){
	system("clear");
	printf("####################################################\n");
	printf("#                                                  #\n");
	printf("#        Ingrese la velocidad del juego            #\n");
	printf("#                                                  #\n");
	printf("####################################################\n");
	printf("#                                                  #\n");
	printf("#    »La velocidad tiene que ser menor a %i        #\n",max_velocidad);
	printf("#    »El porcentaje no puede se negativo.          #\n");
	printf("#    »Si ingresa -1 se utilizara la velocidad      #\n");
	printf("#     default                                      #\n");
	printf("#                                                  #\n");
	printf("####################################################\n");
}

void mostrar_preguntar_ruta_camino(){	
	system("clear");
	printf("####################################################\n");
	printf("#                                                  #\n");
	printf("#   Ingrese el nombre de tu camino personalizado   #\n");
	printf("#                                                  #\n");
	printf("####################################################\n");
	printf("#                                                  #\n");
	printf("#    »Si ingresa -1 se utilizara caminos random.   #\n");
	printf("#    »El nombre debe ser sin espacios.             #\n");
	printf("#    »Si se desea se puede agregar la extension    #\n");
	printf("#     del archivo.                                 #\n");
	printf("#                                                  #\n");
	printf("####################################################\n");
}