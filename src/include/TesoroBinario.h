#ifndef TESOROBINARIO_H__
#define TESOROBINARIO_H__
#include "Tablero.h"
#include "Jugador.h"
#include "Lista.h"
#include "Enums.h"
#include "Coordenadas.h"
#include "Celda.h"

class TesoroBinario{
    private:
        Tablero<Celda*>* tablero;
        Lista<Jugador*>* jugadores;
        bool omitirTurno;
        int cantidadJugadores;
        int turno;
    public:
        // Inicializa tablero y jugadores
        TesoroBinario(int cantidad);
        
        ~TesoroBinario();

        //Post: Gestiona la carga del tablero y los tesoros
        void cargarJuego();    

    private:
         //Post: Carga la cantidad de fichas a cada jugador
        void cargarCantidadesDeFichasAJugadores();

          // ----------Cargas de las fichas en el tablero------

        //Post: Carga las fichas de los jugadores
        void cargarFichas();

        //Pre: 'cantidadDeCarga', 'tipoDeFicha' y 'jugadorOwner' deben contener valores validos
        //Post: Carga la ficha en el tablero
        void cargarFichaDelTipo(int cantidadDeCarga, TipoContenido tipoDeFicha, int jugadorOwner);

        //Pre: 'coordenada' debe contener un valor valido y 'tipoDeFicha' debe estar inicializado
        //Post: Devuelve true si la celda esta vacia y se puede insertar la ficha
        bool validarCeldaAInsertarFicha(Coordenada cordenada, TipoContenido tipoDeFicha);


    
};
#endif /* TESOROBINARIO_H_ */