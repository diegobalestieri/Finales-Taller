#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 1024

void duplicar_palabra(char* palabra, char* cadena){
	int posEscritura = -1;
	int j = 0;
	for (int i = 0; i < strlen(cadena); ++i){
		if(j >= strlen(palabra)){
			posEscritura = i;
			break;
		} else if(cadena[i] == palabra[j]){
			++j;
		} else {
			j = 0;
		}
	}
	if(posEscritura == -1) return;
	char aux[TAM];
	memcpy(aux, &cadena[posEscritura], TAM);
	cadena[posEscritura] = ' ';
	++posEscritura;
	for(int i = 0; i < strlen(palabra); ++i){
		cadena[posEscritura] = palabra[i];
		++posEscritura;
	}
	memcpy(&cadena[posEscritura], aux, TAM-posEscritura);
}

int main(int argc, char const* argv[]){
	char buffer1[TAM];
	char buffer2[TAM];
	printf("Ingrese una cadena:\n");
	fgets(buffer1, TAM, stdin);
	printf("Ingrese otra cadena:\n");
	fgets(buffer2, TAM, stdin);
	
	char aux[TAM];
	memset(aux, '\0', TAM);
	int i = 0;
	int largo = strlen(buffer2);
	for(int j = 0; j < (largo-1); ++j){ //resto 1 por el \n
		if(buffer2[j] == ' '){
			duplicar_palabra(aux, buffer1);
			memset(aux, '\0', TAM);
			i = 0;
		} else {
			aux[i] = buffer2[j];
			++i;
		}
	}
	duplicar_palabra(aux, buffer1);
	printf("Resultado: %s", buffer1);
	return 0;
}