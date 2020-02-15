#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <unistd.h>


bool leer_numero(FILE* archivo, int16_t* num, long seek_lectura){
	fseek(archivo, seek_lectura, SEEK_SET);
	return fread(num, 2, 1, archivo) > 0;
}

void escribir_numero(FILE* archivo, int16_t* num, long seek_escritura){
	fseek(archivo, seek_escritura, SEEK_SET);
	fwrite(num, 2, 1, archivo);
}

bool es_multiplo3(int16_t num){
	return (ntohs(num) % 3) == 0;
}

long procesar_archivo(FILE* archivo){
	long seek_escritura = 0;
	long seek_lectura = 0;
	int16_t numero;

	while (leer_numero(archivo, &numero, seek_lectura)){
		seek_lectura += 2;
		if (!es_multiplo3(numero)){
			escribir_numero(archivo, &numero, seek_escritura);
			seek_escritura += 2;
		}else{
			printf("Es multiplo el numero: %i\n", ntohs(numero));
		}
	}
	return seek_escritura;
}

void escribir_archivo(const char* nombre){
	FILE* archivo = fopen(nombre, "w");
	for (short i = 256; i < 300; i ++){
		short aux = htons(i);
		printf("Escribo el numero, %i como %i\n", i , aux);
		fwrite(&aux, 2, 1, archivo);
	}
	fclose(archivo);
}

int main(int argc, char const *argv[]){
	if (argc != 2){
		fprintf(stderr, "Cant de arg erronea\n" );
		return 1;
	}
	escribir_archivo(argv[1]);
	FILE* archivo = fopen(argv[1], "r+");
	long tam_fin = procesar_archivo(archivo);
	fclose(archivo);
	truncate(argv[1], tam_fin);
	return 0;
}


