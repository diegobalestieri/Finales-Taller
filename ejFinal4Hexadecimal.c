#include <stdio.h>
#include <string.h>
int elevar_a(int num, int exp){
	int res = 1;
	if (exp == 0){
		return res;
	}
	for (int i = 0; i<exp; i++){
		res *= num;
	}
	return res;
}
void valorHexadecimal(char* cadena, int* res){
	int largo = strlen(cadena);
	*res = 0;
	for (int i = 0; i < largo; i++){
		if (cadena[i] >= '0' && cadena[i] <= '9'){
			*res += elevar_a(16,(largo-i-1)) * (cadena[i]-'0');
		} else if (cadena[i] >= 'A' && cadena[i] <= 'F'){
			*res += elevar_a(16,(largo-i-1)) * (cadena[i]-'A'+10);
		}
	}
}

int main(int argc, char const *argv[]){
	int res = 0;
	char* cadena = "3AF";
	valorHexadecimal(cadena, &res);
	printf("El valor convertido es: %d\n", res);
	return 0;
}