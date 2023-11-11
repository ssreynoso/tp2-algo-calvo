#include "../include/TesoroBinario.h"
#include <iostream>
#include <string>

using namespace std;

TesoroBinario::TesoroBinario(int cantidad, int x, int y, int z) {
    // validar canidad y dimensiones

    this->tablero = new Tablero(x, y, z);
    this->jugadores = new Lista<Jugador*>();
    this->omitirTurno = false;

    for (int i = 0; i < cantidad; i++) {
        Jugador* jugador = new Jugador();
        this->jugadores->agregar(jugador);
        this->jugadores->obtener(i + 1)->setNumeroDeJugador(i + 1);
    }

    this->cantidadJugadores = cantidad;
    this->turno = 0;
}

TesoroBinario::~TesoroBinario() {
    this->jugadores->iniciarCursor();
    while (this->jugadores->avanzarCursor()) {
        delete this->jugadores->obtenerCursor();
    }
    delete this->tablero;
    delete this->jugadores;
}

void TesoroBinario::recibirPosicion(int* x, int* y, int* z) {
    std::cout << "plano: ";   std::cin >> *x;
	std::cout << "fila: ";    std::cin >> *y;
	std::cout << "columna: "; std::cin >> *z;

	if(!tablero->inRange(*x, *y, *z)) {
		std::cout << "Coordenadas fuera de rango, intentelo nuevamente" << std::endl;
		recibirPosicion(x, y, z);
	}

	if(!tablero->getCelda(*x,*y,*z)->estaActiva()) {
		std::cout << "La celda indicada esta inactiva" << std::endl;
		recibirPosicion(x, y, z);
	}
}