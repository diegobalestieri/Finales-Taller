//
// Created by manfer on 12/2/20.
//

#ifndef CODIGO2_CONTADOR_H
#define CODIGO2_CONTADOR_H


#include <condition_variable>

class Contador {
private:
    std::mutex m;
    std::condition_variable par;
    std::condition_variable impar;
    int contador = 0;
public:
    void imprimir_par();
    void imprimir_impar();
    void empezar();
};


#endif //CODIGO2_CONTADOR_H
