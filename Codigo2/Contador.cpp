//
// Created by manfer on 12/2/20.
//

#include <iostream>
#include <thread>
#include "Contador.h"

void Contador::imprimir_par() {
    std::unique_lock<std::mutex> lock(m);
    while (contador % 2 != 0){
        par.wait(lock);
    }
    std::cout << "Sor imprimir par y el numero es: " << contador << std::endl;
    contador++;
    impar.notify_all();
}

void Contador::imprimir_impar() {
    std::unique_lock<std::mutex> lock(m);
    while (contador % 2 == 0){
        impar.wait(lock);
    }
    std::cout << "Sor imprimir impar y el numero es: " << contador << std::endl;
    contador++;
    par.notify_all();
}

void Contador::empezar() {
    std::thread h1 (&Contador::imprimir_par, this);
    std::thread h2(&Contador::imprimir_impar, this);

}
