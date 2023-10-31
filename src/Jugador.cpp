#include "iostream"
#include <string>

#include "./include/Jugador.h"
#include "./include/Carta.h"
#include "./include/Enums.h"

using namespace std;

Jugador::Jugador() {
    this->nombre = "";
    this->espias = 0;
    this->tesoros = 0;
    this->cartas = new Lista<Carta*>();
}

Jugador:: ~Jugador(){
    this->cartas->resetIter();
    for(int i = 0; i < this->cartas->getSize(); i++){
        delete this->cartas->getLData(i);
    }
    delete this->cartas;
}

string Jugador::getNombre() {
    return this->nombre;
}

int Jugador::getEspias() {
    return this->espias;
}

int Jugador::getTesoros() {
    return this->tesoros;
}


void Jugador::setNombre(string nombre) {
    this->nombre = nombre;
}

void Jugador::setEspia(int soldados) {
    this->espias = soldados;
}

void Jugador::setTesoro(int minas) {
    this->tesoros = tesoros;
}

void Jugador::agregarCarta(Carta* carta){
    this->cartas->add(carta);
}

void Jugador::imprimirCartas(){
    for(int i = 0; i < this->cartas->getSize(); i++){
        cout<< i+1 <<" Tipo De Carta: " <<this->cartas->getLData(i)->getStringTipoCarta()<<endl;
    }
}

Carta* Jugador::seleccionarCarta(int indiceCarta){
    return this->cartas->getLData(indiceCarta);
}

void Jugador::removerCarta(int indiceCarta){
    delete this->cartas->getLData(indiceCarta);
}

int Jugador::getCantidadDeCartas(){
    int cantidadDeCartas= 0;
    for(int i = 0; i < this->cartas->getSize(); i++){
        cantidadDeCartas++;
    }
    return cantidadDeCartas;
}