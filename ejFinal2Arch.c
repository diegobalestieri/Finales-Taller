#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#define TAM_MAX 1024

bool tiene_una_palabra(char* linea){
	int espacios = 0;
	for (int i = 0; i < strlen(linea); ++i) {
		if(linea[i] == ' '){
			espacios++;
		}
		if(espacios >= 1){
			return false;
		}
	}
	return true;
}

bool leer_linea(char* linea, FILE* arch, long int* posLeer){
	fseek(arch, *posLeer, SEEK_SET);
	return fgets(linea, TAM_MAX, arch) != NULL;
}

void escribir_linea(char* linea, FILE* arch, long int* posEscribir){
	printf("%s\n", linea);
	fseek(arch, *posEscribir, SEEK_SET);
	fwrite(linea, sizeof(char), strlen(linea), arch);
	*posEscribir += strlen(linea);
}

int main(int argc, char const *argv[]) {
	if(argc != 2){
		fprintf(stderr, "Error en parametros\n");
		return -1;
	}
	FILE* arch = fopen(argv[1], "r+");
	if(!arch){
		fprintf(stderr, "No se pudo abrir el archivo\n");
		return -1;
	}
	long int posEscribir = 0;
	long int posLeer = 0;
	char linea[TAM_MAX];
	while(leer_linea(linea, arch, &posLeer)){
		posLeer += strlen(linea);
		if(!tiene_una_palabra(linea)){
			escribir_linea(linea, arch, &posEscribir);
		}
	}
	fclose(arch);
	truncate(argv[1] , sizeof(char) * posEscribir);
	return 0;
}