#include "include/TesoroBinario.h"
#include <iostream>
#include <string>

using namespace std;

const static int MULTIPLICADOR_DE_RESOLUCION = 24;

TesoroBinario::TesoroBinario(int cantidad, int planos, int filas, int columnas) {
    // validar canidad y dimensiones

    this->tablero = new Tablero(planos, filas, columnas);
    this->jugadores = new Lista<Jugador*>();
    this->omitirTurno = false;

    for (int i = 0; i < cantidad; i++) {
        Jugador* jugador = new Jugador();
        this->jugadores->agregar(jugador);
        this->jugadores->obtener(i + 1)->setNumeroDeJugador(i + 1);
    }

    this->cantidadJugadores = cantidad;
    this->turno = 0;
    this->visualizador = new Visualizador(filas, columnas, planos, MULTIPLICADOR_DE_RESOLUCION);
}

TesoroBinario::~TesoroBinario() {
    this->jugadores->iniciarCursor();
    while (this->jugadores->avanzarCursor()) {
        std::cout << "Se elimina el jugador " << this->jugadores->obtenerCursor()->getNumeroDeJugador() << std::endl;
        delete this->jugadores->obtenerCursor();
    }
    std::cout << "Se elimina el tablero" << std::endl;
    delete this->tablero;
    std::cout << "Se elimina el visualizador" << std::endl;
    delete this->visualizador;
    std::cout << "Se elimina la lista de jugadores" << std::endl;
    delete this->jugadores;
}