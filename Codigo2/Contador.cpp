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
    if (contador <= final){
        std::cout << "Sor imprimir par y el numero es: " << contador << std::endl;
        contador++;
    }
    impar.notify_all();
}

void Contador::imprimir_impar() {
    std::unique_lock<std::mutex> lock(m);
    while (contador % 2 == 0){
        impar.wait(lock);
    }
    if (contador <= final){
        std::cout << "Sor imprimir impar y el numero es: " << contador << std::endl;
        contador++;
    }
    par.notify_all();
}
void imprimir_pares(Contador* c){
    while (c->obtener_actual() <= c->obtener_fin()){
        c->imprimir_par();
    }
}
void imprimir_impares(Contador* c){
    while (c->obtener_actual() <= c->obtener_fin()){
        c->imprimir_impar();
    }
}
void Contador::empezar() {
    std::thread h1 (imprimir_pares, this);
    std::thread h2(imprimir_impares, this);
    h1.join();
    h2.join();
}

Contador::Contador(int fin) : final(fin){
}

int Contador::obtener_fin() {
    return final;
}

int Contador::obtener_actual() {
    return contador;
}
