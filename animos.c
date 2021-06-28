#include "animos.h"
#include<stdlib.h>

const int DIA_MAX = 30;
const int DIA_MIN = 1;
const int DURMIO_HORA_MAX = 12;
const int DURMIO_HORA_MIN = 0;
const int PUNTOS_DURMIO_POCO = 0;
const int DURMIO_POCO_MIN = 0;
const int DURMIO_POCO_MAX = 4;
const int PUNTOS_DURMIO_NORMAL = 10;
const int DURMIO_NORMAL_MIN = 5;
const int DURMIO_NORMAL_MAX = 8;
const int PUNTOS_DURMIO_MUCHO = 20;
const char MANIANA = 'M';
const char TARDE = 'T';
const char NOCHE = 'N';
const char ENSALADA = 'E';
const int PUNTOS_ENSALADA = 20;
const char HAMBURGUESA = 'H';
const int PUNTOS_HAMBURGUESA = 15;
const char PIZZA = 'P';
const int PUNTOS_PIZZA = 10;
const char GUISO = 'G';
const int PUNTOS_GUISO = 5;
const int VIENTO_FUERTE = 75;
const int DIA_MAX_VIENTO_FUERTE = 10;
const int DIA_MIN_VIENTO_FUERTE = 1;
const int VIENTO_MEDIO = 50;
const int DIA_MAX_VIENTO_MEDIO = 20;
const int DIA_MIN_VIENTO_MEDIO = 11;
const int VIENTO_DEBIL = 25;
const int HUMEDAD_ALTA = 75;
const int HUMEDAD_MEDIA = 50;
const int HUMEDAD_CHICA = 25;
const char ANIMO_MALO = 'M';
const char ANIMO_REGULAR = 'R';
const int PUNTOS_MIN_ANIMO_REGULAR = 21;
const int PUNTOS_MAX_ANIMO_REGULAR = 35;
const char ANIMO_BUENO = 'B';
const int PUNTOS_MIN_ANIMO_BUENO = 36;
const int PUNTOS_MAX_ANIMO_BUENO = 50;
const char PIE_DERECHO = 'D';
const char PIE_IZQUIERDO = 'I';
const int PUNTOS_PIE_DERECHO = 10;
const int PUNTOS_PIE_IZQUIERDO = 0;
const char PRIMER_MINUS = 'a';
const char ULTIMA_MINUS = 'z';


//Parte:Determinar el dia del mes
//Pre: Un numero
//Post: Devuelve true si el numero esta en el rango de dias del mes
bool dia_valido(int dia_mes){
	return((dia_mes >= DIA_MIN) && (dia_mes <= DIA_MAX));
}
//Pre: Un numero fuera del rango del mes
//Post: Devuelve true si el numero era menor al rango de mes
bool dia_menor_a_rango(int dia_mes){
	return(dia_mes < DIA_MIN);
}
//Pre:---
//post: Un dia del mes en un rango valido
void determinar_dia_mes(int *dia_mes){
	printf("\n»Un nuevo estudio cientifico(que no voy a citar) determino que por la cuarentena la tierra giro un toque mas lento, por lo que realmente seguimos en el mes de abril que solo tiene 30 dias. Esto provoca que el dia del mes tendra un efecto en el viento");
	printf("\n»Le pido muy amablemente que introduzca el dia del mes(entre 1 y 30): ");
	scanf(" %i",dia_mes);
	while(!(dia_valido(*dia_mes))){
		if(dia_menor_a_rango(*dia_mes)){
			printf("\n»Me contaron por aca que los dias del mes no pueden ser negativos o nulos.\n»Por favor ingresa un dia valido(entre 1 y 30): ");
			scanf(" %i",dia_mes);
		}else{
			printf("\n»Che puede ser que abril tiene solo 30 dias?\n»Plischu ingresa un numero entre 1 y 30:");
			scanf(" %i",dia_mes);
		}
	}
}
//Parte: Determinar viento.
//Pre: Un numero en rango del dia de mes
//Post: Devuelve true si el numero esta en el rango de dias de viento fuerte
bool dias_en_rango_viento_fuerte(int dia_mes){
	return((dia_mes >= DIA_MIN_VIENTO_FUERTE)&&(dia_mes <= DIA_MAX_VIENTO_FUERTE));
}
//Pre: Un numero en rango del dia de mes
//Post: Devuelve true si el numero esta en el rango de dias de viento medio
bool dias_en_rango_viento_medio(int dia_mes){
	return((dia_mes >= DIA_MIN_VIENTO_MEDIO)&&(dia_mes <= DIA_MAX_VIENTO_MEDIO));
}
//Pre: Recibe un dia entre 1 y 30
//Post: Devuelve una velocidad de viento ya definida
int velocidad_viento(int dia_mes){
	if(dias_en_rango_viento_fuerte(dia_mes)){
		return VIENTO_FUERTE;
	}else if(dias_en_rango_viento_medio(dia_mes)){
		return VIENTO_MEDIO;
	}else{
		return VIENTO_DEBIL;
	}
}
//Parte:Determinar hora del dia
//Pre: Recibe una letra
//Post: Devuelve true si la letra coincide con la inicial de una de las horas del dia
bool hora_valida(char hora_dia){
	return((hora_dia == MANIANA)||(hora_dia == TARDE)||(hora_dia == NOCHE));	
}
//Pre: Recibe una letra
//Post: Devolvera true si la letra es una minuscula
bool letra_minus(char hora_dia){
	return((hora_dia >= PRIMER_MINUS)&&(hora_dia <= ULTIMA_MINUS));
}
//Pre:---
//Post: Devuelve la hora del dia
void determinar_hora_dia(char* hora_dia){
	printf("\n»Necesitamos determinar que hora del dia es para poder saber la humedad. Lamentablemente nadie tiene reloj.");
	printf("\n»Por eso te asignamos la complicada labor de mirar al cielo y decirnos si es la Mañana(M), la Tarde(T) o es de Noche(N): ");
	scanf(" %c",hora_dia);
	
	while(!(hora_valida(*hora_dia))){
		if(letra_minus(*hora_dia)){
			printf("\n»Estoy bastante seguro que habia que ingresar letra mayuscula. Trata de ingresar devuelta que hora del dia es Mañana(M), la Tarde(T) o es de Noche(N):");
			scanf(" %c", hora_dia);
		}else{
			printf("\n»Ufa, sino nos querias decir la hora no pasa nada.\n»Cualquier cosa si te equivocaste trata de ingresar un caracter el caracter nuevamente(Mañana(M),Tarde(T),Noche(N)):");
			scanf(" %c", hora_dia);
		}
	}
}
//Parte:Determinar Humedad
//Pre: Recibe una hora del dia valida 
//Post: Devuelve una humedad ya definida
int porcentaje_humedad(char hora_dia){
	if(hora_dia == MANIANA){
		return HUMEDAD_ALTA;
	}else if(hora_dia == TARDE){
		return HUMEDAD_CHICA;
	}else{
		return HUMEDAD_MEDIA;
	}
}
//Parte:Determinar el Pie
//Pre: Recibe un letra.
//Post: Devolvera true si el letra coincide con 
bool pie_valido(char pie){
	return((pie == PIE_DERECHO)||(pie == PIE_IZQUIERDO));
}
//Pre:---
//Post:Devuelve un caracter correspondiente al pie con que se levanto
void con_que_pie_se_levanto(char* pie){
	printf("\n»Algo totalmente importante es saber con que pie se levanto, todos saben que esto afecta tu animo.\n»Fue con el pie derecho(D) o el izquierdo(I)? ");
	scanf(" %c",pie);
	while(!(pie_valido(*pie))){
		printf("\n»Y si lo llama Roman, se tiene que levantar si o si con un pie.Mira que no es facil decirle que no a Roman.\n»Por Dieguito ingresame con que pie se levanto (Derecho(D) o Izquier(I)):");
		scanf(" %c",pie);
	}
}
//Pre: Una letra correspondiente a el pie con el que se levanto el personaje
//Post: Devuelve un puntaje correspondiente al pie
int puntos_pie(char pie){
	if(pie == PIE_DERECHO){
		return PUNTOS_PIE_DERECHO;
	}else{
		return PUNTOS_PIE_IZQUIERDO;
	}
}
//Parte:Cena
//Pre:Recibe un caracter
//Post: Devuelve true si el caracter concide con la incial de las cenas
bool cena_valida(char cena){
	return((cena == GUISO)||(cena == PIZZA)||(cena == HAMBURGUESA)||(cena == ENSALADA));
}
//Pre:---
//Post:Devuelve una letra valida que corresponde a una cena
void que_ceno(char* cena){
	printf("\n»Necesitamos saber que comio para determinar su animo.\n»Que ceno? Guiso(G),Pizza(P),Hamburguesa(H) o Ensalada(E): ");
	scanf(" %c",cena);
	while(!(cena_valida(*cena))){
		printf("\n»Che no somos MasterChef. Por favor comformate con Guiso(G),Pizza(P),Hamburguesa(H) o Ensalada(E):");
		scanf(" %c",cena);
	}
}
//Pre: Recibe una letra valida correspondiente a una cena
//Post: Devuelve el puntaje que corresponde a la cena
int puntos_cena(char cena){
	if(cena == GUISO){
		return PUNTOS_GUISO;
	}else if(cena == PIZZA){
		return PUNTOS_PIZZA;
	}else if(cena == HAMBURGUESA){
		return PUNTOS_HAMBURGUESA;
	}else{
		return PUNTOS_ENSALADA;
	}
}
//Parte:Horas dormidas
//Pre: Recibe un numero
//Post: Devuelve true si el numero esta entre horas dormidas minima y maxima
bool horas_dormidas_valida(int horas_dormidas){
	return((horas_dormidas >= DURMIO_HORA_MIN)&&(horas_dormidas <= DURMIO_HORA_MAX));
}
//Pre: Recibe un numero fuera de rango
//Post: Devuelve true si durmio horas menores al rango
bool durmio_horas_menores_al_rango(int horas_dormidas){
	return(horas_dormidas < DURMIO_HORA_MIN);
}
//Pre:---
//Post: Devuelve un numero en el rango de horas dormidas
void cuanto_durmio(int* horas_dormidas){
	printf("\n»Por ultimo necesitamos saber cuanto durmio? Nuestros cientificos hicieron los calculos y solo se puede dormir entre 0 y 12.\n»Ingrese cuantas horas durmio: ");
	scanf("%i",horas_dormidas);
	while(!(horas_dormidas_valida(*horas_dormidas))){
		if(durmio_horas_menores_al_rango(*horas_dormidas)){
			printf("\n»Si queres romper el espacio tiempo anda a Volver al Futuro.\n»Ahora trata de ingresar devuelta cuantas horas durmio(Era entre 0 y 12): ");
			scanf("%i",horas_dormidas);
		}else{
			printf("\n»Nuestros cientificos no se equivocan!! No se puede dormir mas que 12 horas.\n»Por  favor ingresa la cantidad de horas que durmio(Era entre 0 y 12):");
			scanf("%i",horas_dormidas);
		}
	}
}
//Pre: Un nmero en el rango de horas dormidas permitidas
//Post: Devuelve true si el numero esta en el rango de durmio poco
bool durmio_poco(int horas_dormidas){
	return((horas_dormidas >= DURMIO_POCO_MIN)&&(horas_dormidas <= DURMIO_POCO_MAX));
}
//Pre: Un nmero en el rango de horas dormidas permitidas
//Post: Devuelve true si el numero esta en el rango de durmio poco
bool durmio_normal(int horas_dormidas){
	return((horas_dormidas >= DURMIO_NORMAL_MIN)&&(horas_dormidas <= DURMIO_NORMAL_MAX));
}
//Pre: Una cantidad de horas dormidas en rango valido
//Post: Un puntaje correspondiente a esas horas dormidas
int puntos_horas_dormidas(int horas_dormidas){
	if(durmio_poco(horas_dormidas)){
		return PUNTOS_DURMIO_POCO;
	}else if(durmio_normal(horas_dormidas)){
		return PUNTOS_DURMIO_NORMAL;
	}else{
		return PUNTOS_DURMIO_MUCHO;
	}
}
//Parte:Determinar animo
//Pre:---
//Post: Devuelve un pie valido, una cena valida y una cantidad de horas dormidas de rango
void preguntas_determinar_animo(char* pie,char* cena,int* horas_dormidas){
	con_que_pie_se_levanto(pie);
	que_ceno(cena);
	cuanto_durmio(horas_dormidas);
}
//Pre: Un pie valido, una cena valida y horas dormidas en rango
//Post: Devuelve un puntaje entre 0 y 50
int puntaje_animo(char pie,char cena,int horas_dormidas){
	int puntos_animo = 0;
	
	puntos_animo += puntos_pie(pie);
	puntos_animo += puntos_cena(cena);
	puntos_animo += puntos_horas_dormidas(horas_dormidas);
	return puntos_animo;
}
//Pre: Recibe un puntaje entre 0 y 50
//Post: Devuelve true si el puntaje esta en rango del puntaje del animo bueno
bool animo_bueno(int puntos_animo){
	return((puntos_animo >= PUNTOS_MIN_ANIMO_BUENO)&&(puntos_animo <= PUNTOS_MAX_ANIMO_BUENO));
}
//Pre: Recibe un puntaje entre 0 y 50
//Post: Devuelve true si el puntaje esta en rango del puntaje del animo regular
bool animo_regular(int puntos_animo){
	return((puntos_animo >= PUNTOS_MIN_ANIMO_REGULAR)&&(puntos_animo <= PUNTOS_MAX_ANIMO_REGULAR));
}
//Pre: El puntaje del animo de un personaje(entre 0 y 50)
//Post: Devuelve el animo que corresponde al puntaje
char que_animo_tiene(int puntos_animo){
	if(animo_bueno(puntos_animo)){
		return ANIMO_BUENO;
	}else if(animo_regular(puntos_animo)){
		return ANIMO_REGULAR;
	}else{
		return ANIMO_MALO;
	}
}


void animos(int* viento,int* humedad,char* animo_legolas,char* animo_gimli){

	int dia_mes;
	char hora_dia;
	int puntos_animo_legolas = 0, puntos_animo_gimli = 0;
	char pie_levanto_legolas, pie_levanto_gimli;
	char cena_legolas, cena_gimli;
	int horas_dormidas_legolas, horas_dormidas_gimli;

	printf("\n############################################################################################");
	printf("\n#                                                                                          #");
	printf("\n#  Continuaremos a hacerle preguntas para determinar las condiciones del campo de batalla  #");
	printf("\n#                                                                                          #");
	printf("\n############################################################################################");
	determinar_dia_mes(&dia_mes);
	*viento = velocidad_viento(dia_mes);
	determinar_hora_dia(&hora_dia);
	*humedad = porcentaje_humedad(hora_dia);
	system("clear");

	printf("\n#########################################################");
	printf("\n#                                                       #");
	printf("\n#     Ahora vamos a determinar el animo de Legolas!     #");
	printf("\n#                                                       #");
	printf("\n#########################################################");
	preguntas_determinar_animo(&pie_levanto_legolas,&cena_legolas,&horas_dormidas_legolas);
	puntos_animo_legolas += puntaje_animo(pie_levanto_legolas,cena_legolas,horas_dormidas_legolas);
	*animo_legolas = que_animo_tiene(puntos_animo_legolas);
	system("clear");

	printf("\n#######################################################");
	printf("\n#                                                     #");
	printf("\n#     Ahora vamos a determinar el animo de Gimli!     #");
	printf("\n#                                                     #");
	printf("\n#######################################################");
	preguntas_determinar_animo(&pie_levanto_gimli,&cena_gimli,&horas_dormidas_gimli);
	puntos_animo_gimli += puntaje_animo(pie_levanto_gimli,cena_gimli,horas_dormidas_gimli);
	*animo_gimli = que_animo_tiene(puntos_animo_gimli);
	system("clear");

	printf("\nResumen: %i %i %c %c.\n",*viento,*humedad,*animo_legolas,*animo_gimli);
} 