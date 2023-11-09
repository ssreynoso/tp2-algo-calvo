#include "./include/TesoroBinario.h"
#include "./include/Ficha.h"
#include "./include/Celda.h"
#include <iostream>

void TesoroBinario::colocarEspia(int numeroJugador) {
    int x, y, z;
    std::cout << "Indique la posicion para el espia: " << std::endl;
    recibirPosicion(&x, &y, &z); //Verifica que este en rango y que la celda este activa

    Ficha* ficha = this->tablero->getCelda(x, y, z)->getFicha();
    if (ficha->getJugadorOwner() == numeroJugador) {
        std::cout << "Ya tienes una ficha en esta casilla" << std::endl;
        colocarEspia(numeroJugador);
    } else {
        Celda*   celdaActual  = this->tablero->getCelda(x, y, z);
        Jugador* celdaJugador = this->jugadores->obtener(celdaActual->getFicha()->getJugadorOwner());

        switch (ficha->getTipo()) {
            case VACIO:
                ficha->setJugadorOwner(numeroJugador);
                ficha->setTipo(Espia);
                this->jugadores->obtener(numeroJugador)->incrementarEspias();
                break;
            case Tesoro:
                encontrarTesoro(celdaActual);
                break;
            case Espia:
                eliminarEspias(celdaActual);
                break;
            case Mina:
                explotarEspia(celdaActual, celdaJugador);
                break;
        }
    }
}

void TesoroBinario::encontrarTesoro(Celda* celda) {
    std::cout << "Tu espia encontro un tesoro enemigo. La casilla quedara inactiva por 5 turnos" << std::endl;
    celda->setEstado(false);
    celda->setTurnosInactiva(5);
    // descuento en 1 los tesoros del otro jugador
    this->jugadores->obtener(celda->getFicha()->getJugadorOwner())->descontarTesoros();
}

void TesoroBinario::eliminarEspias(Celda* celda) {
    std::cout << "Tu espia se encontro con un espia enemigo. Ambos son eliminados del juego" << std::endl;

    // descuento en 1 los espias del otro jugador
    this->jugadores->obtener(celda->getFicha()->getJugadorOwner())->descontarEspias();

    // vacio la celda
    celda->getFicha()->setTipo(VACIO);
    celda->getFicha()->setJugadorOwner(-1);
}
