#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define TAM_WORD 2

bool leer_word(FILE* archivo, char* buffer, long seek_lectura){
	fseek(archivo, seek_lectura, SEEK_SET);
	char c = '\0';
	for (int i = 0; i < TAM_WORD; i++){
		c = fgetc(archivo);
		if (c == EOF){
			return false;
		}
		buffer[i] = c;
	}
	return true;
}

void escribir_word(FILE* archivo, char* buffer, long seek_escritura){
	fseek(archivo, seek_escritura, SEEK_SET);
	fwrite(buffer, TAM_WORD, sizeof(char), archivo);
}

bool es_multiplo_16(char* buffer){
	buffer[TAM_WORD] = '\0';
	int num = atoi(buffer);
	return num % 16 == 0;
}
long procesar_archivo(FILE* archivo){
	long seek_lectura = 0;
	long seek_escritura = 0;
	char buffer[TAM_WORD+1];
	while (leer_word(archivo, buffer, seek_lectura)){
		seek_lectura += TAM_WORD;
		if (!es_multiplo_16(buffer)){
			escribir_word(archivo, buffer, seek_escritura);
			seek_escritura += TAM_WORD;
		}
	}
	return seek_escritura;
}

int main(int argc, char const *argv[]){
	if (argc != 2){
		printf("Parametros erroneos\n");
		return 1;
	}
	const char* archivo = argv[1];
	FILE* arch = fopen(archivo, "r+");
	if (arch == NULL){
		fprintf(stderr, "Archivo inexistente\n" );
		return 1;
	}
	long pos_fin = procesar_archivo(arch);
	fclose(arch);
	truncate(archivo, pos_fin * sizeof(char));
	return 0;
}