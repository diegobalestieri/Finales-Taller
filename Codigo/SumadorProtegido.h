//
// Created by diego on 10/2/20.
//

#ifndef CODIGO_SUMADORPROTEGIDO_H
#define CODIGO_SUMADORPROTEGIDO_H


#include <mutex>

class SumadorProtegido {
private:
    int numero;
    std::mutex m;
public:
    SumadorProtegido();
    void incrementar();
    int obtener();
};


#endif //CODIGO_SUMADORPROTEGIDO_H
