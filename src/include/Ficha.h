#include "Enums.h"
#ifndef __FICHA_H__
#define __FICHA_H__

class Ficha{
    private:
        int jugadorOwner;
        int enumerador;
        TipoContenido tipo; 
    public:
        //Post: Contruye una instancia de la clase Ficha
        Ficha();

        //Pre: recibe el tipo de ficha que se quiere asignar
        //Post: asigna el tipo de ficha recibido
        void setTipo(TipoContenido tipo);

        //Post: devuelve el tipo de contenido que tiene la ficha
        TipoContenido getTipo();

        //Post: devuelve el identificador del jugador que es dueño de essa ficha
        int getJugadorOwner();

        //Pre:recibe el identificador del jugador que se asigna como dueño de la ficha
        //Post: asigna el identificador del owner ingresado
        void setJugadorOwner(int jugadorOwner);

        //Post: devuelve el identificador de la ficha
        int getNumFicha();

        //Pre: recibe el identificador de la ficha
        //Post: asigna el numero de la ficha recibido 
        void setNumFicha(int numero);
};
#endif