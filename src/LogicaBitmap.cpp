#include "../include/TesoroBinario.h"
#include "../include/Jugador.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// libreria bitmap
#include "../include/libreria/EasyBMP_1.06/EasyBMP.h"


//Creacion de canvas blanco de dimensiones del juego.
//Habria que hacer uno para cada jugador
void TesoroBinario::creacionCanvas(){

    //declaramos el operador Animage para referirnos a nuestra nueva imagen
    BMP AnImage;

    //asigamos tamaño
    //El ancho va a ser de: (x * 10) + constante de margen
    //El alto va a ser de: ((y + linea de separacion) * 10) * z + constante de margen
    int anchoCanvas, altoCanvas, altoPlanoIndividual;
    anchoCanvas = (this->tablero->getTamanioX()) + 4;
    altoPlanoIndividual = (this->tablero->getTamanioY()) + 1;
    altoCanvas = (altoPlanoIndividual * this->tablero->getTamanioZ() + 1);
    AnImage.SetSize(anchoCanvas, altoCanvas);
    //Set color depth a 8-bits
    AnImage.SetBitDepth(8);


    //Esta serie de iteraciones deja un canvas con planos vacios, mas margenes de color
    //Esta primer iteracion recorre el bmp
    for(int y = 0; y < altoCanvas; y++){

        //Recorre el bmp dejandolo blanco
        for(int x = 0; x < anchoCanvas; x++){

            AnImage(x, y)->Red = 255;
            AnImage(x, y)->Green = 255;
            AnImage(x, y)->Blue= 255;

        }

        //Recorre verticalmente dando un margen vertical de 2 pixeles
        AnImage(0, y)->Red = 78;
        AnImage(0, y)->Green = 184;
        AnImage(0, y)->Blue = 244;
        AnImage(anchoCanvas, y)->Red = 78;
        AnImage(anchoCanvas - 2, y)->Green = 184;
        AnImage(anchoCanvas - 2, y)->Blue = 244;
        AnImage(1, y)->Red = 78;
        AnImage(1, y)->Green = 184;
        AnImage(1, y)->Blue = 244;
        AnImage(anchoCanvas - 1, y)->Red = 78;
        AnImage(anchoCanvas - 1, y)->Green = 184;
        AnImage(anchoCanvas - 1, y)->Blue = 244;

    }

    //Itera cada  y = largo de planoIndividual, es decir, pinta la separacion entre planos
    for(int y = 0; y < altoCanvas + 1; y = y + altoPlanoIndividual){
        for(int x = 2; x < anchoCanvas - 2; x++){
            AnImage(x, y)->Red = 78;
            AnImage(x, y)->Green = 184;
            AnImage(x, y)->Blue = 244;
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

    AnImage(x + 2, (y + 1) + (this->tablero->getTamanioZ() + 1)* z)->Red = rojo;
    AnImage(x + 2, (y + 1) + (this->tablero->getTamanioZ() + 1)* z)->Green = green;
    AnImage(x + 2, (y + 1) + (this->tablero->getTamanioZ() + 1)* z)->Blue = blue;

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