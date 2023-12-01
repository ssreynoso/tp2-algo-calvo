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

const static int MULTIPLICADOR_DE_RESOLUCION = 1;
const static int ANCHO_DEL_MARGEN = 1 * MULTIPLICADOR_DE_RESOLUCION;
const static int ALTO_DEL_MARGEN = 1 * MULTIPLICADOR_DE_RESOLUCION;

//Creacion de canvas blanco de dimensiones del juego.
//Habria que hacer uno para cada jugador
void TesoroBinario::creacionCanvas(){
    visualizador->crearCanvas(cantidadJugadores);
}

//Esta va a ser una funcion que podamos llamar en cada momento que se requiera
//cambiar un o unos pixeles en especifico, asi no tenemos que reescribir el bitmap entero
void TesoroBinario::pintarPixel(std::string contenido, int numeroDeJugador , int x, int y, int z){
    visualizador->pintarPixel(contenido, numeroDeJugador, x, y, z);
}

void TesoroBinario::pintarActivoInactivo(int x, int y, int z, char caracter) {
    int alto_del_tablero = this->tablero->getTamanioY();
    x *= MULTIPLICADOR_DE_RESOLUCION;
    y *= MULTIPLICADOR_DE_RESOLUCION;

    int rojo, green, blue;
    //Seteo el color en negro
    if (caracter == '$'){
        rojo = 0;
        green = 0;
        blue = 0;
    } else{
        rojo = 255;
        green = 255;
        blue = 255;
    }

    for(unsigned int k = 0; k < this->jugadores->contarElementos(); k++){
        BMP AnImage;
        std::stringstream  ss;
        ss << k;
        std::string fila = ss.str();
        std::string  guardado = "sample" + fila + ".bmp";
        AnImage.ReadFromFile(guardado.c_str());

        for (int i = 0; i < MULTIPLICADOR_DE_RESOLUCION; ++i) {
            for (int j = 0; j < MULTIPLICADOR_DE_RESOLUCION; ++j) {
                AnImage(x + MULTIPLICADOR_DE_RESOLUCION + j, (y + MULTIPLICADOR_DE_RESOLUCION + i) + (alto_del_tablero+1)*MULTIPLICADOR_DE_RESOLUCION * (z))->Red = rojo;
                AnImage(x + MULTIPLICADOR_DE_RESOLUCION + j, (y + MULTIPLICADOR_DE_RESOLUCION + i) + (alto_del_tablero+1)*MULTIPLICADOR_DE_RESOLUCION * (z))->Green = green;
                AnImage(x + MULTIPLICADOR_DE_RESOLUCION + j, (y + MULTIPLICADOR_DE_RESOLUCION + i) + (alto_del_tablero+1)*MULTIPLICADOR_DE_RESOLUCION * (z))->Blue = blue;
            }
        }
        AnImage.WriteToFile(guardado.c_str());
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