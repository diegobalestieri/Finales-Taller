#include <stdio.h>
#define ASSERT(condicion) if(!(condicion)) printf("ERROOR\n");

#define ASSERT_2LINEAS(condicion) if(!(condicion)) \
	printf("ERROR DE 2DO ASSERT\n");


#define ASSERT_2PARAMETROS(condicion, mensaje)  if(!(condicion)){\
	printf("Assert error on %s.%d: %s\n",__FILE__, __LINE__, (mensaje));\
}
int main(int argc, char const *argv[]){
	int a = 3;
	int b = 4;
	ASSERT(a == b);
	ASSERT_2LINEAS(a == b);
	ASSERT_2PARAMETROS(a == b, "Error en el assert de 2 parametros yeey");
	return 0;
}
