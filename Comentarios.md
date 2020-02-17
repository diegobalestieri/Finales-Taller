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

Para swapear endiannes de **2 bytes** se puede hacer: `short a = (aux>>8) | (aux<<8);`

En C, si vos haces `int* dir = 1000;`, es equivalente hacer: `dir[1]` == `dir++` == `dir + sizeof(int)*1`.

Cuando se declaran operadores, solo se devuelve con referencia cuando se devuelve un objeto ya creado, ya sea sí mismo (ya está contruido el \*this) o otro objeto externo. Cuando se devuelven objetos creados en el cuerpo del operador en el stack se devuelve por copia.
Ej:
 - `Telefono operator+(const Telefono& otro);` Este operador de suma devuelve un objeto nuevo con la suma de si mismo con el otro y como lo crea en el stack debe devolverlo por copia   
 - `Telefono& operador++();` El operador de pre incremento se devuelve a sí mismo luego de incrementar.  
 - `Telefono& operator=(const Telefono& otro);` El operador de asignación por copia se devuelve a sí mismo despues de haber copiado los atributos del otro.  
 - `Telefono operator++(int);` El operador de post incremento devuelve un objeto nuevo, porque se hace una copia y luego incrementa. Y devuelve el valor previo a hacer el incremento (la copia)  