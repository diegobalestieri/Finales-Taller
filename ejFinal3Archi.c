#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define LONG_MAX 1024

bool leer_linea(FILE* archivo, char* linea){
	return fgets(linea, LONG_MAX, archivo) != NULL;
}

void swapear_palabras(FILE* archivo, char* palabra1, char* palabra2){
	int long1 = strlen(palabra1);
	int long2 = strlen(palabra2);
	fseek(archivo, -(long1 + long2), SEEK_CUR); //SEEK_CUR
	fwrite(palabra2, long2, 1, archivo);
	fwrite(palabra1, long1, 1, archivo);
}

void procesar_archivo(FILE* archivo){
	bool ordenado = false;
	bool eof = false;
	while(!ordenado){
		rewind(archivo);
		eof = false;
		ordenado = true;
		while(!eof){
			char palabra1[LONG_MAX];
			char palabra2[LONG_MAX];
			if (!leer_linea(archivo, palabra1) || !leer_linea(archivo, palabra2)){
				eof = true;
				break;
			} else if (strcmp(palabra1, palabra2) > 0){
				swapear_palabras(archivo, palabra1, palabra2);
				fseek(archivo, -strlen(palabra1), SEEK_CUR);
				ordenado = false;
			}else{
				fseek(archivo, -strlen(palabra2), SEEK_CUR);
			}
		}
	}
}


int main(int argc, char const *argv[]){
	if (argc != 2){
		fprintf(stderr, "La cantidad de agrgumentos es erronea\n" );
		return 1;
	}
	const char* archivo = argv[1];
	FILE* arch = fopen(archivo, "r+");
	if(arch == NULL){
		fprintf(stderr, "No se pudo abrir el archivo\n");
		return 1;
	}
	procesar_archivo(arch);
	fclose(arch);
	return 0;
}