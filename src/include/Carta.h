#include <string>
#include "Tablero.h"
#include "Celda.h"
#include "Enums.h"
#include "Coordenadas.h"
#include "TesoroBinario.h"
#include <map>

#ifndef __CARTA_H__
#define __CARTA_H__

class Carta{
    private:
        TipoCarta carta;
        bool cartaActiva;
        int radioAccion;

    public:

        //Post: construye una instancia de la clase carta
        Carta(TipoCarta carta);

        //Pre: recibe como parametro el tablero y el centro de accion
        //Post:Dependiendo del tipo de carta desencadenara la accion 
        void usarCarta(TesoroBinario* tesoroBinario, Tablero* tablero, Jugador* jugador);

        //Post:Permite saber cual es el tipo de carta
        TipoCarta getTipoCarta();

        //Post:devuelve un strung del tipo de carta
        std::string getStringTipoCarta();

        //Post:Permite saber si la carta esta activa
        bool getCartaActiva();

    private:
        //Avisa si hay Tesoros a la redonda
        void radar(Tablero* tablero, Jugador* jugador);

        // Inactiva la Celdad por turnos limitados
        void blindaje(Tablero* tablero, Jugador* jugador);

        //Parte una ficha "Tesoro" en dos fichas "TesoroPartido"
        // en dos casilleros distintos
        void partirTesoro(TesoroBinario* tesoroBinario, Tablero* tablero, Jugador* jugador);

        //Post: elimina la ficha del jugador e inactiva la celda en donde se produjo el encuentro
        void eliminarEspia(Tablero* tablero, Jugador* jugador);

        // Pre: 'jugador' debe estar inicializado
        // Post: 'jugador' no podra jugar en su proximo turno
        void omitirTurno(Jugador* jugador);

        // Pre: 'jugador' debe estar inicializado
        // Post: 'jugador' tendra un escudo activo
        void asignarEscudo(Jugador* jugador);

};

#endif
