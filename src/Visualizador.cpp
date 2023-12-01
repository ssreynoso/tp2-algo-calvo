#include "include/TesoroBinario.h"
#include "include/Jugador.h"
#include "include/Utilidades.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// libreria bitmap
#include "include/libreria/EasyBMP_1.06/EasyBMP.h"

using namespace std;

const static int ANCHO_DEL_MARGEN = 1;
const static int ALTO_DEL_MARGEN  = 1;

Visualizador::Visualizador(
    int anchoTablero,
    int altoTablero,
    int cantidadTableros,
    int multiplicadorDeResolucion
) {
    this->anchoCanvas             = (anchoTablero + (2 * ANCHO_DEL_MARGEN)) * multiplicadorDeResolucion;
    // Dejar solo un margen en medio de cada plano
    this->altoCanvas              = ((altoTablero + (2 * ALTO_DEL_MARGEN)) * cantidadTableros) * multiplicadorDeResolucion;
    this->anchoMargen             = ANCHO_DEL_MARGEN * multiplicadorDeResolucion;
    this->altoMargen              = ALTO_DEL_MARGEN * multiplicadorDeResolucion;
    this->cantidadTableros        = cantidadTableros;
    this->multiplicadorResolucion = multiplicadorDeResolucion;
}

void Visualizador::crearCanvas(int cantidadJugadores) {
    BMP AnImage;

    AnImage.SetSize(anchoCanvas, altoCanvas);
    //Set color depth a 8-bits
    AnImage.SetBitDepth(8);


    //Esta serie de iteraciones deja un canvas con planos vacios, mas margenes de color
    //Esta primer iteracion recorre el bmp

    //Recorre el bmp dejandolo blanco
    for(int y = 0; y < altoCanvas; y++){
        for(int x = 0; x < anchoCanvas; x++){
            AnImage(x, y)->Red = 255;
            AnImage(x, y)->Green = 255;
            AnImage(x, y)->Blue= 255;
        }
    }

    // Agrego márgenes
    for(int y = 0; y < altoCanvas; y++){
        for(int x = 0; x < anchoCanvas; x++){
            bool esMargenSuperior = y < altoMargen || y >= altoCanvas - altoMargen;
            bool esMargenLateral = x < anchoMargen || x >= anchoCanvas - anchoMargen;
            bool esSeparador = y % (altoCanvas / cantidadTableros) == 0;

            if (esMargenLateral || esMargenSuperior){
                AnImage(x, y)->Red = 78;
                AnImage(x, y)->Green = 184;
                AnImage(x, y)->Blue = 244;
            }
        }
    }

    //Esta parte guarda una copia del tablero que acabamo de armar por cada jugador, siendo que empiezan todos igual
    //y mas tarde vamos a acceder a estos por el nombre.
    for(int i = 0; i < cantidadJugadores; i++){

        //con esta parte, cada jugador va a tener su propio bmp al que acceder mas
        //tarde cuando juegue. Va a tener su numero de jugador en el nombre.
        int numeroDeJugador = i;
        std::string guardado = "sample" + toString(numeroDeJugador) + ".bmp";
        AnImage.WriteToFile(guardado.c_str());
    }
}


//Esta va a ser una funcion que podamos llamar en cada momento que se requiera
//cambiar un o unos pixeles en especifico, asi no tenemos que reescribir el bitmap entero
void Visualizador::pintarPixel(std::string contenido, int numeroDeJugador , int x, int y, int z){
    numeroDeJugador--;

    BMP AnImage;
    std::string  guardado = "sample" + toString(numeroDeJugador) + ".bmp";
    AnImage.ReadFromFile(guardado.c_str());

    /*
     * Listado colores:
     * Blanco: vacio
     * Gris: Espia
     * Rojo: Mina
     * Amarillo: Tesoro
     * Naranja: TesoroPartido
     * Negro: Inhablitado
     * Celeste: Fuera del tablero
     */

    int rojo, green, blue;
    if(contenido == "T"){
        rojo = 248;
        green = 255;
        blue = 32;
    } else if (contenido == "T/2"){
        rojo = 255;
        green = 136;
        blue = 25;
    } else if (contenido == "M"){
        rojo = 255;
        green = 0;
        blue = 0;
    } else if (contenido == "-"){
        rojo = 255;
        green = 255;
        blue = 255;
    } else if (contenido == "E"){
        rojo = 130;
        green = 130;
        blue = 130;
    } else {
        rojo = 78;
        green = 184;
        blue = 244;
    }

    int _y = y * multiplicadorResolucion;
    int _x = x * multiplicadorResolucion;
    for (int j = _y; j < _y + multiplicadorResolucion; j++) {
        for (int i = _x; i < _x + multiplicadorResolucion; i++) {
            AnImage(i, j)->Red = rojo;
            AnImage(i, j)->Green = green;
            AnImage(i, j)->Blue = blue;
        }
    }

    AnImage.WriteToFile(guardado.c_str());
}