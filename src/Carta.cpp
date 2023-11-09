#include <string>

#include "Carta.h"
#include "Tablero.h"
#include "Coordenadas.h"

Carta::Carta(TipoCarta carta) {
    this->cartaActiva = true;
    this->carta = carta;
}

void Carta::usarCarta(Tablero* tablero, Coordenada centro) {
    this->cartaActiva = false;
    switch (this->carta) {
        case Blindaje:
            // this->blindaje(tablero,centro);
            break;
        case Radar:
            // this->radar(tablero,centro);
            break;
        case PartirTesoro:
            // this->partirTesoro(tablero,centro);
            break;
    }
}

TipoCarta Carta::getTipoCarta() { return this->carta; }

std::string Carta::getStringTipoCarta() {
    std::string tipoDeCarta = "";

    switch (this->carta) {
        case Blindaje:
            tipoDeCarta = "Blindaje";
            break;
        case Radar:
            tipoDeCarta = "Radar";
            break;
        case PartirTesoro:
            tipoDeCarta = "Partir Tesoro";
            break;
    }
    return tipoDeCarta;
}

bool Carta::getCartaActiva() { return this->cartaActiva; }

std::string Carta::getStringTipoFicha(TipoContenido tipo) {
    std::string tipoDeCarta = "";

    switch (tipo) {
        case Espia:
            tipoDeCarta = "espia";
            break;
        case Tesoro:
            tipoDeCarta = "tesoro";
            break;
        default:
            tipoDeCarta = "vacio";
            break;
    }
    return tipoDeCarta;
}

// void Carta::blindaje(Tablero<Celda*>* tablero, Coordenada centro){
// }
// void Carta::radar(Tablero<Celda*>* tablero, Coordenada centro){
// }
// void Carta::partirTesoro(Tablero<Celda*>* tablero, Coordenada centro){
// }