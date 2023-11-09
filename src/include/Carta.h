#include <string>
#include "Tablero.h"
#include "Celda.h"
#include "Enums.h"
#include "Coordenadas.h"
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
        void usarCarta(Tablero* tablero, Coordenada centro);

        //Post:Permite saber cual es el tipo de carta
        TipoCarta getTipoCarta();

        //Post:devuelve un strung del tipo de carta
        std::string getStringTipoCarta();

        //Post:Permite saber si la carta esta activa
        bool getCartaActiva();

    private:

        //Pre: recibe el contenido de una ficha
        //Post: devuelve un string  que describa el tipo de contenido
        std::string getStringTipoFicha(TipoContenido tipoFicha);
        
        //Avisa si hay Tesoros a la redonda
        bool radar(Tablero* tablero, Coordenada coord);

        // Inactiva la Celdad por turnos limitados
        void blindaje(Tablero* tablero, Coordenada coord);

        //Parte una ficha "Tesoro" en dos fichas "TesoroPartido"
        // en dos casilleros distintos
        void partirTesoro(Tablero* tablero, Coordenada coord);

        //Post: elimina la ficha del jugador e inactiva la celda en donde se produjo el encuentro
        void eliminarEspia(Tablero* tablero, Coordenada coord);


};

#endif
