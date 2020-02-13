#include <iostream>
#include <thread>
#include "Contador.h"

void par(Contador* c){
    for (int i = 0; i <= 10; i++){
        c->imprimir_par();
    }
}
void impar(Contador* c){
    for (int i = 0; i < 10; i++){
        c->imprimir_impar();
    }
}

int main() {
    Contador c;
    std::thread h1 (par, &c);
    std::thread h2 (impar, &c);
    h1.join();
    h2.join();
    return 0;
}
