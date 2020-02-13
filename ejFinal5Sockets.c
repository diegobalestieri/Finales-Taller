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
#define TAM_MAX 3

int crear_socket(const char* ip, const char* puerto){
	struct addrinfo* resultado;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(ip, puerto, &hints, &resultado) != 0){
		fprintf(stderr, "Error getaddrinfo: %s\n", strerror(errno));
		return -1;
	}
	int fd = -1;
	struct addrinfo* actual;
	for (actual = resultado; actual != NULL; actual = actual->ai_next){
		fd = socket(actual->ai_family, actual->ai_socktype,  actual->ai_protocol);
		if (fd < -1){
			continue;
		}
		if (bind(fd, actual->ai_addr, actual->ai_addrlen) == 0){
			break;
		}
		close(fd);
	}
	if (actual == NULL){
		fprintf(stderr, "Error en el bind: %s\n", strerror(errno) );
		freeaddrinfo(resultado);
		return -1;
	}
	freeaddrinfo(resultado);
	return fd;
}

int aceptar_cliente(int fd){
	if (listen(fd, TAM_COLA) < 0){
		fprintf(stderr, "Error listen: %s\n", strerror(errno));
		return -1;
	}
	int cfd = accept(fd, NULL, NULL);
	if (cfd < 0){
		fprintf(stderr, "Error en acept: %s\n", strerror(errno));
		return -1;
	}
	return cfd;
}
bool recibir_linea(int cfd, char* buffer){
	int i = 0;
	memset(buffer, '\0', TAM_MAX * sizeof(char));

	char c = '\0';
	while(recv(cfd, &c, 1, 0) > 0){
		if (i >= TAM_MAX){
			memset(buffer, '\0', TAM_MAX * sizeof(char));
			i = 0;
			printf("Mensaje demasiado largo\n");
			continue;
		}
		if (c == '\n'){
			buffer[i] = '\0';
			return true;
		}
		buffer[i] = c;
		i++;
	}
	return false;
}
void hacer_cosas(int fd, int cfd){
	char buffer[TAM_MAX];
	while (recibir_linea(cfd, buffer)){
		if (strcmp(buffer, "0") == 0){
			break;
		}
		uint32_t num = htonl(atoi(buffer));
		printf("Numero luego de htonl: %d\n", ntohl(num));
		send(cfd, &num, sizeof(uint32_t), MSG_NOSIGNAL);
	}
}
int main(int argc, char const *argv[]){
	if (argc != 3){
		fprintf(stderr, "Cant de argumentos invalida\n");
		return 1;
	}
	const char* ip = argv[1];
	const char* puerto = argv[2];
	int fd = crear_socket(ip, puerto);
	if (fd < 0) return 1;
	int cfd = aceptar_cliente(fd);
	if (cfd < 0){
		shutdown(fd, SHUT_RDWR);
		close(fd);
		return 1;
	}
	hacer_cosas(fd, cfd);
	shutdown(fd, SHUT_RDWR);
	shutdown(cfd, SHUT_RDWR);
	close(cfd);
	close(fd);
	return 0;
}