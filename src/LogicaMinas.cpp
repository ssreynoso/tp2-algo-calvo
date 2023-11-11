#include "TesoroBinario.h"
#include "Ficha.h"
#include "Celda.h"
#include <iostream>

///Disminuye una unidad la cantidad de Espias del jugador, resetea la casilla y
///configura la cantidad de turnos desactivados. Finalmente omite el turno del jugador propietario;
void TesoroBinario::explotarEspia(Celda *celda, Jugador *jugador) {
    jugador->descontarEspias();
    celda->getFicha()->resetFicha();
    celda->desactivarCasillaPorTurnos(2);
    jugador->setOmitirTurno(true);
    pintarActivoInactivo(celda->getCoordenada()->getCoordenadaX(), celda->getCoordenada()->getCoordenadaY(), celda->getCoordenada()->getCoordenadaZ(), '$');
}

///Disminuye una unidad la cantidad de Tesoros del jugador, resetea la casilla y
///configura la cantidad de turnos desactivados.
void TesoroBinario::explotarTesoro(Celda *celda, Jugador *jugador) {
    jugador->descontarTesoros();
    celda->desactivarCasillaPorTurnos(3);
    pintarActivoInactivo(celda->getCoordenada()->getCoordenadaX(), celda->getCoordenada()->getCoordenadaY(), celda->getCoordenada()->getCoordenadaZ(), '$');
}

///Resetea la casilla y configura la cantidad de turnos desactivados.
void TesoroBinario::explotarMinas(Celda *celda) {
    celda->getFicha()->resetFicha();
    celda->desactivarCasillaPorTurnos(5);
    pintarActivoInactivo(celda->getCoordenada()->getCoordenadaX(), celda->getCoordenada()->getCoordenadaY(), celda->getCoordenada()->getCoordenadaZ(), '$');
}


void TesoroBinario::colocarMina(int jugador){
    int x,y,z;
    std::cout << "JUGADOR. " << jugador << "Indique la posicion para Mina: " << std::endl;

    recibirPosicion(&x,&y,&z);
    Celda *celdaActual = this->tablero->getCelda(x,y,z);
    Ficha *ficha = celdaActual->getFicha();
    Jugador *jugadorPropietario = this->jugadores->obtener(celdaActual->getFicha()->getJugadorOwner());

    if(ficha->getJugadorOwner() == jugador){
        std::cout << "Ya tienes una ficha en esta casilla" << std::endl;
        colocarMina(jugador);
    }else{
        switch (ficha->getTipo()){

            case VACIO:
                ficha->setJugadorOwner(jugador);
                ficha->setTipo(Mina);
                pintarPixel("M", jugador, x, y, z);
                break;
            case Tesoro:
                //Si encuentra un tesoro entonces pierde el tesoro el jugador contrincante, dajando inactivo 3 turnos
                std::cout << "Eliminaste un tesoro del oponente: " << ficha->getJugadorOwner()<< std::endl;
                explotarTesoro(celdaActual,jugadorPropietario);
                pintarPixel("-", jugador, x, y, z);
                break;
            case TesoroPartido:
                //Si encuentra un tesoro entonces pierde el tesoro el jugador contrincante, dajando inactivo 3 turnos
                std::cout << "Eliminaste un tesoro partido del oponente: " << ficha->getJugadorOwner()<< std::endl;
                explotarTesoro(celdaActual,jugadorPropietario);
                pintarPixel("-", jugador, x, y, z);
                break;
            case Espia:
                std::cout << "Eliminaste un Espia. El dueño perdera un turno"<< std::endl;
                std::cout << "Se desactivo la casilla por 2 Turnos"<< std::endl;
                //Si encuentra un espia deja incactivo el casillero por 2 turno
                //Pierde el turno el dueño del espia
                explotarEspia(celdaActual, jugadorPropietario);

                break;
            case Mina:
                std::cout << "Oh, encontraste una mina..."<< std::endl;
                std::cout << "Ambas minas explotaron y desactivaron la casilla por 5 Turnos"<< std::endl;
                //Si encuentra otra minas, ambas explotan si se desactiva por 5 turnos
                explotarMinas(celdaActual);
                break;

        }
    }
}