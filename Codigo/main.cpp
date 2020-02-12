#include <iostream>
#include <thread>
#include "SumadorProtegido.h"
#include "ContadorDeInstancias.h"

#include <list>
#include "Interseccion.cpp"
class Sumar_impar{
private:
    SumadorProtegido& sumador;
public:
    Sumar_impar(SumadorProtegido& o) : sumador(o) {}
    void operator() () {
        int num = sumador.obtener();
        while (num < 100){
            if (num % 2 != 0){
                std::cout << "Soy el hilo impar y el numero es: " << num << '\n';
                sumador.incrementar();
            }
            num = sumador.obtener();
        }
    }
};
class Sumar_par{
private:
    SumadorProtegido& sumador;
public:
    Sumar_par(SumadorProtegido& o) : sumador(o){}
    void operator() (){
        int num = sumador.obtener();
        while (num <= 100){
            if (num % 2 == 0){
                std::cout << "Soy el hilo par y el numero es: " << num << '\n';
                sumador.incrementar();
            }
            num = sumador.obtener();
        }
    }
};
int main() {
    SumadorProtegido sumador;
    Sumar_par sumador_par (sumador);
    Sumar_impar sumador_impar (sumador);
    std::thread hilo1 (sumador_par);
    std::thread hilo2 (sumador_impar);
    hilo1.join();
    hilo2.join();

    //Prueba de un atributo estatico en una clase
    ContadorDeInstancias c1;
    std::cout << c1.obtenerNroInstancias() << std::endl;
    if (true){
        ContadorDeInstancias c2;
        std::cout << c1.obtenerNroInstancias() << " y " << c2.obtenerNroInstancias() << std::endl;
    }
    std::cout << c1.obtenerNroInstancias() << std::endl;

    std::list<int> l1 = {1,2,3,4,5,6,7,8,9};
    std::list<int> l2 = {4,2};
    std::list<int> res = interseccion(l1, l2);
    for (auto it = res.begin(); it != res.end(); it++){
        std::cout << *it << ", ";
    }
    return 0;
}