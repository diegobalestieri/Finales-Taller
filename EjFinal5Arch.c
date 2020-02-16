#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 #include <arpa/inet.h>

bool leer_linea(FILE* arch, int16_t* numero, long seek_lectura){
	fseek(arch, seek_lectura, SEEK_SET);
	return (fread(numero, 2, 1, arch) == 1);
}

bool tengo_duplicar(int16_t numero){
	return ((numero-1)%5 == 0);
}

void swap(FILE* arch, long pos1, long pos2){
	int16_t numero1, numero2;
	leer_linea(arch, &numero1, pos1);
	leer_linea(arch, &numero2, pos2);
	fseek(arch, pos1, SEEK_SET);
	fwrite(&numero2, 2, 1, arch);
	fseek(arch, pos2, SEEK_SET);
	fwrite(&numero1, 2, 1, arch);
}

void escribir_linea(FILE* arch, int16_t* numero, long seek_lectura){
	long inicio = ftell(arch); //Porque esta en la posicion luego de leer el que tengo que duplicar
	
	fseek(arch, 0, SEEK_END);
	long final = ftell(arch);
	fwrite(numero, 2, 1, arch);
	long pos = final;
	for(int i = 0; i < (final-inicio)/2; ++i){
		swap(arch, pos, pos-2);
		pos -= 2;
	}
}

void duplicar_lineas(FILE* arch){
	long seek_lectura = 0;
	int16_t numero;
	while(leer_linea(arch, &numero, seek_lectura)){
		seek_lectura += 2;
		if(tengo_duplicar(numero)){
			escribir_linea(arch, &numero, seek_lectura);
			seek_lectura += 2;
		}
	}
}

void crear_arch(const char* nombre){
	FILE* arch = fopen(nombre, "wb");
	for(int16_t i = 0; i < 17; ++i){
		int16_t aux = htons(i);
		if(i == 6){
			fwrite(&aux, 2, 1, arch);
		}
		fwrite(&aux, 2, 1, arch);
	}
	fclose(arch);
}

int main(int argc, char const *argv[]){
	if(argc != 2){
		fprintf(stderr, "Falta el archivo\n");
		return -1;
	}
	crear_arch(argv[1]);
	FILE* arch = fopen(argv[1], "rb+");
	if(arch == NULL){
		fprintf(stderr, "El archivo no existe\n");
		return -1;
	}
	duplicar_lineas(arch);
	fclose(arch);
	return 0;
}