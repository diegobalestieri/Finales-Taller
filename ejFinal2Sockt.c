#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdbool.h>
#include <errno.h>
#define TAM_COLA 1
#define TAM_MAX 1024
#define LARGO_MAX_NUM 10

int crear_socket(const char* ip, const char* puerto) {
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; //IPv4
	hints.ai_socktype = SOCK_STREAM; //TCP
	hints.ai_flags = AI_PASSIVE; //Servidor
	struct addrinfo* ptr;
	int e = getaddrinfo(ip, puerto, &hints, &ptr);
	if(e != 0){
		fprintf(stderr, "Getaddrinfo: %s\n", gai_strerror(e));
        return -1;
	}
	struct addrinfo* res = NULL;
	int sfd;
	for(res = ptr; res != NULL; res = res->ai_next){
		sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(sfd == -1) {continue;}
		if(bind(sfd, res->ai_addr, res->ai_addrlen) == 0){break;}
		close(sfd);
	}
	if(res == NULL){
		fprintf(stderr, "Bind: %s\n", strerror(errno));
		return -1;
	}
	freeaddrinfo(ptr);
	return sfd;
}

int conectar_cliente(int sfd){
	if(listen(sfd, TAM_COLA) == -1){
		fprintf(stderr, "Listen: %s\n", strerror(errno));
		return -1;
	}
	int cfd = accept(sfd, NULL, NULL);
	if(cfd == -1){
		fprintf(stderr, "Accept: %s\n", strerror(errno));
		return -1;	
	}
	return cfd;
}

int recibir_mensaje(int cfd, char* buffer){
	memset(buffer, '\0', sizeof(char)*TAM_MAX);
	int i = 0;
	while(recv(cfd, &buffer[i], 1, 0) > 0){
		if(strcmp(buffer, "FIN\n") == 0){ //el \n esta por el netcat
			return -1;
		}
		if(i >= TAM_MAX-1){
			fprintf(stderr, "El mensaje es demasiado largo\n");
			return -1;
		}
		if(buffer[i] == '='){
			i++;
			recv(cfd, &buffer[i], 1, 0); //recibo el \n del netcat
			return 0;
		}
		i++;
	}
	return -1;
}

void sumar_numeros(char* buffer){
	int resultado = 0;
	char aux[LARGO_MAX_NUM];
	memset(&aux, '\0', sizeof(char)*LARGO_MAX_NUM);
	int cont = 0;
	for(int i = 0; i < strlen(buffer); ++i){
		if(buffer[i] == '='){
			resultado += atoi(aux);
			break;
		}
		if(buffer[i] == ','){
			resultado += atoi(aux);
			cont = 0;
			memset(&aux, '\0', sizeof(char)*LARGO_MAX_NUM);
		} else {
			aux[cont] = buffer[i];
			cont++;
		}
		if(cont > LARGO_MAX_NUM){
			fprintf(stderr, "Numero demasiado largo\n");
			return;
		}
	}
	printf("Resultado = %i\n", resultado);
}

void ejecutar_programa(int cfd){
	char buffer[TAM_MAX];
	while(recibir_mensaje(cfd, buffer) == 0){
		sumar_numeros(buffer);
	}
}

int main(int argc, char const *argv[]) {
	if(argc != 3){
		printf("falta el puerto y la ip\n");
		return -1;
	}
	int sfd = crear_socket(argv[1], argv[2]);
	if(sfd == -1){
		return -1;
	}
	int cfd = conectar_cliente(sfd);
	if(cfd == -1){
		return -1;
	}
	ejecutar_programa(cfd);
	shutdown(sfd, SHUT_RDWR);
	shutdown(cfd, SHUT_RDWR);
	close(sfd);
	close(cfd);
	return 0;
}