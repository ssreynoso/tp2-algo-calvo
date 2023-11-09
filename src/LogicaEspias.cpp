#include "./include/TesoroBinario.h"
#include <iostream>

void TesoroBinario::colocarEspia(int jugador) {
    int x, y, z;
    std::cout << "Indique la posicion para el espia: " << std::endl;
    recibirPosicion(&x, &y, &z);

    Ficha* ficha = this->tablero->getCelda(x, y, z)->getFicha();
    if (ficha->getJugadorOwner() == jugador) {
        std::cout << "Ya tienes una ficha en esta casilla" << std::endl;
        colocarEspia(jugador);
    } else {
        switch (ficha->getTipo()) {
            case VACIO:
                ficha->setJugadorOwner(jugador);
                ficha->setTipo(Espia);
                this->jugadores->obtener(jugador)->incrementarEspias();
                break;
            case Tesoro:
                encontrarTesoro(this->tablero->getCelda(x, y, z));
                break;
            case Espia:
                eliminarEspias(this->tablero->getCelda(x, y, z));
                break;
            case Mina:
                // pierdeTurno;
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
    this->jugadores->obtener(celda->getFicha()->getJugadorOwner())->descontarTesoros();

    // vacio la celda
    celda->getFicha()->setTipo(VACIO);
    celda->getFicha()->setJugadorOwner(-1);
}