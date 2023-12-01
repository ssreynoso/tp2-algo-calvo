#include <string>
#include <iostream>
#include "include/TesoroBinario.h"
#include "include/Utilidades.h"
#include "include/Ficha.h"

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
    bool hayEspiaPropio  = true;
    bool hayMinaPropia   = true;

    // Se pide una nueva posición
    std::cout << "JUGADOR " << toString(numeroJugador) << " ";

    // La celda no tiene que estar inactiva y no tiene que haber un tesoro propio.
    while (celdaInactiva || hayTesoroPropio || hayEspiaPropio || hayMinaPropia) {
        std::cout << "Indique la nueva posicion del tesoro: " << std::endl;
        tesoroBinario->recibirPosicion(&x, &y, &z);
        celda = tablero->getCelda(x, y, z);
        ficha = celda->getFicha();
        bool esCeldaPropia = ficha->getJugadorOwner() == numeroJugador;

        celdaInactiva   = !celda->estaActiva();
        hayTesoroPropio = (ficha->getTipo() == Tesoro || ficha->getTipo() == TesoroPartido) && esCeldaPropia;
        hayEspiaPropio  = ficha->getTipo() == Espia && esCeldaPropia;
        hayMinaPropia   = ficha->getTipo() == Mina && esCeldaPropia;

        if (celdaInactiva) {
            std::cout << "Esta celda está inactiva, intente nuevamente" << std::endl;
        }

        if (hayTesoroPropio) {
            std::cout << "Ya tienes un tesoro en esta celda, intente nuevamente" << std::endl;
        }

        if (hayEspiaPropio) {
            std::cout << "Ya tienes un espía en esta celda, intente nuevamente" << std::endl;
        }

        if (hayMinaPropia) {
            std::cout << "Ya tienes una mina en esta celda, intente nuevamente" << std::endl;
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

    int coordenadaX = tesoroPropio->getCoordenada()->getCoordenadaX();
    int coordenadaY = tesoroPropio->getCoordenada()->getCoordenadaY();
    int coordenadaZ = tesoroPropio->getCoordenada()->getCoordenadaZ();

    int nuevaCoordenadaX = nuevaPosicion->getCoordenada()->getCoordenadaX();
    int nuevaCoordenadaY = nuevaPosicion->getCoordenada()->getCoordenadaY();
    int nuevaCoordenadaZ = nuevaPosicion->getCoordenada()->getCoordenadaZ();

    switch (fichaNuevaPosicion->getTipo()) {
        case VACIO:
            colocarTesoro(nuevaPosicion, numeroJugador);
            fichaTesoroPropio->resetFicha();
            pintarPixel("-",numeroJugador,coordenadaX,coordenadaY,coordenadaZ);
            pintarPixel("T",numeroJugador,nuevaCoordenadaX,nuevaCoordenadaY,nuevaCoordenadaZ);
            break;
        case Tesoro:
            std::cout << "Hay un tesoro enemigo en esta posición, envie un espía" << std::endl;
            // No utilizo un while porque si ya le doy la información de que hay un
            // tesoro enemigo sería injusto que pueda intentar muchas veces con
            // chances de encontrar múltiples tesoros enemigos.
            break;
        case TesoroPartido:
            std::cout << "Hay un tesoro partido enemigo en esta posición, envie un espía" << std::endl;
            // No utilizo un while porque si ya le doy la información de que hay un
            // tesoro enemigo sería injusto que pueda intentar muchas veces con
            // chances de encontrar múltiples tesoros enemigos.
            break;
        case Espia:
            std::cout << "Tu tesoro ha sido encontrado por un espia enemigo. La casilla quedara inactiva por 5 turnos" << std::endl;
            nuevaPosicion->setEstado(false);
            nuevaPosicion->setTurnosInactiva(5);
            jugador->descontarTesoros();
            pintarPixel("-",numeroJugador,coordenadaX,coordenadaY,coordenadaZ);
            pintarActivoInactivo(nuevaCoordenadaX,nuevaCoordenadaY,nuevaCoordenadaZ,'$');
            break;
        case Mina:
            // pierdeTurno;
            std::cout << "Ups... En ese casillero había una mina enemiga. La casilla quedara inactiva por 3 turnos" << std::endl;
            explotarTesoro(nuevaPosicion, jugador);
            pintarPixel("-",numeroJugador,coordenadaX,coordenadaY,coordenadaZ);
            pintarActivoInactivo(nuevaCoordenadaX,nuevaCoordenadaY,nuevaCoordenadaZ,'$');
            break;
    }
}
