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
#define TAM_MAX 5

int crear_servidor(const char* ip, const char* puerto){
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; //IPv4
	hints.ai_socktype = SOCK_STREAM; //TCP
	hints.ai_flags = AI_PASSIVE; //Servidor
	struct addrinfo* ptr;
	if(getaddrinfo(ip, puerto, &hints, &ptr) < 0){
		fprintf(stderr, "getaddrinfo: %s\n", strerror(errno));
		return -1;
	}
	struct addrinfo* aux;
	int sfd = -1;
	for(aux = ptr; aux != NULL; aux = aux->ai_next){
		sfd = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
		if(sfd < 0) continue;
		if(bind(sfd, aux->ai_addr, aux->ai_addrlen) == 0) break;
		close(sfd);
	}
	if(aux == NULL){
		fprintf(stderr, "Bind: %s\n", strerror(errno));
		return -1;
	}
	freeaddrinfo(ptr);
	return sfd;
}

int conectar_cliente(int sfd){
	if(listen(sfd, TAM_COLA) < 0){
		fprintf(stderr, "Listen: %s\n", strerror(errno));
		return -1;
	}
	int cfd = accept(sfd, NULL, NULL);
	if(cfd < 0){
		fprintf(stderr, "Accept: %s\n", strerror(errno));
		return -1;
	}
	return cfd;
}

bool recibir_numero(char* buffer, int cfd){
	memset(buffer, '\0', (TAM_MAX+1)*sizeof(char));
	char aux = '\0';
	int i = 0;
	while(aux != '\n'){
		if(recv(cfd, &aux, 1, 0) <= 0){
			return false;
		}
		if(i < TAM_MAX && aux != '\n'){
			buffer[i] = aux;
			++i;
		}
	}
	printf("Buffer: %s\n", buffer);
	if(strcmp(buffer, "0") == 0){
		return false;
	}
	return true;
}

int main(int argc, char const *argv[]){
	if(argc != 3){
		fprintf(stderr, "Ingrese ip y puerto\n");
		return -1;
	}
	int sfd = crear_servidor(argv[1], argv[2]);
	if(sfd == -1){
		return -1;
	}
	int cfd = conectar_cliente(sfd);
	if(cfd == -1){
		shutdown(sfd, SHUT_RDWR);
		close(sfd);
	}
	char buffer[TAM_MAX+1]; //agrego 1 por el \0
	while(recibir_numero(buffer, cfd)){
		uint32_t numero = atoi(buffer);
		printf("Numero = %i\n", numero);
		uint32_t aux = htonl(numero);
		send(cfd, &aux, 4, MSG_NOSIGNAL);
	}
	shutdown(sfd, SHUT_RDWR);
	shutdown(cfd, SHUT_RDWR);
	close(sfd);
	close(cfd);
	return 0;
}