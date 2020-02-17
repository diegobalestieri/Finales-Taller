#include <stdio.h>
#include <string.h>
#define TAM_MAX 1024

void duplicar_ocurrencias(char* resultado, const char* cad1, const char* cad2){
	int pos_res = 0;
	int pos_cad1 = 0;

	int largo_cad2 = strlen(cad2);
	char* ptr_aparicion = strstr(&cad1[pos_cad1], cad2);
	while (ptr_aparicion != NULL){
		//Copio en resultado la cad1 hasta la primera aparicion
		for (int i = pos_cad1; i < pos_cad1 + (ptr_aparicion - &cad1[pos_cad1]); ++i){
			resultado[pos_res] = cad1[pos_cad1];
			++pos_cad1;
			++pos_res;
		}
		//Copio las dos ocurrencias de la cad2 en resultado
		strcpy(&resultado[pos_res], cad2);
		strcpy(&resultado[pos_res + largo_cad2], cad2);
		pos_res += 2*largo_cad2;
		pos_cad1 += largo_cad2;
		ptr_aparicion = strstr(&cad1[pos_cad1], cad2);
	}
	//Escribo los caracteres restantes desde la ultima aparicion de cad2
	for (int i = pos_cad1; pos_cad1 <= strlen(cad1); ++i){ //Es hasta el = para que copie el '\0'
		resultado[pos_res] = cad1[pos_cad1];
		++pos_res;
		++pos_cad1;
	}
}

int main(int argc, char const *argv[]){
	if (argc != 3){
		fprintf(stderr, "Cantidad de argumentos erronea\n");
		return 1;
	}
	if (strlen(argv[1]) == 0 || strlen(argv[2]) == 0){
		printf("%s\n", argv[1]);
		return 0;
	}
	char resultado[TAM_MAX];
	duplicar_ocurrencias(resultado, argv[1], argv[2]);
	printf("%s\n", resultado);
	return 0;
}