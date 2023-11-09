#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "./include/Carta.h"
#include "./include/Celda.h"
#include "./include/Jugador.h"
#include "./include/TesoroBinario.h"
#include "./include/Utilidades.h"

Carta* TesoroBinario::generarCarta() {
    int numero     = rand() % 3;
    TipoCarta tipo = obtenerTipoDeCarta(numero);
    Carta* carta   = new Carta(tipo);

    return carta;
}

void TesoroBinario::ejecutarCartaElegida(
    Carta*     carta,
    Jugador*   jugador,
    Coordenada coordenada
) {
    carta->usarCarta(tablero, coordenada);
}
int TesoroBinario::obtenerIndiceDeCarta(Jugador* jugador) {
    int i = 0;
    int indiceDeCarta;
    bool esIndiceValido = false;

    while (!esIndiceValido) {
        // Ingreso de datos
        std::cout << "Ingrese el indice de la carta que quiere usar: "
                  << std::endl;
        std::cin >> indiceDeCarta;

        // Evaluación de índice
        bool estaEnRangoValido = (indiceDeCarta - 1 >= 0);
        bool estaEnRangoDeJugador =
            (indiceDeCarta - 1 < jugador->getCantidadDeCartas());

        esIndiceValido = estaEnRangoValido && estaEnRangoDeJugador;

        if (!esIndiceValido) {
            std::cout << "Ingrese un indice valido" << std::endl;
        }
    }

    return indiceDeCarta - 1;
}

void TesoroBinario::tomarCartaDeMazo(Jugador* jugador, Coordenada coordenada) {
    Carta* carta = this->generarCarta();
    jugador->agregarCarta(carta);
    std::cout << "Acaba de selecionar una carta del tipo: "
              << carta->getStringTipoCarta() << std::endl;

    bool respuesta = confirmar("¿Desea usar alguna Carta? Y/N: ");

    if (respuesta) {
        jugador->imprimirCartas();
        int indiceCarta = this->obtenerIndiceDeCarta(jugador);
        this->ejecutarCartaElegida(jugador->seleccionarCarta(indiceCarta),
                                   jugador, coordenada);
        jugador->removerCarta(indiceCarta);
        std::cout << "Carta ejecutada correctamente" << std::endl;
    }
}

TipoCarta TesoroBinario::obtenerTipoDeCarta(int indiceCarta) {
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
    }
    return tipo;
}