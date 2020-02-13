#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
void replicar(const char* palabra, int posInicio, int posFinal, int cantRepeticiones) {
	size_t largoOriginal = strlen(palabra);
	printf("%s - %i - %i - %i\n", palabra, posInicio, posFinal, cantRepeticiones);
	if(posInicio >= posFinal || posFinal < 0 || posInicio < 0 || cantRepeticiones <= 0 || posInicio >= largoOriginal || posFinal >= largoOriginal){
		fprintf(stderr, "Error en los parametros ingresados\n");
		return;
	}
	size_t largoFinal = largoOriginal + (posFinal - posInicio + 1)*(cantRepeticiones-1) + 1;
	char palabraFinal[largoFinal];
	for(size_t i = 0; i <= posFinal; ++i){
		palabraFinal[i] = palabra[i];
	}
	size_t aux = posFinal+1;
	while(cantRepeticiones-1 > 0){
		for(size_t i = posInicio; i <= posFinal; ++i){
			palabraFinal[aux] = palabra[i];
			aux++;
		}
		cantRepeticiones--;
	}
	for (int i = posFinal+1; i < largoOriginal; ++i){
		palabraFinal[aux] = palabra[i];
		aux++;
	}
	palabraFinal[largoFinal-1] = '\0';
	printf("La cadena final es: %s\n", palabraFinal);
}
*/

char* replicar(const char* palabra, int i1, int i2, int cantRepeticiones) {
	if(palabra == NULL || i1 >= i2 || cantRepeticiones < 0){return NULL;}
	size_t lenOrg = strlen(palabra);
	if(lenOrg <= 0 || i2 >= lenOrg){return NULL;}
	size_t tam = lenOrg+(i2-i1+1)*(cantRepeticiones-1);
	char* nuevo = malloc(sizeof(char)*tam);
	for(int i = 0; i < i1; ++i){
		nuevo[i] = palabra[i];
	}
	int pos = i1;
	for(int i = 0; i < cantRepeticiones; ++i){
		for(int j = i1; j <= i2; ++j){
			nuevo[pos] = palabra[j];
			++pos;
		}
	}
	for(int i = i2+1; i < lenOrg; ++i){
		nuevo[pos] = palabra[i];
		++pos;
	}
	return nuevo;
}

int main(int argc, char const *argv[]) {
	if(argc != 5){
		fprintf(stderr, "Error en los parametros ingresados\n");
		return -1;
	}
	char* aux = replicar(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
	if(aux == NULL){
		printf("Es null\n");
	} else {
		printf("%s\n", aux);
	}
	free(aux);
	return 0;
}