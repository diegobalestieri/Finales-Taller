//
// Created by diego on 10/2/20.
//

#include <iostream>
#include "SumadorProtegido.h"

SumadorProtegido::SumadorProtegido() : numero(1){

}

void SumadorProtegido::incrementar() {
    std::unique_lock<std::mutex> lock(m);
    numero++;
}

int SumadorProtegido::obtener() {
    return numero;
}
