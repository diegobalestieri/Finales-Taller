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
    int final;
public:
    Contador(int fin);
    void imprimir_par();
    void imprimir_impar();
    void empezar();
    int obtener_fin();
    int obtener_actual();
};



#endif //CODIGO2_CONTADOR_H
