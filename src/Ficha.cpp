// Constructor
#include "./include/Ficha.h"

Ficha::Ficha() {
    this->tipo = VACIO;
    this->jugadorOwner = -1;
    this->enumerador = -1;
}

// Devuelve ID del jugador al que le pertenece la ficha
int Ficha::getJugadorOwner() {
    return this->jugadorOwner;
}

// Modifica el ID del jugador al que le pertenece la ficha
void Ficha::setJugadorOwner(int jugadorOwner) {
    this->jugadorOwner = jugadorOwner;
}

// Tipos que admite: ESPIA, TESORO y, VACIO.
// Modifica el tipo de fichea, se le debe pasar un enum { setTipo(TipoFicha) }
void Ficha::setTipo(TipoContenido tipo) {
    this->tipo = tipo;
}

// Devuelve el tipo enum de la ficha
TipoContenido Ficha::getTipo() {
    return this->tipo;
}

// Devuelve el número que identifica a la ficha de las otras del mismo tipo
int Ficha::getNumFicha(){
    return this->enumerador;
}

// Cambia el número que identifica a la ficha de las otras del mismo tipo
void Ficha::setNumFicha(int numero){
    this->enumerador = numero;
}