#include <iostream>
#include <sstream>
#include <string>
#include "include/Jugador.h"
#include "include/Tablero.h"

bool rta(std::string texto) {
    return (texto == "Y" || texto == "N");
}

bool confirmar(std::string mensaje) {
    std::string respuesta = "";
    
    while(!rta(respuesta)){
        std::cout << mensaje;
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

bool controlarEscudoJugador(Jugador *jugador){
    bool tieneEscudo = jugador->tieneEscudo();
    if (tieneEscudo){
        std::cout << "El jugador " << jugador->getNumeroDeJugador() << " tiene un escudo activo" << std::endl;
        jugador->desactivarEscudo();
        std::cout << "Se desactivo el escudo del jugador " << jugador->getNumeroDeJugador() << std::endl;
    }
    return tieneEscudo;
}


void recibirPosicion(Tablero* tablero, int* x, int* y, int* z) {
    std::cout << "plano: ";   std::cin >> *x;
    std::cout << "fila: ";    std::cin >> *y;
    std::cout << "columna: "; std::cin >> *z;

    if(!tablero->inRange(*x, *y, *z)) {
        std::cout << "Coordenadas fuera de rango, intentelo nuevamente" << std::endl;
        recibirPosicion(tablero, x, y, z);
    }

    // if(!tablero->getCelda(*x,*y,*z)->estaActiva()) {
    //     std::cout << "La celda indicada esta inactiva" << std::endl;
    //     recibirPosicion(tablero, x, y, z);
    // }
}

Coordenada* getTesoroPropio(Tablero* tablero, int numeroJugador, std::string mensaje) {
    int x, y, z;
    Celda* celda = NULL;
    Ficha* ficha = NULL;
    bool fichaEsTipoTesoro = false;
    bool hayTesoroPropio   = false;

    std::cout << mensaje << std::endl;

    // La ficha tiene que ser de tipo tesoro y tiene que ser un tesoro propio.
    while (!fichaEsTipoTesoro && !hayTesoroPropio) {
        recibirPosicion(tablero, &x, &y, &z);
        celda = tablero->getCelda(x, y, z);
        ficha = celda->getFicha();
        fichaEsTipoTesoro = ficha->getTipo() == Tesoro;
        hayTesoroPropio   = ficha->getJugadorOwner() == numeroJugador;
        
        if (!fichaEsTipoTesoro && !hayTesoroPropio) {
            std::cout << "No hay un tesoro en la celda indicada. Intentelo nuevamente" << std::endl;
        }
    }

    Coordenada* coordenada = new Coordenada();
    coordenada->setCoordenadaX(x);
    coordenada->setCoordenadaY(y);
    coordenada->setCoordenadaZ(z);
    return coordenada;
}