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
#define TAM_MAX 10

int crear_socket(const char* ip, const char* puerto){
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; //IPv4
	hints.ai_socktype = SOCK_STREAM; //TCP
	hints.ai_flags = AI_PASSIVE; //servidor
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
		if(sfd == -1){continue;}
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

bool recibir_mensaje(char* buffer, int sfd){
	memset(buffer, '\0', TAM_MAX*sizeof(char));
	char aux = '\0';
	while(aux != '<'){
		if(recv(sfd, &aux, 1, 0) <= 0){
			return false;
		}
	}
	int i = 0;
	if(recv(sfd, &aux, 1, 0) <= 0){
		return false;
	}
	while(aux != '>'){
		if(i >= TAM_MAX){
			i = 0;
			fprintf(stderr, "Mensaje demasiado largo\n");
		}
		buffer[i] = aux;
		i++;
		if(recv(sfd, &aux, 1, 0) <= 0){
			return -1;
		}		
	}
	return true;
}

int main(int argc, char const *argv[]) {
	if(argc != 3){
		fprintf(stderr, "Cantidad de parametros incorrecta\n");
		return -1;
	}
	int sfd = crear_socket(argv[1], argv[2]);
	if(sfd == -1){
		return -1;
	}
	int cfd = conectar_cliente(sfd);
	if(cfd == -1){
		shutdown(sfd, SHUT_RDWR);
		close(sfd);
		return -1;
	}
	char mensaje[TAM_MAX];
	while(recibir_mensaje(mensaje, cfd)){
		if(strlen(mensaje) > 0){
			printf("Mensaje recibido: %s\n", mensaje);
		} else {
			break;
		}
	}
	shutdown(cfd, SHUT_RDWR);
	shutdown(sfd, SHUT_RDWR);
	close(cfd);
	close(sfd);
	return 0;
}