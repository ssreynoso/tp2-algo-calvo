#include <iostream>
#include <string>

#include "Tablero.h"
#include "Utilidades.h"

Tablero::Tablero(int x, int y, int z) {
    // validar
    this->x = x;
    this->y = y;
    this->z = z;

    this->cubo = new Lista<Lista<Lista<Celda*>*>*>();
    for (int i = 0; i < x; i++) {
        Lista<Lista<Celda*>*>* plano = new Lista<Lista<Celda*>*>();
        for (int j = 0; j < y; j++) {
            Lista<Celda*>* fila = new Lista<Celda*>();
            for (int k = 0; k < z; k++) {
                Celda* celda = new Celda();
                fila->agregar(celda);
                celda->setCoordenada(i + 1, j + 1, k + 1);
            }
            plano->agregar(fila);
        }
        cubo->agregar(plano);
    }
}

Tablero::~Tablero() {
    this->cubo->iniciarCursor();
    while (this->cubo->avanzarCursor()) {
        Lista<Lista<Celda*>*>* plano = this->cubo->obtenerCursor();
        plano->iniciarCursor();
        while (plano->avanzarCursor()) {
            Lista<Celda*>* fila = plano->obtenerCursor();
            fila->obtenerCursor();
            while (fila->avanzarCursor()) {
                delete fila->obtenerCursor();
            }
            delete fila;
        }
        delete plano;
    }
    delete this->cubo;
}

Celda* Tablero::getCelda(int x, int y, int z) {
    if (inRange(x, y, z)) {
        return this->cubo->obtener(x)->obtener(y)->obtener(z);
    } else {
        throw "Las coordenadas indicadas estan fuera de rango";
    }
}

int Tablero::getTamanioX() { return this->x; }

int Tablero::getTamanioY() { return this->y; }

int Tablero::getTamanioZ() { return this->z; }

bool Tablero::inRange(int x, int y, int z) {
    if ((x >= 0 && x <= this->x) && (y >= 0 && y <= this->y) &&
        (z >= 0 && z <= this->z)) {

        return true;
    } else {
        return false;
    }
}

void Tablero::imprimir(int numeroJugador) {
    for (int i = 1; i <= getTamanioX(); i++) {
        std::cout << "Plano " << i << std::endl;
        for (int j = 1; j <= getTamanioY(); j++) {
            for (int k = 1; k <= getTamanioZ(); k++) {
                std::string contenido;
                Celda* celda = getCelda(i, j, k);
                if (!celda->estaActiva()) {
                    contenido = " X ";
                } else {
                    if (celda->getFicha()->getJugadorOwner() == numeroJugador) {
                        switch (celda->getFicha()->getTipo()) {
                            case Espia:
                                contenido = " E ";
                                break;
                            case Tesoro:
                                contenido = " T ";
                                break;
                            case TesoroPartido:
                                contenido = " T ";
                                break;
                            case Mina:
                                contenido = " M ";
                                break;
                            case VACIO:
                                contenido = " - ";
                                break;
                        }
                    } else {
                        contenido = " - ";
                    }
                }
                std::cout << contenido;
            }
            std::cout << std::endl;
        }
        std::cout << "\n----------\n";
    }
}