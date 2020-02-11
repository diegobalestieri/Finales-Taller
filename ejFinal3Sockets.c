#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdbool.h>

#define TAM_COLA 1
#define TAM_MAX 1024
#define PAQUETE_FIN "<>"
int crear_socket(const char* puerto){
	struct addrinfo* resultado; //es un puntero, porque getaddrinfo, pide memoria para el struct.
	struct addrinfo hints; //Este NO es un puntero porque lo seteo yo.
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; //IPv4
	hints.ai_socktype = SOCK_STREAM; //TCP
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, puerto, &hints, &resultado) != 0){
		fprintf(stderr, "No se pudieron obtener las direcciones\n");
		return -1;
	}

	struct addrinfo* dir_actual;
	int fd = -1;
	for (dir_actual = resultado; dir_actual != NULL; dir_actual = dir_actual->ai_next){
		//Creo un socket con el tipo de internet/dominio (IPv4 -- ai_family), 
		//el tipo/"protocolo" (TCP -- ai_socktype) y el protocolo (ai_protocol)
		fd = socket(dir_actual->ai_family, dir_actual->ai_socktype,dir_actual->ai_protocol);
		if (fd < 0){
			continue;
		}
		//Trato de bindiear en la direccion que estoy (paso la direccion y su longitud)
		if (bind(fd, dir_actual->ai_addr, dir_actual->ai_addrlen) == 0){
			break;
		}
		close(fd);
	}
	if (!dir_actual){
		fprintf(stderr, "Error al intentar bindear: %s\n", strerror(errno));
		return -1;
	}
	return fd;
}

int aceptar_cliente(int fd){
	if (listen(fd, TAM_COLA) != 0){
		fprintf(stderr, "Error en listen: %s\n", strerror(errno));
		return -1;
	}
	int cfd = accept(fd,NULL, NULL);
	if (cfd < 0){
		fprintf(stderr, "Error al aceptar: %s\n", strerror(errno));
		return -1;
	}
	return cfd;
}

bool recibir_paquete(int cfd, char* buffer){
	int posicion = 0;
	while(recv(cfd, &buffer[posicion], 1, 0) > 0){
		if (buffer[0] != '<'){
			printf("Error de protocolo\n");
			memset(buffer, '\0', sizeof(char) * TAM_MAX);
			posicion = 0;
			continue;
		}else if (posicion > TAM_MAX){
			printf("Mensaje demasiado largo\n");
			return false;
		} else if (buffer[0] == '<' && buffer[posicion] == '>'){
			buffer[posicion+1] = '\0';
			char aux[1];
			recv(cfd, aux, 1, 0);  //Saco el \n restante 
			return true;
		}
		posicion++;
	}
	return false;
}
void imprimir_paquetes(int fd, int cfd){
	char buffer[TAM_MAX+1];
	while(recibir_paquete(cfd, buffer)){
		if(strcmp(buffer, PAQUETE_FIN) == 0){
			break;
		}
		printf("Paquete: %s\n",buffer);
	}
}
int main(int argc, char const *argv[]){
	if (argc != 2){
		fprintf(stderr, "No se recibieron los parametros adecuados\n");
		return 1;
	}
	const char* puerto = argv[1];
	int fd = crear_socket(puerto);
	if (fd < 0){
		fprintf(stderr, "Error al crear el socket\n");
		shutdown(fd, SHUT_RDWR);
		close(fd);
		return 1;
	}
	int cfd = aceptar_cliente(fd);
	if (cfd < 0){
		fprintf(stderr, "Error al aceptar cliente\n" );
		shutdown(fd, SHUT_RDWR);
		shutdown(cfd, SHUT_RDWR);
		close(fd);
		close(cfd);
		return 1;
	}
	imprimir_paquetes(fd, cfd);	

	shutdown(fd, SHUT_RDWR);
	shutdown(cfd, SHUT_RDWR);
	close(fd);
	close(cfd);
	return 0;
}