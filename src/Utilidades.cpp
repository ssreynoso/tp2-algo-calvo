#include <iostream>
#include <sstream>
#include <string>
#include "./include/Tablero.h"

bool rta(std::string texto) {
    return (texto == "Y" || texto == "N");
}

bool confirmar(std::string mensaje) {
    std::string respuesta = "";
    
    while(!rta(respuesta)){
        std::cout << mensaje << std::endl;
        std::cin >>respuesta;
    }

    return respuesta == "Y";
}

std::string toString(int numero) {
    std::stringstream ss;
    ss << numero;

    std::string cadena = ss.str(); 
    return cadena;
}


void recibirPosicion(Tablero* tablero, int* x, int* y, int* z) {
    std::cout << "plano: ";   std::cin >> *x;
	std::cout << "fila: ";    std::cin >> *y;
	std::cout << "columna: "; std::cin >> *z;

	if(!tablero->inRange(*x, *y, *z)) {
		std::cout << "Coordenadas fuera de rango, intentelo nuevamente" << std::endl;
		recibirPosicion(tablero, x, y, z);
	}

	if(!tablero->getCelda(*x,*y,*z)->estaActiva()) {
		std::cout << "La celda indicada esta inactiva" << std::endl;
		recibirPosicion(tablero, x, y, z);
	}
}