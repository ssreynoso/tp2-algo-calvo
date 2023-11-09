#include <string>
#include <iostream>
#include "TesoroBinario.h"
#include "Utilidades.h"
#include "Ficha.h"

void TesoroBinario::colocarTesoro(int x, int y, int z, int jugador) {
    this->tablero->getCelda(x, y, z)->getFicha()->setTipo(Tesoro);
    this->tablero->getCelda(x, y, z)->getFicha()->setJugadorOwner(jugador);
}

void TesoroBinario::colocarTesoro(Celda* celda, int jugador) {
    celda->getFicha()->setTipo(Tesoro);
    celda->getFicha()->setJugadorOwner(jugador);
}

Celda* obtenerTesoroPropio(TesoroBinario* tesoroBinario, Tablero* tablero, int numeroJugador) {
    int x, y, z;
    Celda* celda = NULL;
    Ficha* ficha = NULL;
    bool fichaEsTipoTesoro = false;
    bool hayTesoroPropio   = false;

    std::cout << "JUGADOR " << toString(numeroJugador) << " indique la posicion del tesoro a mover: " << std::endl;

    // La ficha tiene que ser de tipo tesoro y tiene que ser un tesoro propio.
    while (!fichaEsTipoTesoro && !hayTesoroPropio) {
        tesoroBinario->recibirPosicion(&x, &y, &z);
        celda = tablero->getCelda(x, y, z);
        ficha = celda->getFicha();
        fichaEsTipoTesoro = ficha->getTipo() == Tesoro;
        hayTesoroPropio   = ficha->getJugadorOwner() == numeroJugador;
        
        if (!fichaEsTipoTesoro && !hayTesoroPropio) {
            std::cout << "No hay un tesoro en la celda indicada. Intentelo nuevamente" << std::endl;
        }
    }

    return celda;
}

Celda* obtenerNuevaPosicion(TesoroBinario* tesoroBinario, Tablero* tablero, int numeroJugador) {
    int x, y, z;
    Celda* celda = NULL;
    Ficha* ficha = NULL;
    bool celdaInactiva   = true;
    bool hayTesoroPropio = true;

    // Se pide una nueva posición
    std::cout << "JUGADOR " << toString(numeroJugador) << " Indique la nueva posicion del tesoro: " << std::endl;

    // La celda no tiene que estar inactiva y no tiene que haber un tesoro propio.
    while (celdaInactiva && hayTesoroPropio) {
        tesoroBinario->recibirPosicion(&x, &y, &z);
        celda = tablero->getCelda(x, y, z);
        ficha = celda->getFicha();
        celdaInactiva   = !celda->estaActiva();
        hayTesoroPropio = ficha->getTipo() == Tesoro && ficha->getJugadorOwner() == numeroJugador;

        if (celdaInactiva) {
            std::cout << "Esta celda está inactiva, intente nuevamente" << std::endl;
            std::cout << "Indique la nueva posicion del tesoro: " << std::endl;
            continue;
        }

        if (hayTesoroPropio) {
            std::cout << "Ya tienes un tesoro en esta celda, intente nuevamente" << std::endl;
            std::cout << "Indique la nueva posicion del tesoro: " << std::endl;
        }
    }

    return celda;
}

void TesoroBinario::moverTesoro(Jugador* jugador) {
    int numeroJugador = jugador->getNumeroDeJugador();
    Celda* tesoroPropio       = obtenerTesoroPropio(this, this->tablero, numeroJugador);
    Celda* nuevaPosicion      = obtenerNuevaPosicion(this, this->tablero, numeroJugador);
    Ficha* fichaNuevaPosicion = nuevaPosicion->getFicha();
    Ficha* fichaTesoroPropio  = tesoroPropio->getFicha();

    switch (fichaNuevaPosicion->getTipo()) {
        case VACIO:
            colocarTesoro(nuevaPosicion, numeroJugador);
            fichaTesoroPropio->resetFicha();
            break;
        case Tesoro:
            std::cout << "Hay un tesoro enemigo en esta posición, envie un espía" << std::endl;
            // No utilizo un while porque si ya le doy la información de que hay un
            // tesoro enemigo sería injusto que pueda intentar muchas veces con
            // chances de encontrar múltiples tesoros enemigos.
            break;
        case Espia:
            std::cout << "Tu tesoro ha sido encontrado por un espia enemigo. La casilla quedara inactiva por 5 turnos" << std::endl;
            nuevaPosicion->setEstado(false);
            nuevaPosicion->setTurnosInactiva(5);
            jugador->descontarTesoros();
            break;
        case Mina:
            // pierdeTurno;
            std::cout << "Ups... En ese casillero había una mina enemiga. La casilla quedara inactiva por 3 turnos" << std::endl;
            explotarTesoro(nuevaPosicion, jugador);
            break;
    }
}
