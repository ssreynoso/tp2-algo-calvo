#include "TesoroBinario.h"
#include "Jugador.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// libreria bitmap
#include "libreria/EasyBMP_1.06/EasyBMP.h"


//Creacion de canvas blanco de dimensiones del juego.
//Habria que hacer uno para cada jugador
void TesoroBinario::creacionCanvas(Jugador * jugador){

    //declaramos el operador Animage para referirnos a nuestra nueva imagen
    BMP AnImage;

    //asigamos tamaño
    //El ancho va a ser de: (x * 10) + constante de margen
    //El alto va a ser de: ((y + linea de separacion) * 10) * z + constante de margen
    int anchoCanvas, altoCanvas, altoPlanoIndividual;
    anchoCanvas = (this->tablero->getTamanioX() * 10);
    altoPlanoIndividual = this->tablero->getTamanioY() + 1;
    altoCanvas = ((altoPlanoIndividual) * this->tablero->getTamanioZ() * 10);
    AnImage.SetSize(anchoCanvas, altoCanvas);
    //Set color depth a 8-bits
    AnImage.SetBitDepth(8);

    //Itera para que cada pixel sea lanco
    for(int y = 0; y < altoCanvas; y++){

        for(int x = 0; x < anchoCanvas; x++){

            AnImage(x, y)->Red = 255;
            AnImage(x, y)->Green = 255;
            AnImage(x, y)->Blue= 255;

        }
    }

    //Buscar manera de crear un archivo con un nombre personalizado para el
    //numero de jugador

    /*
    int numeroDeJugador = jugador->getNumeroDeJugador();
    std::stringstream ss;
    ss << numeroDeJugador;
    std::string cambioIntStr= ss.str();

    std::string guardado = "sample" + cambioIntStr + ".bmp";
    AnImage.WriteToFile("sample.bmp");
     */

}

//Esta va a ser una funcion que podamos llamar en cada momento que se requiera
//cambiar un o unos pixeles en especifico, asi no tenemos que reescribir el bitmap entero
void TesoroBinario::pintarPixel(std::string contenido){

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