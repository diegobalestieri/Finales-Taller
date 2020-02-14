#include <stdio.h>
#include <stdlib.h>

void funca(const char* d[]){
	d = NULL;
}
int main(int argc, char const *argv[]){
	char cad[3];
	cad[0] = 'H';
	cad[1] = 'H';
	cad[2] = '\0';

/*	const char* a = cad;
	char const * b = cad;
	char * const c  = cad;

	//Pruebo si el contenido del puntero es constante 
	a[1] = 'B';
	b[1] = 'B';
	c[1] = 'B';

	//Pruebo si el puntero es constante;
	a = NULL;
	b = NULL;
	c = NULL;
*/
	/*
	'const char *a'  y 'char const *b' son equivalentes: un puntero a caracteres constantes. [es un string que no puedo modificar]
	'char* const c' es un puntero constante a un string. (el string lo puedo modificar pero el puntero no, siempre apunta ahí.)
	*/
	const char* aux[2];
	aux[0] = cad;
	aux[1] = cad;
	//aux[0][0] = 'B';
	//'const char* aux[2];' y 'char const *e[2];' es un array de cadenas constantes. Puedo modificar valores del array (aux[0] = algo) pero no los valores
	// de las cadenas de adentro (aux[0][0] != 'B')

	char* const f[2];
	f[0] = cad;
	f[0][0] = 'B';

	//Pruebo si el puntero es constante
	funca(aux);
	//e = NULL;
	//f = NULL;

	return 0;
}