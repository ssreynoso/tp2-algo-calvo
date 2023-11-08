#include <iostream>
#include "./include/TesoroBinario.h"

void TesoroBinario::moverTesoro(Jugador* jugador) {
    int x, y, z;
    int numeroJugador = jugador->getNumeroDeJugador();
    Celda* celda = NULL;
    std::cout << "JUGADOR " << toString(numeroJugador) << " indique la posicion del tesoro a mover: " << std::endl;

    // Se busca un tesoro propio
    recibirPosicion(&x, &y, &z);
    celda = this->tablero->getCelda(x,y,z);
    while(!(celda->getFicha()->getTipo() == Tesoro && celda->getFicha()->getJugadorOwner() == numeroJugador)){
        std::cout << "No hay un tesoro en la celda indicada. Intentelo nuevamente" << std::endl;
        recibirPosicion(&x,&y,&z);
        celda = this->tablero->getCelda(x,y,z);
    }

    // Se pide una nueva posición
    std::cout << "JUGADOR " << toString(numeroJugador) << " Indique la nueva posicion del tesoro: " << std::endl;
    recibirPosicion(&x, &y, &z);
    celda = this->tablero->getCelda(x,y,z);

    // Chequeo celda inactiva
    while (!celda->estaActiva()) {
        std::cout << "Esta celda está inactiva, intente nuevamente" << std::endl;
        std::cout << "Indique la nueva posicion del tesoro: " << std::endl;
        recibirPosicion(&x, &y, &z);
        celda = this->tablero->getCelda(x,y,z);
    }

    // Si hay un tesoro, el juego le avisa al jugador para que mande un espía y lo pueda recuperar.
    if (celda->getFicha()->getTipo() == Tesoro) {
        std::cout << "Hay un tesoro enemigo en esta posición, envie un espía" << std::endl;
        // Pongo un return porque si ya le doy la información de que hay un tesoro enemigo
        // sería injusto que pueda intentar muchas veces con chances de encontrar múltiples tesoros enemigos. 
        return;
    }

    if (celda->getFicha()->getTipo() == Espia) {

    }
    
    // 
    colocarTesoro(x, y, z, numeroJugador);
}