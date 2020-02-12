#include <stdlib.h>
#include <stdio.h>

void fa(){
	static int a = 0;
	a++;
	printf("A: %i\n",a );
}
int main(int argc, char const *argv[]){
	for(int i = 0; i < 10; i++){
		fa();
	}
/*	int * puntero_a = fa();
	int * puntero_b = fb();
	if (puntero_a == puntero_b){
		printf("Son iguales\n");
	}else{
		printf("Son distitos\n");
	}*/
	return 0;
}