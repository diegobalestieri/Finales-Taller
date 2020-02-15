#include <iostream>
#include <thread>
#include "Contador.h"
#include <list>
#include "DuplicarSiPertenece.cpp"
int main() {
    //Contador c (1000);
    //c.empezar();

    std::list<int> l1 = {1,2,3,4,5,6,7,8};
    std::list<int> l2 = {1,2,4,5,6,7,8};
    duplicarSiNoPertenceInPlace(l1,l2);
    for (auto it = l1.begin(); it != l1.end(); it ++){
        std::cout << *it << ", ";
    }
    return 0;
}
