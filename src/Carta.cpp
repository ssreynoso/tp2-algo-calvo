#include "Carta.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Celda.h"
#include "Tablero.h"
#include "TesoroBinario.h"

using namespace std;

Carta::Carta(TipoCarta carta) {
    this->cartaActiva = true;
    this->carta = carta;
}

void Carta::usarCarta(Tablero* tablero, Coordenada coord) {

    this->cartaActiva = false;

    switch (this->carta) {
        case Blindaje:
            this->blindaje(tablero, coord);
            break;
        case Radar:
            this->radar(tablero, coord);
            break;
        case PartirTesoro:
            this->partirTesoro(tablero, coord);
            break;
        case EliminarEspia:
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
            break;
        case OmitirTurno:
            break;
        case Escudo:
            break;
    }

    return tipoDeCarta;
}

bool Carta::getCartaActiva() { return this->cartaActiva; }

string Carta::getStringTipoFicha(TipoContenido tipo) {
    string tipoDeCarta = "";

    switch (tipo) {
        case Espia:
            tipoDeCarta = "Espia";
            break;
        case Tesoro:
            tipoDeCarta = "Tesoro";
            break;

        default:
            tipoDeCarta = "Vacio";
            break;
    }
    return tipoDeCarta;
}

void Carta::blindaje(Tablero* tablero, Coordenada coord) {
    // Inactiva la celda por varios turnos, por lo tanto no se puede hacer
    // ningun movimiento/jugada en ella hasta que vuelva a la actividad.
    tablero
        ->getCelda(
            coord.getCoordenadaX(),
            coord.getCoordenadaY(),
            coord.getCoordenadaZ()
        )
        ->setEstado(false);
    tablero
        ->getCelda(
            coord.getCoordenadaX(),
            coord.getCoordenadaY(),
            coord.getCoordenadaZ()
        )
        ->setTurnosInactiva(4);
}
bool Carta::radar(Tablero* tablero, Coordenada coord) {
    // Verifica si hay Tesoro cerca (a la redonda)
    // e informa la situación con un mensaje boolenano;

    std::cout << "Verificando si hay tesoros cerca" << std::endl;
    bool hayTesoroCerca = true;
    Ficha* comparar1 =
        tablero
            ->getCelda(
                coord.getCoordenadaX(),
                coord.getCoordenadaY() - 1,
                coord.getCoordenadaZ()
            )
            ->getFicha();
    if (comparar1->getTipo() != Tesoro) {
        Ficha* comparar2 =
            tablero
                ->getCelda(
                    (coord.getCoordenadaX()) + 1,
                    coord.getCoordenadaY(),
                    (coord.getCoordenadaZ()) - 1
                )
                ->getFicha();
        if (comparar2->getTipo() != Tesoro) {
            Ficha* comparar3 = tablero
                                   ->getCelda(
                                        (coord.getCoordenadaX()) + 1,
                                        coord.getCoordenadaY(),
                                        coord.getCoordenadaZ() + 1
                                    )
                                   ->getFicha();
            if (comparar3->getTipo() != Tesoro) {
                hayTesoroCerca = false;
            }
        }
    }
    return hayTesoroCerca;
}
void Carta::partirTesoro(Tablero* tablero, Coordenada coord) {
    // Parte un Tesoro en dos, cambiando la ficha de la celda inicial a ficha=
    // TesoroPartido
    //  Agregando la otra mitad a un casilla elegida

    Coordenada coord2;
    int x = 0, y = 0, z = 0;

    cout << "Ingrese coordenada en formato 'x y z': ";
    cin >> x >> y >> z;
    coord2.setCoordenadaX(x);
    coord2.setCoordenadaY(y);
    coord2.setCoordenadaZ(z);
    tablero
        ->getCelda(
            coord.getCoordenadaX(), 
            coord.getCoordenadaY(),
            coord.getCoordenadaZ()
        )
        ->getFicha()
        ->setTipo(TesoroPartido);
    tablero
        ->getCelda(
            coord2.getCoordenadaX(), 
            coord2.getCoordenadaY(),
            coord2.getCoordenadaZ()
        )
        ->getFicha()
        ->setTipo(TesoroPartido);
}
void Carta::eliminarEspia(Tablero* tablero, Coordenada coord) {
    // Verifica si hay un Espia cerca, eliminando el primero que aparece

    std::cout << "Verificando si hay Espias cerca" << std::endl;

    Ficha* comparar1 =
        tablero
            ->getCelda(
                coord.getCoordenadaX(), 
                coord.getCoordenadaY() - 1,
                coord.getCoordenadaZ()
            )
            ->getFicha();
    if (comparar1->getTipo() != Espia) {
        Ficha* comparar2 =
            tablero
                ->getCelda((
                    coord.getCoordenadaX()) + 1, 
                    coord.getCoordenadaY(),
                    coord.getCoordenadaZ() - 1
                )
                ->getFicha();
        if (comparar2->getTipo() != Espia) {
            Ficha* comparar3 = tablero
                                   ->getCelda((
                                        coord.getCoordenadaX()) + 1,
                                        coord.getCoordenadaY(),
                                        coord.getCoordenadaZ() + 1
                                    )
                                   ->getFicha();
            if (comparar3->getTipo() == Espia) {
                comparar3->setTipo(VACIO);
                comparar3->setJugadorOwner(-1);
                comparar3->setNumFicha(-1);
            }
        } else {
            comparar2->setTipo(VACIO);
            comparar2->setJugadorOwner(-1);
            comparar2->setNumFicha(-1);
        }
    } else {
        comparar1->setTipo(VACIO);
        comparar1->setJugadorOwner(-1);
        comparar1->setNumFicha(-1);
    }
}
