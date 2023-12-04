#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "include/Carta.h"
#include "include/Celda.h"
#include "include/Tablero.h"
#include "include/Utilidades.h"
#include "include/TesoroBinario.h"

using namespace std;

Carta::Carta(TipoCarta carta) {
    this->cartaActiva = true;
    this->carta = carta;
}

void Carta::usarCarta(TesoroBinario* tesoroBinario, Tablero* tablero, Jugador* jugador) {

    this->cartaActiva = false;

    switch (this->carta) {
        case Blindaje:
            this->blindaje(tablero, jugador);
            break;
        case Radar:
            this->radar(tablero, jugador);
            break;
        case PartirTesoro:
            this->partirTesoro(tesoroBinario, tablero, jugador);
            break;
        case EliminarEspia:
            this->eliminarEspia(tablero, jugador);
            break;
        case OmitirTurno:
            break;
        case Escudo:
            break;
    }
}

TipoCarta Carta::getTipoCarta() { return this->carta; }

string Carta::getStringTipoCarta() {
    string tipoDeCarta = "";

    switch (this->carta) {
        case Blindaje:
            tipoDeCarta = "Blindaje";
            break;
        case Radar:
            tipoDeCarta = "Radar";
            break;
        case PartirTesoro:
            tipoDeCarta = "PartirTesoro";
            break;
        case EliminarEspia:
            tipoDeCarta = "EliminarEspia";
            break;
        case OmitirTurno:
            tipoDeCarta = "OmitirTurno";
            break;
        case Escudo:
            tipoDeCarta = "Escudo";
            break;
    }

    return tipoDeCarta;
}

bool Carta::getCartaActiva() { return this->cartaActiva; }

void Carta::blindaje(Tablero* tablero, Jugador* jugador) {
    // Se pide la celda en la que se usará la carta
    int x, y, z;
    std::cout << "Ingrese la celda en la que se usará la carta blindaje: " << std::endl;
    recibirPosicion(tablero, &x, &y, &z);
    
    // Inactiva la celda por varios turnos, por lo tanto no se puede hacer
    // ningun movimiento/jugada en ella hasta que vuelva a la actividad.
    tablero->getCelda(x, y, z)->setEstado(false);
    tablero->getCelda(x, y, z)->setTurnosInactiva(4);
}
void Carta::radar(Tablero* tablero, Jugador* jugador) {
    // Verifica si hay Tesoro cerca (a la redonda)
    // e informa la situación con un mensaje boolenano;

    // Se pide la celda en la que se usará la carta
    int plano, fila, columna;
    std::cout << "Ingrese la celda en la que se usará la carta radar: " << std::endl;
    recibirPosicion(tablero, &plano, &fila, &columna);

    bool hayTesoroCerca = false;

    for (int i = plano - 1; i < plano + 1; i++) {
        for (int j = fila - 1; j < fila + 1; j++) {
            for (int k = columna - 1; k < columna + 1; k++) {
                bool esCeldaValida = tablero->inRange(i, j, k);
                
                if (esCeldaValida) {
                    if (tablero->getCelda(i, j, k)->getFicha()->getTipo() == Tesoro) {
                        hayTesoroCerca = true;
                    }
                }
            }
        }
    }

    // Ficha* comparar1 = tablero->getCelda(x, y - 1, z)->getFicha();
    // if (comparar1->getTipo() != Tesoro) {

    //     Ficha* comparar2 =tablero->getCelda(x + 1, y, z - 1)->getFicha();
    //     if (comparar2->getTipo() != Tesoro) {

    //         Ficha* comparar3 = tablero->getCelda(x + 1, y, z + 1)->getFicha();
    //         if (comparar3->getTipo() != Tesoro) {
    //             hayTesoroCerca = false;
    //         }
    //     }
    // }
    
    if (hayTesoroCerca) {
        std::cout << "Hay un tesoro cerca." << std::endl;
    } else {
        std::cout << "No hay un tesoro cerca." << std::endl;
    }
}
void Carta::partirTesoro(TesoroBinario* tesoroBinario, Tablero* tablero, Jugador* jugador) {
    // Parte un Tesoro en dos, cambiando la ficha de la celda inicial a ficha=
    // TesoroPartido
    //  Agregando la otra mitad a un casilla elegida
    int numeroJugador = jugador->getNumeroDeJugador();

    Coordenada* coordenadaTesoroAPartir = getTesoroPropio(tablero, numeroJugador, "Indique la posicion del tesoro a partir: ");

    int nuevoPlano = 0, nuevaFila = 0, nuevaColumna = 0;
    cout << "Ingrese la celda en la que se ubicará la otra parte del tesoro: " << endl;
    recibirPosicion(tablero, &nuevoPlano, &nuevaFila, &nuevaColumna);

    Celda* celdaTesoroPartido1 = tablero->getCelda(
        coordenadaTesoroAPartir->getCoordenadaX(), 
        coordenadaTesoroAPartir->getCoordenadaY(),
        coordenadaTesoroAPartir->getCoordenadaZ()
    );
    Celda* celdaTesoroPartido2 = tablero->getCelda(nuevoPlano, nuevaFila, nuevaColumna);


    celdaTesoroPartido1->getFicha()->setTipo(TesoroPartido);
    celdaTesoroPartido1->getFicha()->setJugadorOwner(numeroJugador);
    celdaTesoroPartido2->getFicha()->setTipo(TesoroPartido);
    celdaTesoroPartido2->getFicha()->setJugadorOwner(numeroJugador);
    tesoroBinario->pintarPixel("T", numeroJugador, nuevaFila, nuevaColumna, nuevoPlano);
    jugador->incrementarTesoros();
}
void Carta::eliminarEspia(Tablero* tablero, Jugador* jugador) {
    int plano = 0, fila = 0, columna = 0;
    int planoEspiaEncontrado = 0, filaEspiaEncontrado = 0, columnaEspiaEncontrado = 0;
    cout << "Ingrese la celda en la que se buscará un espía adyacente: ";
    recibirPosicion(tablero, &plano, &fila, &columna);

    // Verifica si hay un Espia cerca, eliminando el último que aparece
    bool hayEspiaCerca = false;

    for (int i = plano - 1; i < plano + 1; i++) {
        for (int j = fila - 1; j < fila + 1; j++) {
            for (int k = columna - 1; k < columna + 1; k++) {
                bool esCeldaValida = tablero->inRange(i, j, k);
                
                if (esCeldaValida) {
                    if (tablero->getCelda(i, j, k)->getFicha()->getTipo() == Tesoro) {
                        hayEspiaCerca = true;
                    }
                }
            }
        }
    }

    if (hayEspiaCerca) {
        Ficha* fichaEspiaEncontrado = tablero->getCelda(planoEspiaEncontrado, filaEspiaEncontrado, columnaEspiaEncontrado)->getFicha();
        fichaEspiaEncontrado->setTipo(VACIO);
        fichaEspiaEncontrado->setJugadorOwner(-1);
        fichaEspiaEncontrado->setNumFicha(-1);
        cout << "Se encontró un espía adyacente y se ha eliminado." << endl;
    } else {
        cout << "No se encontró un espía adyacente." << endl;
    }
}

void Carta::omitirTurno(Jugador* jugador) {
    std::cout << "Ups.. Mala suerte. Obtuviste una carta que omite tu turno." << std::endl;
    jugador->setOmitirTurno(true);
}

void Carta::asignarEscudo(Jugador* jugador) {
    std::cout << "Que suerte! Obtuviste una carta que te da un escudo." << std::endl;
    jugador->activarEscudo();
}