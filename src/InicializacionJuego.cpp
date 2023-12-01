#include <cstdlib>
#include <iostream>
#include "include/TesoroBinario.h"

void TesoroBinario::cargarTesorosPorJugador() {
    int cantidadDeTesoros;
    std::cout << "Indicar la cantidad de tesoros por jugador: ";
    std::cin >> cantidadDeTesoros;
    while (cantidadDeTesoros <= 0) {
        std::cout << "\nValor invalido, intentelo nuevamente: ";
        std::cin >> cantidadDeTesoros;
    }
    for (int i = 1; i <= this->cantidadJugadores; i++) {
        this->jugadores->obtener(i)->setTesoro(cantidadDeTesoros);
    }

    for (int i = 0; i < cantidadDeTesoros; i++) {
        for (int j = 1; j <= this->cantidadJugadores; j++) {
            int x, y, z;
            std::cout << "JUGADOR " << j
                      << " indique la posicion del tesoro numero " << i + 1
                      << " (plano, fila, columna): " << std::endl;

            recibirPosicion(&x, &y, &z);
            while (this->tablero->getCelda(x, y, z)->getFicha()->getTipo() == Tesoro) {
                std::cout << "Ya hay un tesoro en la celda indicada. Intentelo nuevamente"
                          << std::endl;
                recibirPosicion(&x, &y, &z);
            }
            colocarTesoro(x, y, z, j);
            pintarPixel("T", j, y, z, x);
        }
    }
}

//
// Pruebas con carga aleatoria
//
void TesoroBinario::cargarJuego() {
    this->cargarCantidadesDeFichasAJugadores();
    std::cout << this->jugadores->obtener(1)->getEspias() << std::endl;
    this->cargarFichas();
    // this->tablero->getCelda(3,3,3)->getFicha()->setTipo(Tesoro);
    std::cout << "fichas cargadas" << std::endl;
}

void TesoroBinario::cargarCantidadesDeFichasAJugadores() {
    this->jugadores->iniciarCursor();
    while (this->jugadores->avanzarCursor()) {
        this->jugadores->obtenerCursor()->setEspia(1);
        this->jugadores->obtenerCursor()->setTesoro(1);
    }
}

bool TesoroBinario::validarCeldaAInsertarFicha(Coordenada coordenada) {
    TipoContenido tipo =
        this->tablero
            ->getCelda(
                coordenada.getCoordenadaX(),
                coordenada.getCoordenadaY(),
                coordenada.getCoordenadaZ()
            )
            ->getFicha()
            ->getTipo();

    return (tipo == VACIO);
}

void TesoroBinario::cargarFichaDelTipo(
    int           cantidadDeCarga,
    TipoContenido tipoDeFicha,
    int           jugadorOwner
) {
    Coordenada coordenada;
    for (int i = 0; i < cantidadDeCarga; i++) {
        do {
            int x, y, z;
            x = rand() % this->tablero->getTamanioX() + 1;
            y = rand() % this->tablero->getTamanioY() + 1;
            z = rand() % this->tablero->getTamanioZ() + 1;
            std::cout << x << y << z << std::endl;
            coordenada.setCoordenadaX(x);
            coordenada.setCoordenadaY(y);
            coordenada.setCoordenadaZ(z);
        } while (!validarCeldaAInsertarFicha(coordenada));

        this->tablero
            ->getCelda(
                coordenada.getCoordenadaX(),
                coordenada.getCoordenadaY(),
                coordenada.getCoordenadaZ()
            )
            ->getFicha()
            ->setJugadorOwner(jugadorOwner);

        this->tablero
            ->getCelda(
                coordenada.getCoordenadaX(),
                coordenada.getCoordenadaY(),
                coordenada.getCoordenadaZ()
            )
            ->getFicha()
            ->setTipo(tipoDeFicha);
    }
}

void TesoroBinario::cargarFichas() {
    int i = 0;
    this->jugadores->iniciarCursor();
    while (this->jugadores->avanzarCursor()) {
        this->cargarFichaDelTipo(this->jugadores->obtenerCursor()->getEspias(),Espia, i);
        this->cargarFichaDelTipo(this->jugadores->obtenerCursor()->getTesoros(), Tesoro, i);
        i++;
    }
}