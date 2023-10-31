#include "./include/Celda.h"

Celda::Celda() {
    this->estado = true;
    this->ficha = Ficha();
}

bool Celda::getEstado() {
    return this->estado;
}

void Celda::setEstado(bool estado) {
    this->estado = estado;
}

Ficha* Celda::getFicha() {
    return &this->ficha;
}
Ficha Celda::getCopiaFicha() {
    return this->ficha;
}

void Celda::setTurnosInactiva(int turnosInactiva){
    this->turnosInactiva = turnosInactiva;
}

int Celda::getTurnosInactiva(){
    return this->turnosInactiva;
}