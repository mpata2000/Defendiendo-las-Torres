#include "comandos.h"

#define NO_EXISTE_ARCHIVO -1
#define EXISTE_ARCHIVO 0

void parse_comando(int argc, char* argv[],comando_t comando[MAX_COMANDOS], size_t* num_comando){
	char * tok = NULL;
	
	for(int i = 0; i<argc; i++){
		if(strstr(argv[i], "=")){
			tok = strtok(argv[i], "=");
			strcpy(comando[*num_comando].key, tok);

			tok = strtok(NULL, "=");
			strcpy(comando[*num_comando].valor, tok);
			
			(*num_comando)++;
		}
	}
}


void sacar_extension_archivo(char nombre_archivo[MAX_NOMBRE_COMANDO]){
	char * tok = NULL;

	if(strstr(nombre_archivo, ".")){	
		tok = strtok(nombre_archivo, ".");
		strcpy(nombre_archivo, tok);
	}
}


void comandos_defendiendo_torres(configuracion_t* config, comando_t comandos[MAX_COMANDOS],size_t num_comando,rutas_t* rutas){
	strcpy(rutas->ruta_config, "DEFAULT");
	strcpy(rutas->ruta_ranking, "DEFAULT");
	rutas->hay_grabacion = false;

	
	for(int i=0;i<num_comando;i++){
		if(strcmp(comandos[i].key,"config") == 0){
			strcpy(rutas->ruta_config,comandos[i].valor);
			sacar_extension_archivo(rutas->ruta_config);
			strcpy(rutas->ruta_ranking,rutas->ruta_config);
			if(leer_configuracion(config,rutas->ruta_config) == NO_EXISTE_ARCHIVO){
				strcpy(rutas->ruta_ranking, "DEFAULT");
			}		
		}else if(strcmp(comandos[i].key,"grabacion") == 0){
			strcpy(rutas->ruta_grabacion,comandos[i].valor);
			sacar_extension_archivo(rutas->ruta_grabacion);

			strcat(rutas->ruta_grabacion,".dat");
			rutas->hay_grabacion = true;
		}else if(strcmp(comandos[i].key,"listar") == 0){
			config->listar = atoi(comandos[i].valor);
		}else if(strcmp(comandos[i].key,"velocidad") == 0){
			config->velocidad = (float)atof(comandos[i].valor);
		}
	}
	
}





int comandos_simples(int argc, char* argv[],char nombre_archivo[MAX_NOMBRE_COMANDO]){
	if(argc < 3){
		printf("Se ingresaron comandos de menos!");
		return COMANDO_NO_FUNCIONO;
	}else if(argc > 3){
		printf("Se ingresaron comandos de mas!");
		return COMANDO_NO_FUNCIONO;
	}
	strcpy(nombre_archivo,argv[2]);
	sacar_extension_archivo(nombre_archivo);
	
	return COMANDO_FUNCIONO;
}
