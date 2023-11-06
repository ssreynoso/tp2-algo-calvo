#include "./include/Carta.h"
#include "./include/Tablero.h"
#include "./include/Celda.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sstream>


using namespace std;

Carta::Carta(TipoCarta carta) {
    this->cartaActiva = true;
    this->radioAccion = -1;
    this->carta = carta;
}

 void Carta::usarCarta(Tablero* tablero, Coordenada centro){

    this->cartaActiva = false;

    switch(this->carta){
        case Blindaje:
            this->radioAccion = 4;
          
            break;
        case Radar:
            this->radioAccion = 5;
           
            break;
        case PartirTesoro:
            this->radioAccion = 3;
            break;
    }
}

TipoCarta Carta::getTipoCarta() {
    return this->carta;
}

string Carta::getStringTipoCarta(){
    string tipoDeCarta = "";

    switch (this->carta)
    {
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

bool Carta::getCartaActiva() {
    return this->cartaActiva;
}


string Carta::getStringTipoFicha(TipoContenido tipo){
    string tipoDeCarta= "";

    switch (tipo)
    {
    case Espia:
        tipoDeCarta= "espia";
        break;
    case Tesoro:
        tipoDeCarta= "tesoro";
        break;

    default:
        tipoDeCarta= "vacio";
        break;
    }
    return tipoDeCarta;
}



