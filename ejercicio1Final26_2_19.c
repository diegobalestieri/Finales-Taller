#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdbool.h>
#include <errno.h>

#define CANT_MAX_BUFFER 1024
#define TAM_COLA 1

int crear_socket(const char* port, const char* ip, int* peerskt){
	struct addrinfo hints;
	struct addrinfo *ptr;
	struct addrinfo *res = NULL;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; // IPv4 (or AF_INET6 for IPv6)
	hints.ai_socktype = SOCK_STREAM; // TCP (or SOCK_DGRAM for UDP)
	hints.ai_flags = AI_PASSIVE;	// AI_PASSIVE for server
	int skt;
	int s = getaddrinfo(ip, port, &hints, &ptr);
	if(s != 0){
		fprintf(stderr, "Getaddrinfo: %s\n", gai_strerror(s));
        return -1;
	}
	for (res = ptr; res != NULL; res = res->ai_next) {
		skt = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (skt == -1){continue;}
        if (bind(skt, res->ai_addr, res->ai_addrlen) == 0){
            break;
        }
        close(skt);
	}
	if(res == NULL){
		fprintf(stderr, "Bind: %s\n", strerror(errno));
		return -1;
	}
	if( listen(skt, TAM_COLA) ){
		fprintf(stderr, "Listen: %s\n", strerror(errno));
		return -1;
	}
	*peerskt = accept(skt, NULL, NULL);
	if(*peerskt == -1){
		fprintf(stderr, "Accept: %s\n", strerror(errno));
		return -1;
	}
	freeaddrinfo(ptr);
	return skt;
}

int main(int argc, char const *argv[]) {
	if(argc != 3){
		printf("Ingrese un puerto y un ip.\n");
		return 0;
	}
	const char* ip = argv[1];
	const char* puerto = argv[2];
	int peerskt = 0;
	int skt = crear_socket(puerto, ip, &peerskt);
	if(skt == -1) {
		return -1;
	}
	char buffer[CANT_MAX_BUFFER];
	int leidos = 0;
	while(true){
		leidos = recv(peerskt,buffer, CANT_MAX_BUFFER, 0);
		if(leidos < 0){
			fprintf(stderr, "Recv: %s\n", strerror(errno));
			break;
		}
		if(leidos == 0){
			printf("F en el chat por el cliente\n");
			break;
		}
		if(buffer[0] != '[' || buffer[leidos-2] != ']') { //el -2 es porque del netcat llega con un \n de mas
			printf("Error de protocolo\n");
			continue;
		} else if(buffer[0] == '[' && buffer[1] == ']') {
			break;
		}
		int suma = 0;
		for (int i = 1; i < leidos-2; ++i) { //el -2 es porque del netcat llega con un \n de mas
			suma += buffer[i];
		}
		printf("La suma es: %i\n", suma);
	}
	shutdown(peerskt, SHUT_RDWR);
	shutdown(skt, SHUT_RDWR);
	close(skt);
	close(peerskt);
	return 0;
}