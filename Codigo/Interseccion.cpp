#include <list>

template <class T>
bool esta_en_lista(const std::list<T>& lista,const T& elemento){
    for (auto it = lista.begin(); it != lista.end(); it++){
        if(*it == elemento){
            return true;
        }
    }
    return false;
}
template <class T>
std::list<T> interseccion(const std::list<T>& lista1,const std::list<T>& lista2){
    std::list<T> resultado;
    for (auto it = lista1.begin(); it != lista1.end(); it++){
        if(esta_en_lista(lista2,*it)){
            resultado.push_back(*it);
        }
    }
    return resultado;
}
