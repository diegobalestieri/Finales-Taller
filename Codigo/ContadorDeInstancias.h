//
// Created by manfer on 11/2/20.
//

#ifndef CODIGO_CONTADORDEINSTANCIAS_H
#define CODIGO_CONTADORDEINSTANCIAS_H


class ContadorDeInstancias {
private:
    static int contador;
public:
    ContadorDeInstancias();
    ~ContadorDeInstancias();
    int obtenerNroInstancias();
};

#endif //CODIGO_CONTADORDEINSTANCIAS_H
