#include "Ficha.h"
#include "Coordenadas.h"

#ifndef __CELDA_H__
#define __CELDA_H__

class Celda {
    private:
        bool activa;
        Ficha* ficha;
        int turnosInactiva;
        Coordenada* coordenadas;

    public:
        //Pre: no tiene
        //Post: crea una instancia de celda
        Celda();

        //Pre: -
        //Post: destructor default
        virtual ~Celda();

        //Pre: true para activa, false para inactiva
        //Post: asigna el estado pasado por parametro
        void setEstado(bool activa);
        
        //Pre: no tiene
        //Post: devuelve true si la celda esta activa y false si esta inactiva
        bool estaActiva();
        
        //Pre: recibe un puntero a la ficha a agregar
        //Post: coloca la ficha en la celda
        void setFicha(Ficha* ficha);

        //Pre:no tiene
        //Post:devuelve un puntero a la ficha que se encuentra dentro de la celda
        Ficha* getFicha();

        //Pre:recibe un numero con la cantidad de rondas que hay que dejar a la celda inactiva
        //Post: asigna la cantidad de rondas que la celda tiene que permancer inactiva
        void setTurnosInactiva(int turnosInactiva);

        //Pre: no tiene
        //Post: devuelve la cantidad de turnos que la celda debe permanecer inactiva
        int getTurnosInactiva();

        //Pre: recibe las coordenadas de la celda
        //Post guarda las coordenadas
        void setCoordenada(int x, int y, int z);

        //Pre: -
        //Post: devuelve un puntero a las coordenadas
        Coordenada* getCoordenada();

        //Pre: 'Debe existir la instancia Celda'
        //Post: 'Desactiva la casilla por la cantidad de turnos especificada'
        void desctivarCasillaPorTurnos(int cantidadDeTurnos);

};
#endif
