#include "../include/TesoroBinario.h"
#include "../include/Jugador.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// libreria bitmap
#include "../include/libreria/EasyBMP_1.06/EasyBMP.h"
//#include "../inlcude/libreria/EasyBMP_1.06/EasyBmp.cpp"

const static int ANCHO_DEL_MARGEN = 2;
const static int MULTIPLICADOR_DE_RESOLUCION = 8;
const static int MARGEN_INFERIOR = 8;

//Creacion de canvas blanco de dimensiones del juego.
//Habria que hacer uno para cada jugador
void TesoroBinario::creacionCanvas(){

    //Ancho recibido por parametro, NO es constante
    int anchoDelTablero = this->tablero->getTamanioX();
    //Alto recibido por parametro, NO es constante
    int alto_del_tablero = this->tablero->getTamanioY();
    //Cantidad de tableros (profundidad)
    int cantidad_de_tableros = this->tablero->getTamanioZ();

    BMP AnImage;

    int anchoTotal, altoTotal, altoTablero, contadorDelMargenSuperior = 0;
    anchoTotal = (anchoDelTablero) + ANCHO_DEL_MARGEN;
    anchoTotal = anchoTotal * MULTIPLICADOR_DE_RESOLUCION;
    altoTablero = alto_del_tablero + 1;
    altoTablero = altoTablero * MULTIPLICADOR_DE_RESOLUCION;
    altoTotal = ((altoTablero) * cantidad_de_tableros ) + MARGEN_INFERIOR;

    AnImage.SetSize(anchoTotal, altoTotal);
    //Set color depth a 8-bits
    AnImage.SetBitDepth(8);


    //Esta serie de iteraciones deja un canvas con planos vacios, mas margenes de color
    //Esta primer iteracion recorre el bmp
    for(int y = 0; y < altoTotal; y++){

        //Recorre el bmp dejandolo blanco
        for(int x = 0; x < anchoTotal; x++){

            AnImage(x, y)->Red = 255;
            AnImage(x, y)->Green = 255;
            AnImage(x, y)->Blue= 255;

        }

        //Agregando margenes laterales
        for (int j = 0; j < MULTIPLICADOR_DE_RESOLUCION ; ++j) {

            AnImage(j, y)->Red = 78;
            AnImage(j, y)->Green = 184;
            AnImage(j, y)->Blue = 244;
            AnImage(anchoTotal - j - 1, y)->Red = 78;
            AnImage(anchoTotal - j - 1, y)->Green = 184;
            AnImage(anchoTotal - j - 1, y)->Blue = 244;

        }

        //Agregando margenes superiores
        if (y % altoTablero == 0 || contadorDelMargenSuperior > 0){
            for(int x = 8; x < anchoTotal - 8; x++){
                AnImage(x, y)->Red = 78;
                AnImage(x, y)->Green = 184;
                AnImage(x, y)->Blue = 244;
            }
            if (contadorDelMargenSuperior == 7){
                contadorDelMargenSuperior = 0;
            }else{
                contadorDelMargenSuperior++;
            }
        }

    }

    //Esta parte guarda una copia del tablero que acabamo de armar por cada jugador, siendo que empiezan todos igual
    //y mas tarde vamos a acceder a estos por el nombre.
    for(int i = 0; i < this->jugadores->contarElementos(); i++){

        //con esta parte, cada jugador va a tener su propio bmp al que acceder mas
        //tarde cuando juegue. Va a tener su numero de jugador en el nombre.
        int numeroDeJugador = i;
        std::stringstream ss;
        ss << numeroDeJugador;
        std::string fila = ss.str();
        std::string guardado = "sample" + fila + ".bmp";
        AnImage.WriteToFile(guardado.c_str());

    }
}

//Esta va a ser una funcion que podamos llamar en cada momento que se requiera
//cambiar un o unos pixeles en especifico, asi no tenemos que reescribir el bitmap entero
void TesoroBinario::pintarPixel(std::string contenido, Jugador * jugador, int x, int y, int z){

    BMP AnImage;
    int numeroDejugador = jugador->getNumeroDeJugador();
    std::stringstream  ss;
    ss << numeroDejugador;
    std::string fila = ss.str();
    std::string  guardado = "sample" + fila + ".bmp";
    AnImage.ReadFromFile(guardado.c_str());

    int alto_del_tablero = this->tablero->getTamanioY();
    x *= MULTIPLICADOR_DE_RESOLUCION;
    y *= MULTIPLICADOR_DE_RESOLUCION;

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
    } else if (contenido == "$"){
        rojo = 0;
        green = 0;
        blue = 0;
    } else if (contenido == "E"){
        rojo = 130;
        green = 130;
        blue = 130;
    } else {
        rojo = 78;
        green = 184;
        blue = 244;
    }

    for (int i = 0; i < MULTIPLICADOR_DE_RESOLUCION; ++i) {
        for (int j = 0; j < MULTIPLICADOR_DE_RESOLUCION; ++j) {
            AnImage(x + MULTIPLICADOR_DE_RESOLUCION + j, (y + MULTIPLICADOR_DE_RESOLUCION + i) + (alto_del_tablero+1)*MULTIPLICADOR_DE_RESOLUCION * (z))->Red = rojo;
            AnImage(x + MULTIPLICADOR_DE_RESOLUCION + j, (y + MULTIPLICADOR_DE_RESOLUCION + i) + (alto_del_tablero+1)*MULTIPLICADOR_DE_RESOLUCION * (z))->Green = green;
            AnImage(x + MULTIPLICADOR_DE_RESOLUCION + j, (y + MULTIPLICADOR_DE_RESOLUCION + i) + (alto_del_tablero+1)*MULTIPLICADOR_DE_RESOLUCION * (z))->Blue = blue;
        }
    }
    AnImage.WriteToFile(guardado.c_str());
}

//Escritura del archivo que copia la terminal
void TesoroBinario::escrituraArchivoDeTexto(std::string contenido){

    std::string nombreDeArchivo = "src/include/libreria/textoBitmap.txt";
    std::ofstream archivo;

    archivo.open(nombreDeArchivo.c_str(), std::fstream::app);

    if (archivo.is_open()) {
        if(contenido == "$"){
            archivo << std::endl;
        } else if (contenido == "+"){
            for(int i = 0; i < this->tablero->getTamanioX(); i++){
                archivo << "+";
            }
        } else {
            archivo << contenido;
        }

        //Con esta combinacion de $, + y contenido, nos quedaria un txt replica de la
        // terminal, separando los planos xy con una cadena de x * "+"
        //usamos fstream::app para que no reinicie el archivo, sino que le agregue algo.

        archivo.close();
    } else {
        std::cerr << "Error al abrir el archivo.\n";
    }
}

//Reseteo de archivo de texto
void TesoroBinario::reiniciarArchivoEscrito(){
    std::string nombreArchivo = "src/include/libreria/textoBitmap.txt";
    std::ofstream archivo;

    archivo.open(nombreArchivo.c_str(), std::fstream::out);
    archivo.close();
}