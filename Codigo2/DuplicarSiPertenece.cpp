//
// Created by manfer on 15/2/20.
//
#include <list>
template <class T>
bool pertenece(const T& elemento,const std::list<T>& l){
    for (auto it = l.begin(); it != l.end(); it++){
        if (*it == elemento) return true;
    }
    return false;
}

template<class T>
std::list<T> duplicarSiNoPertence(std::list<T> l1, std::list<T> l2){
    std::list<T> l_aux;
    for (auto it = l1.begin(); it != l1.end(); it++){
        T aux = *it;
        l_aux.push_back(aux);
        if (!pertenece(aux, l2)) l_aux.push_back(aux);
    }
    return l_aux;
}

template<class T>
std::list<T> duplicarSiNoPertenceInPlace(std::list<T>& l1,const std::list<T>& l2){
    for (auto it = l1.begin(); it != l1.end(); it++){
        if (!pertenece(*it, l2)){
            l1.insert(it, *it);
        }
    }
    return l1;
}