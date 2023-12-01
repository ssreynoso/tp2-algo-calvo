#include "include/TesoroBinario.h"

void TesoroBinario::juego() {
    this->jugadores->iniciarCursor();    //El cursor se inicia en NULL
    this->jugadores->ligarUltimoConPrimero();
    this->jugadores->avanzarCursor();    //Se avanza el cursor al primero
    while (!finDeJuego()) {
        Jugador* jugadorActual = this->jugadores->obtenerCursor();
        if (sigueJugando(jugadorActual)) {
            jugarTurno(jugadorActual);
        }
        this->jugadores->avanzarCursor();
    }
}

void TesoroBinario::imprimirTodosLosTableros() {
    for (int i = 1; i <= this->cantidadJugadores; i++) {
        this->tablero->imprimir(i);
    }
}

bool TesoroBinario::finDeJuego() {
    // El juego termina cuando todos los jugadores se quedan sin tesoros salvo uno, ganando este jugador
    int jugadoresConTesoro = 0;

    // Recorro todos los jugadores. El indice de la lista va de 1 a cantidadJugadores
    for (int i = 1; i <= this->cantidadJugadores; i++) {
        int numeroTesoros = this->jugadores->obtener(i)->getTesoros();
        // Tiene tesoros?
        if (numeroTesoros > 0) {
            jugadoresConTesoro++;
        }
    }

    return jugadoresConTesoro == 1;
}

bool TesoroBinario::sigueJugando(Jugador* jugador) {
    return jugador->getTesoros() > 0;
}

void TesoroBinario::jugarTurno(Jugador* jugador) {
    // Punto a)
    // logica cartas (levantar, jugar, guardar, ver disponibles)

    // Punto b)
    // colocarMina();

    // Punto c)
    // colocarEspia(jugador);

    // Punto d)
    moverTesoro(jugador);

    this->turno++;
}
