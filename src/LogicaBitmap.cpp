#include "include/TesoroBinario.h"
#include "include/Jugador.h"
#include "include/Utilidades.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// libreria bitmap
#include "include/libreria/EasyBMP_1.06/EasyBMP.h"
//#include "../include/libreria/EasyBMP_1.06/EasyBmp.cpp"

//Creacion de canvas blanco de dimensiones del juego.
//Habria que hacer uno para cada jugador
void TesoroBinario::creacionCanvas()
{
    visualizador->crearCanvas(cantidadJugadores);
}

//Esta va a ser una funcion que podamos llamar en cada momento que se requiera
//cambiar un o unos pixeles en especifico, asi no tenemos que reescribir el bitmap entero
void TesoroBinario::pintarPixel(std::string contenido, int numeroDeJugador, int fila, int columna, int plano)
{
    visualizador->pintarPixel(contenido, numeroDeJugador, fila, columna, plano);
}

void TesoroBinario::pintarActivoInactivo(std::string caracter, int fila, int columna, int plano)
{
   
    for (int numeroJugador = 1; numeroJugador <= cantidadJugadores; numeroJugador++)
    {
        pintarPixel(caracter,numeroJugador,fila,columna,plano);
    }
}

/*
 * aplicar pintar pixel en:
 * TesoroBinario::moverTesoro()  de LogicaTesoros.cpp -- Listo
 * TesoroBinario::colocarEspia() y demas en LogicaEspias.cpp
 * TesoroBinario::colocarMina y demas en LogicaMinas.cpp
 * Cuando termina de deshabilitar el casillero
 * Faltan varias mas
 *
 */