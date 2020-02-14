#include <stdio.h>
int main(int argc, char const *argv[]){
	
	short* Pi = 1000;
	Pi++;
	printf("Pi apunta a la direccion: %li\n", (long)Pi);
	return 0;
}