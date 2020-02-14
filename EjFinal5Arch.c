#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool leer_linea(FILE* arch, int16_t* numero){
	return (fread(numero, 2, 1, arch) == 1);
}

bool tengo_duplicar(int16_t numero){
	return ((numero-1)%5 == 0);
}

void swap(FILE* arch, long pos1, long pos2){
	int16_t numero1, numero2;
	fseek(arch, pos1, SEEK_SET);
	fread(&numero1, 2, 1, arch);
	fseek(arch, pos2, SEEK_SET);
	fread(&numero2, 2, 1, arch);
	fseek(arch, pos1, SEEK_SET);
	fwrite(&numero2, 2, 1, arch);
	fseek(arch, pos2, SEEK_SET);
	fwrite(&numero1, 2, 1, arch);
}

void escribir_linea(FILE* arch, int16_t* numero){
	long posActual = ftell(arch);
	fseek(arch, 0, SEEK_END);
	fwrite(numero, 2, 1, arch);
	long final = ftell(arch)-2;
	long pos1 = final;
	long pos2 = final-2;
	for(int i = 0; i < (final-posActual)/2; ++i){
		swap(arch, pos1, pos2);
		pos2 -= 2;
		pos1 -= 2;
	}
}

void duplicar_lineas(FILE* arch){
	int16_t numero;
	while(leer_linea(arch, &numero)){
		if(tengo_duplicar(numero)){
			escribir_linea(arch, &numero);
		}
	}
}

void crear_arch(const char* nombre){
	FILE* arch = fopen(nombre, "w");
	for(int16_t i = 0; i < 17; ++i){
		if(i == 6){
			fwrite(&i, 2, 1, arch);
		}
		fwrite(&i, 2, 1, arch);
	}
	fclose(arch);
}

int main(int argc, char const *argv[]){
	if(argc != 2){
		fprintf(stderr, "Falta el archivo\n");
		return -1;
	}
	crear_arch(argv[1]);
	FILE* arch = fopen(argv[1], "r+");
	if(arch == NULL){
		fprintf(stderr, "El archivo no existe\n");
		return -1;
	}
	duplicar_lineas(arch);
	fclose(arch);
	return 0;
}