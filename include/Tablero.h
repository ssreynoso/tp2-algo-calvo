#ifndef __TABLERO_H__
#define __TABLERO_H__
#include "Lista.h"
#include "Celda.h"
#include "Jugador.h"

class Tablero{
private:
	Lista<Lista<Lista<Celda*>*>*>* cubo;
	int x;
	int y;
	int z;

public:
    // PRE: Recibe 3 enteros positivos
    // POST: Construye un Tablero con las dimensiones especificadas
	// 		 y guarda en cada celda sus coordenadas
    Tablero(int x, int y, int z);

    //Pre: -
    //Post: libera la memoria asignada al tablero
    ~Tablero();

    // PRE: Recibe 3 enteros positivos como Coordenada
    // POST: Devuelve un puntero a la celda especificada
    Celda* getCelda(int x, int y, int z);

    //PRE: Devuelve el tamanio del tablero en X
    int getTamanioX();

    //PRE: Devuelve el tamanio del tablero en Y
    int getTamanioY();

    //PRE: Devuelve el tamanio del tablero en Z
    int getTamanioZ();

    //PRE: Recibe 3 enteros positivos como Coordenada
    //POST: Devuelve true si la coordenada esta dentro del tablero
    bool inRange(int x, int y, int z);

    // Pre: Recibe un puntero a jugador
    // Post: Imprime el tablero del jugador
    void imprimir(int numeroJugador);
};

#endif
