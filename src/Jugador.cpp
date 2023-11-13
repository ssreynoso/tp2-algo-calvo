#include "Jugador.h"
#include <string>
#include "Carta.h"
#include "Enums.h"
#include "Lista.h"
#include "iostream"

Jugador::Jugador() {
    this->nombre = "";
    this->escudoActivo = false;
    this->numeroDeJugador = 0;
    this->espias = 0;
    this->tesoros = 0;
    this->cartas = new Lista<Carta*>();
    this->omitirTurno = false;
}

Jugador::~Jugador() {
    this->cartas->iniciarCursor();
    while (this->cartas->avanzarCursor()) {
        delete this->cartas->obtenerCursor();
    }
    delete this->cartas;
}

std::string Jugador::getNombre() { return this->nombre; }

int Jugador::getNumeroDeJugador() { return this->numeroDeJugador; }

int Jugador::getEspias() { return this->espias; }

int Jugador::getTesoros() { return this->tesoros; }

void Jugador::setNombre(std::string nombre) { this->nombre = nombre; }

void Jugador::setNumeroDeJugador(int numeroDeJugador) {
    this->numeroDeJugador = numeroDeJugador;
}

void Jugador::setEspia(int soldados) { this->espias = soldados; }

void Jugador::setTesoro(int minas) { this->tesoros = minas; }

void Jugador::incrementarTesoros() { this->tesoros++; }

void Jugador::descontarTesoros() { this->tesoros--; }

void Jugador::incrementarEspias() { this->espias++; }

void Jugador::descontarEspias() { this->espias--; }

void Jugador::agregarCarta(Carta* carta) { this->cartas->agregar(carta); }

void Jugador::imprimirCartas() {
    this->cartas->iniciarCursor();
    int i = 1;
    while (this->cartas->avanzarCursor()) {
        std::cout << i << " Tipo de carta: "
                  << this->cartas->obtenerCursor()->getStringTipoCarta()
                  << std::endl;
    }
}

Carta* Jugador::seleccionarCarta(int indiceCarta) {
    // validar
    return this->cartas->obtener(indiceCarta);
}

void Jugador::removerCarta(int indiceCarta) {
    // validar

    // se elimina la carta
    Carta* aRemover = this->cartas->obtener(indiceCarta);
    delete aRemover;

    // elimina el nodo de la lista y une el anterior con el siguiente
    this->cartas->remover(indiceCarta);
}

int Jugador::getCantidadDeCartas() { return this->cartas->contarElementos(); }

void Jugador::setOmitirTurno(bool estado) { this->omitirTurno = estado; }

bool Jugador::getOmitirTurno() { return this->omitirTurno; }

void Jugador::desactivarEscudo() { this->escudoActivo = false; }

void Jugador::activarEscudo() { this->escudoActivo = true; }
