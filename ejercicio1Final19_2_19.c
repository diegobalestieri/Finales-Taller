/*
Escriba una función ISO C llamada Replicar que reciba una cadena (S), dos índices (I1 e I2) y una
cantidad (Q). La función debe retornar una copia de S salvo los carácteres que se encuentren entre los
índices I1 e I2 que serán duplicados Q veces.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*
void replicar_caracter(char* cadena, char c, int cantidad){
	for (int i = 0; i < cantidad; i++){
		cadena[i] = c;
	}
}

char * replicar(char* cadena, int i1, int i2, int cantidad){
	int longitud = strlen(cadena);
	//Chequeos (no se si son necesarios)
	if (i1 > i2 || i1 < 0 || i2 > longitud-1){
		printf("Indices invalidos\n");
		return cadena;
	}
	char * resultado = malloc(sizeof(char) * (longitud + cantidad * (i2 - i1)));

	int pos_res = 0;
	for (int j = 0; j < longitud; j++){
		if (j >= i1 && j <= i2){
			replicar_caracter(&resultado[pos_res], cadena[j], cantidad);
			pos_res = pos_res + cantidad;
		} else {
			resultado[pos_res] = cadena[j];
			pos_res ++;
		}
	}
	return resultado;
}
*/
void copiar_buffer(char* cadena, char* buffer, int cantidad){
	int pos_inicial = 0;
	for (int i = 0; i < cantidad; i++){
		for (int j = 0; j < strlen(buffer); j++){
			cadena[pos_inicial + j] = buffer[j];
		}
		pos_inicial = pos_inicial + strlen(buffer);
	}
}
char* replicar(char* cadena, int i1, int i2, int cantidad){
	int longitud = strlen(cadena);
	//Chequeos (no se si son necesarios)
	if (i1 > i2 || i1 < 0 || i2 > longitud-1){
		printf("Indices invalidos\n");
		return cadena;
	}
	char * resultado = malloc(sizeof(char) * (longitud + cantidad * (i2 - i1)));


	char buffer[i2 - i1];
	int pos_res = 0;
	for (int j = 0; j < longitud; j++){
		if (j >= i1 && j <= i2){
			buffer[j - i1] = cadena[j];
		}
		if (j == i2){
			copiar_buffer(&resultado[j], buffer, cantidad);
			pos_res = pos_res + cantidad*(i2 - i1);
		}
		resultado[pos_res] = cadena[j];
		pos_res++;
		resultado[pos_res+1] = '\0';
		printf("Iteracion con j = %d, %s\n",j, resultado );
	}
	return resultado;
}

/*
Escribir un programa ISO C que reciba por argumento el nombre de un archivo de texto y 
lo procese sobre sí mismo (sin crear archivos intermedios ni subiendo todo su contenido a memoria).
 El procesamiento consiste en eliminar todas las líneas de 1 sola palabra
*/
#define TAM_MAX 1024
int contar_palabras(char* cadena){
	//Asumo que todas las palabras están separadas por espacios y que son oraciones que tienen
	//un espacio luego del punto. Así como que ninguna de las oraciones esta vacía con espacios.
	int contador = 0;
	for (int i = 0; i < strlen(cadena); i++){
		if (cadena[i] == ' '){
			contador++;
		}
	}
	return contador;
}

void escribir_linea(FILE* archivo, char* buffer, size_t seek_escritura){
	fseek(archivo, seek_escritura, SEEK_SET);
	for (int i = 0; i < strlen(buffer); i++){
		//Podria hacerse con fWrite
		fputc(buffer[i], archivo);
	}
}
int leer_linea(FILE* archivo, char* buffer, char delim){
	int contador = 0;
	char c = fgetc(archivo);
	while (c != EOF){
		buffer[contador] = c;
		contador++;
		c = fgetc(archivo);
	}
	return contador;
}
void eliminar_lineas_1_palabra(FILE* archivo){
	size_t seek_lectura = 0;
	size_t seek_escritura = 0;

	char buffer[TAM_MAX];
	int leidos = 0;
	while (!feof(archivo)){
		int pos_buffer = 0;
		leidos = leer_linea(archivo, buffer, '\n');
		if (leidos == 0){
			break;
		}
		seek_lectura += leidos;
		buffer[pos_buffer+1] = '\0';
		int cant_palabras = contar_palabras(buffer);
		if (cant_palabras != 1){
			escribir_linea(archivo, buffer, seek_escritura);
			seek_escritura += leidos;
		}
	}
}

int main(int argc, char const *argv[]){
	//char* res = replicar("HOLA", 1, 2, 3);
	//printf("%s\n", res);
	//free(res);

	const char* archivo = argv[1];
	FILE* arch = fopen(archivo, "r+");
	if (arch == NULL){
		fprintf(stderr, "El archivo no se pudo abrir\n");
		return 1;
	}
	eliminar_lineas_1_palabra(arch);
	return 0;
}