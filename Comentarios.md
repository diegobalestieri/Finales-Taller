Se usan dos punteros a struct addrinfo porque uno apunta siempre al comienzo de la lista enlazada. Y el otro lo uso para recorrer.
Uso el que apunta al comienzo para liberar los recursos luego con freeaddrinfo()

El operador para convertir a entero, su declaracion es:   
			operator int() const; 

Para los operadores << y >> de STREAM. Que son los que se usan para imprimir o cargar datos de una clase Fraccion desde un stream de datos.  
> **friend** std::istream& operator>>(std::istream& in, Fraction& a); //operador de carga   
> **friend** std::ostream& operator<<(std::ostream& out, const Fraction& a); //operador de impresion   
Se tiene que agregar la declaracion **friend** porque son operadores de la clase STREAM (o algo así). Y con esta declaracion le permitís a 
esta clase acceder en esta funcion a los atributos privados de la clase Fraccion.  
Mas informacion sobre friends: [aqui](https://en.cppreference.com/w/cpp/language/friend)  



unsigned really is a shorthand for **unsigned int**, and so defined in standard C.


En C, si vos haces `int* dir = 1000;`, es equivalente hacer: `dir[1]` == `dir++` == `dir + sizeof(int)*1`.