#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

bool leer(FILE* arch, char* buffer, int posLectura, int cantLeer){
	fseek(arch, posLectura, SEEK_SET);
	return fgets(buffer, cantLeer+1, arch) != NULL;
}

int potencia(int numero, int potencia){
	int res = 1;
	for(int i = 0; i < potencia; ++i){
		res *= numero;
	}
	return res;
}

int transformar(char* hexa){
	int decimal = 0;
	int largo = strlen(hexa);
	for(int i = 0; i < largo; ++i){
		if(hexa[i] >= 'A' && hexa[i] <= 'F'){
			decimal += (hexa[i] - 'A' + 10)*potencia(16, largo-i-1);
		} else {
			decimal += (hexa[i]-'0')*potencia(16, largo-i-1);
		}
	}
	printf("Transforme: %s en %i\n", hexa, decimal);
	return decimal;
}

void escribirLinea(FILE* arch, char* buffer, int pos){
	//printf("Escribo: %s\n", buffer);
	fseek(arch, pos, SEEK_SET);
	fwrite(buffer, strlen(buffer), 1, arch);
}

void swapAnterior(FILE* arch, int pos, int longEste, int longAnterior){
	char num1[longEste+1];
	char num2[longAnterior+1];
	leer(arch, num1, pos, longEste);
	leer(arch, num2, pos-longAnterior, longAnterior);
	printf("Swapeo: %s con %s\n", num1, num2);
	escribirLinea(arch, num1, pos-longAnterior);
	escribirLinea(arch, num2, pos-longAnterior+longEste);
}

int escribir(FILE* arch, int decimal, int* fin){
	int inicio = ftell(arch)-4;
	char aux[1024];
	sprintf(aux, "%d", decimal);
	int largo = strlen(aux);
	escribirLinea(arch, aux, *fin);
	for(int pos = *fin; pos > inicio; pos -= 4){
		swapAnterior(arch, pos, largo, 4);
	}
	*fin += largo-4;
	for(int pos = inicio+largo; pos <= *fin; pos += 4){
		swapAnterior(arch, pos+4, 4, 4);
	}
	return largo;
}

void crearArch(const char* nombre){
	FILE* arch = fopen(nombre, "w");
	char* buf = "000FF000000A0001";
	fwrite(buf, strlen(buf), 1, arch);
	fclose(arch);
}

int main(int argc, char const* argv[]){
	if(argc != 2){
		printf("La cague\n");
		return -1;
	}
	crearArch(argv[1]);
	FILE* arch = fopen(argv[1], "r+");
	if(arch == NULL){
		printf("La cague\n");
		return -1;
	}
	int posLectura = 0;
	fseek(arch, 0, SEEK_END);
	int fin = ftell(arch);
	char buffer[5];
	while(posLectura < fin){
		if(!leer(arch, buffer, posLectura, 4)){
			break;
		}
		int decimal = transformar(buffer);
		posLectura += escribir(arch, decimal, &fin);
	}
	fclose(arch);
	truncate(argv[1], fin);
	return 0;
}