//
// Created by manfer on 11/2/20.
//

#include "ContadorDeInstancias.h"

int ContadorDeInstancias::contador = 0;

ContadorDeInstancias::ContadorDeInstancias(){
    contador++;
}

ContadorDeInstancias::~ContadorDeInstancias() {
    contador--;
}

int ContadorDeInstancias::obtenerNroInstancias() {
    return contador;
}
