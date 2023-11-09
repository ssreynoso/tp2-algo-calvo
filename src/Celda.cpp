#include "Celda.h"

Celda::Celda() {
    this->activa = true;
    this->ficha = new Ficha();
    this->turnosInactiva = 0;
    this->coordenadas = new Coordenada();
}

Celda::~Celda(){
	delete this->ficha;
	delete this->coordenadas;
}

bool Celda::estaActiva() {
    return this->activa;
}

void Celda::setEstado(bool activa) {
    this->activa = activa;
}

void Celda::setFicha(Ficha* ficha){
	this->ficha = ficha;
}

Ficha* Celda::getFicha() {
    return this->ficha;
}

void Celda::setTurnosInactiva(int turnosInactiva){
    this->turnosInactiva = turnosInactiva;
}

int Celda::getTurnosInactiva(){
    return this->turnosInactiva;
}

void Celda::setCoordenada(int x, int y, int z){
	this->coordenadas->setCoordenadaX(x);
	this->coordenadas->setCoordenadaY(y);
	this->coordenadas->setCoordenadaZ(z);
}

Coordenada* Celda::getCoordenada(){
	return this->coordenadas;
}

// Desactiva la casilla por la canticad de turnos especificada

void Celda::desactivarCasillaPorTurnos(int cantidadDeTurnos) {
    this->activa = false;
    this->turnosInactiva = cantidadDeTurnos;
}