#include "include/TesoroBinario.h"
#include "include/Ficha.h"
#include "include/Celda.h"
#include "include/Utilidades.h"
#include <iostream>

///Disminuye una unidad la cantidad de Espias del jugador, resetea la casilla y
///configura la cantidad de turnos desactivados. Finalmente omite el turno del jugador propietario;
void TesoroBinario::explotarEspia(Celda *celda, Jugador *jugador) {
    jugador->descontarEspias();
    celda->getFicha()->resetFicha();
    celda->desactivarCasillaPorTurnos(this, 2);
    jugador->setOmitirTurno(true);
}

///Disminuye una unidad la cantidad de Tesoros del jugador, resetea la casilla y
///configura la cantidad de turnos desactivados.
void TesoroBinario::explotarTesoro(Celda *celda, Jugador *jugador) {
    jugador->descontarTesoros();
    celda->desactivarCasillaPorTurnos(this, 3);
}

///Resetea la casilla y configura la cantidad de turnos desactivados.
void TesoroBinario::explotarMinas(Celda *celda) {
    std::cout << "Oh, encontraste una mina..."<< std::endl;
    std::cout << "Ambas minas explotaron y desactivaron la casilla por 5 Turnos"<< std::endl;
    celda->getFicha()->resetFicha();
    celda->desactivarCasillaPorTurnos(this, 5);
}


void TesoroBinario::colocarMina(int jugador){
    int plano, fila, columna;
    std::cout << "---------" << std::endl;
    std::cout << "Indique la posicion para Mina: " << std::endl;

    bool celdaActiva = false;

    // Verifico que la celda no tenga blindaje
    while(!celdaActiva){
        recibirPosicion(this->tablero, &plano, &fila, &columna);
        celdaActiva = this->tablero->getCelda(plano, fila, columna)->getTurnosInactiva() == 0;
        if(!celdaActiva){
            std::cout << "La celda esta inactiva, intente nuevamente" << std::endl;
        }
    }

    Celda *celdaActual = this->tablero->getCelda(plano, fila, columna);
    Ficha *ficha                = celdaActual->getFicha();
    Jugador *jugadorPropietario = this->jugadores->obtener(celdaActual->getFicha()->getJugadorOwner());

    if(ficha->getJugadorOwner() == jugador){
        std::cout << "Ya tienes una ficha en esta casilla" << std::endl;
        colocarMina(jugador);
    } else {
        switch (ficha->getTipo()){
            case VACIO:
                ficha->setJugadorOwner(jugador);
                ficha->setTipo(Mina);
                pintarPixel("M", jugador, fila, columna, plano);
                break;
            case Tesoro:
                if (controlarEscudoJugador(jugadorPropietario)) {
                    break;
                }
                //Si encuentra un tesoro entonces pierde el tesoro el jugador contrincante, dajando inactivo 3 turnos
                std::cout << "Eliminaste un tesoro del oponente: " << ficha->getJugadorOwner()<< std::endl;
                explotarTesoro(celdaActual,jugadorPropietario);
                pintarPixel("-", jugador, fila, columna, plano);
                break;
            case TesoroPartido:
                if (controlarEscudoJugador(jugadorPropietario)) {
                    break;
                }
                //Si encuentra un tesoro entonces pierde el tesoro el jugador contrincante, dajando inactivo 3 turnos
                std::cout << "Eliminaste un tesoro partido del oponente: " << ficha->getJugadorOwner()<< std::endl;
                explotarTesoro(celdaActual,jugadorPropietario);
                pintarPixel("-", jugador, fila, columna, plano);
                break;
            case Espia:
                std::cout << "Eliminaste un Espia. El dueño perdera un turno"<< std::endl;
                std::cout << "Se desactivo la casilla por 2 Turnos"<< std::endl;
                //Si encuentra un espia deja incactivo el casillero por 2 turno
                //Pierde el turno el dueño del espia
                explotarEspia(celdaActual, jugadorPropietario);
                break;
            case Mina:
                //Si encuentra otra minas, ambas explotan si se desactiva por 5 turnos
                explotarMinas(celdaActual);
                break;
        }
    }
}