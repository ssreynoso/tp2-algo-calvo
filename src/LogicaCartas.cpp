#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "include/Carta.h"
#include "include/Celda.h"
#include "include/Jugador.h"
#include "include/TesoroBinario.h"
#include "include/Utilidades.h"

Carta* TesoroBinario::generarCarta() {
    // int numero     = rand() % 3;
    // TipoCarta tipo = obtenerTipoCarta(numero);
    Carta* carta   = new Carta(PartirTesoro);

    return carta;
}

int TesoroBinario::obtenerIndiceCarta(Jugador* jugador) {
    int indiceDeCarta;
    bool esIndiceValido = false;

    while (!esIndiceValido) {
        // Ingreso de datos
        std::cout << "Ingrese el indice de la carta que quiere usar: ";
        std::cin >> indiceDeCarta;

        // Evaluación de índice
        bool estaEnRangoValido    = (indiceDeCarta > 0);
        bool estaEnRangoDeJugador = (indiceDeCarta <= jugador->getCantidadDeCartas());

        esIndiceValido = estaEnRangoValido && estaEnRangoDeJugador;

        if (!esIndiceValido) {
            std::cout << "Ingrese un indice valido" << std::endl;
        }
    }

    return indiceDeCarta;
}

void TesoroBinario::tomarCartaDeMazo(Jugador* jugador) {
    Carta* carta = this->generarCarta();

    // Si es de omitir turno ni siquiera agrega la carta al mazo
    if (carta->getTipoCarta() == OmitirTurno || carta->getTipoCarta() == Escudo) {
        carta->usarCarta(this, tablero, jugador);
        return;
    }

    jugador->agregarCarta(carta);
    std::cout << "La carta obtenida es del tipo: " << carta->getStringTipoCarta() << std::endl;

    bool respuesta = confirmar("¿Desea usar alguna Carta? Y/N: ");

    if (respuesta) {
        // Se muestran las cartas disponibles
        jugador->imprimirCartas();

        // Se pide el índice de la carta a usar
        int indiceCarta = this->obtenerIndiceCarta(jugador);

        // Se ejecuta la carta
        Carta* cartaSeleccionada = jugador->seleccionarCarta(indiceCarta);
        cartaSeleccionada->usarCarta(this, tablero, jugador);

        // Se remueve la carta del mazo
        jugador->removerCarta(indiceCarta);
        
        std::cout << "Carta ejecutada correctamente" << std::endl;
    }
}

TipoCarta TesoroBinario::obtenerTipoCarta(int indiceCarta) {
    TipoCarta tipo;
    switch (indiceCarta) {
        case Blindaje:
            tipo = Blindaje;
            break;
        case Radar:
            tipo = Radar;
            break;
        case PartirTesoro:
            tipo = PartirTesoro;
            break;
        case EliminarEspia:
            tipo = EliminarEspia;
            break;
        case OmitirTurno:
            tipo = OmitirTurno;
            break;
        case Escudo:
            tipo = Escudo;
            break;
    }
    return tipo;
}