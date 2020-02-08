#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char const *argv[]) {
	if(argc != 5){
		fprintf(stderr, "Error en los parametros ingresados\n");
		return -1;
	}
	replicar(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
	return 0;
}