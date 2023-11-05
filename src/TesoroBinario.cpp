#include <map>
#include <string>
#include <cmath>
#include <cstdlib>
#include <time.h>

#include "./include/Tablero.h"
#include "./include/TesoroBinario.h"
#include "./include/Lista.h"
#include "./include/Jugador.h"
#include "./include/Enums.h"
#include "./include/Celda.h"
#include "./include/Carta.h"

using namespace std;

TesoroBinario::TesoroBinario(int cantidad){
    this->tablero = new Tablero<Celda*>(20,20,20);
    this->jugadores = new Lista<Jugador*>();
    this->omitirTurno=false;

    for(int i = 0; i < cantidad; i++){
        Jugador* jugador = new Jugador();
        this->jugadores->add(jugador);
    }

    this->cantidadJugadores = cantidad;
    this->turno = 0;
}

TesoroBinario::~TesoroBinario(){
    delete this->tablero;
    delete this->jugadores;
}

void TesoroBinario::cargarJuego() {
    this->cargarCantidadesDeFichasAJugadores();
    this->cargarFichas();
}



void TesoroBinario::cargarCantidadesDeFichasAJugadores(){
    for(int i = 0; i < this->jugadores->getSize(); i++) {
        this->jugadores->getLData(i)->setEspias(1), jugadores->getLData(i)->setTesoros(5);
    }    
}

bool TesoroBinario::validarCeldaAInsertarFicha(Coordenada cordenada) {
    TipoContenido tipo = this->tablero->getTData(cordenada.getCoordenadaX(),cordenada.getCoordenadaY(),cordenada.getCoordenadaZ())->getFicha()->getTipo();

    return (tipo == VACIO);
}


void TesoroBinario::cargarFichaDelTipo(int cantidadDeCarga, TipoContenido tipoDeFicha, int jugadorOwner){
    Coordenada cordenada;
    for (int i = 0; i <= cantidadDeCarga; i++){
        do{
            cordenada.setCoordenadaX(rand()% this->tablero->getTamanioX());
            cordenada.setCoordenadaY(rand()% this->tablero->getTamanioY());
            cordenada.setCoordenadaZ(rand()% this->tablero->getTamanioZ());
        } while (validarCeldaAInsertarFicha(cordenada));
        this->tablero->getTData(cordenada.getCoordenadaX(),cordenada.getCoordenadaY(),cordenada.getCoordenadaZ())->getFicha()->setJugadorOwner(jugadorOwner);
        this->tablero->getTData(cordenada.getCoordenadaX(),cordenada.getCoordenadaY(),cordenada.getCoordenadaZ())->getFicha()->setTipo(tipoDeFicha);
    }
}
        
void TesoroBinario::cargarFichas(){
    for (int i = 0; i < jugadores->getSize(); i++){
        this->cargarFichaDelTipo(jugadores->getLData(i)->getEspia(),Espia,i);
        this->cargarFichaDelTipo(jugadores->getLData(i)->getTesoro(),Tesoro,i);
    }
}


    

