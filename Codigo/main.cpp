#include <iostream>
#include <thread>
#include "SumadorProtegido.h"

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
    return 0;
}