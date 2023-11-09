#include <iostream>
#include <sstream>
#include <string>
#include "Tablero.h"

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