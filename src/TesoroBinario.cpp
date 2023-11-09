#include <map>
#include <string>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <iostream>

#include "./include/Tablero.h"
#include "./include/TesoroBinario.h"
#include "./include/Lista.h"
#include "./include/Jugador.h"
#include "./include/Enums.h"
#include "./include/Celda.h"
#include "./include/Carta.h"

// libreria bitmap
#include "./include/libreria/EasyBMP_1.06/EasyBMP.h"
#include <fstream>
#include <sstream>

using namespace std;

TesoroBinario::TesoroBinario(int cantidad, int x, int y, int z){
	//validar canidad y dimensiones

    this->tablero = new Tablero(x,y,z);
    this->jugadores = new Lista<Jugador*>();
    this->omitirTurno=false;

    for(int i = 0; i < cantidad; i++){
        Jugador* jugador = new Jugador();
        this->jugadores->agregar(jugador);
        this->jugadores->obtener(i+1)->setNumeroDeJugador(i+1);
    }

    this->cantidadJugadores = cantidad;
    this->turno = 0;
}

TesoroBinario::~TesoroBinario(){
	this->jugadores->iniciarCursor();
	while(this->jugadores->avanzarCursor()){
		delete this->jugadores->obtenerCursor();
	}
    delete this->tablero;
    delete this->jugadores;
}

void TesoroBinario::imprimirTodosLosTableros(){
	for(int i=1; i <= this->cantidadJugadores; i++){
		imprimirTablero(i);
	}
}

void TesoroBinario::imprimirTablero(int jugador){
	if(jugador <= 0 || jugador > this->cantidadJugadores){
		throw "El indice de jugador no es valido";
	}
	for(int i = 1; i <= this->tablero->getTamanioX(); i++){
		cout << "Plano " << i << endl;
		for(int j = 1; j <= this->tablero->getTamanioY(); j++){
			for(int k = 1; k <= this->tablero->getTamanioZ(); k++){
				string contenido;
				Celda* celda = this->tablero->getCelda(i, j, k);
				if(!celda->estaActiva()){
					contenido = " X ";
				}else{
					if(celda->getFicha()->getJugadorOwner() == jugador){
						switch (celda->getFicha()->getTipo()){
						case Espia:
							contenido = " E ";
							break;
						case Tesoro:
							contenido = " T ";
							break;
						case Mina:
							contenido = " M ";
							break;
						case VACIO:
							contenido = " - ";
							break;
						}
					}else{
						contenido = " - ";
					}
				}
				cout << contenido;
                this->escrituraArchivoDeTexto(contenido);
				}
			cout << endl;
            this->escrituraArchivoDeTexto("$");
			}
		cout << "\n----------\n";
        this->escrituraArchivoDeTexto("+");
		}
}

void TesoroBinario::cargarTesorosPorJugador(){
	int cantidadDeTesoros;
	cout << "Indicar la cantidad de tesoros por jugador: ";
	cin >> cantidadDeTesoros;
	while(cantidadDeTesoros <= 0){
		cout << "\nValor invalido, intentelo nuevamente: ";
		cin >> cantidadDeTesoros;
	}
	for(int i=1; i <= this->cantidadJugadores; i++){
		this->jugadores->obtener(i)->setTesoro(cantidadDeTesoros);
	}

	for(int i=0; i<cantidadDeTesoros; i++){
		for(int j=1; j <= this->cantidadJugadores; j++){
			int x,y,z;
			cout << "JUGADOR " << j << " indique la posicion del tesoro numero " << i+1 << " (plano,fila,columna): " << endl;

			recibirPosicion(&x, &y, &z);
			while(this->tablero->getCelda(x,y,z)->getFicha()->getTipo() == Tesoro){
				cout << "Ya hay un tesoro en la celda indicaca. Intentelo nuevamente" << endl;
				recibirPosicion(&x,&y,&z);
			}
			colocarTesoro(x, y, z, j);

		}
	}
}

void TesoroBinario::recibirPosicion(int* x, int* y, int* z){
	cout << "plano: ";
	cin >> *x;
	cout << "fila: ";
	cin >> *y;
	cout << "columna: ";
	cin >> *z;
	if(!this->tablero->inRange(*x,*y,*z)){
		cout << "Coordenadas fuera de rango, intentelo nuevamente" << endl;;
		recibirPosicion(x,y,z);
	}
	if(!this->tablero->getCelda(*x,*y,*z)->estaActiva()){
		cout << "La celda indicada esta inactiva" << endl;
		recibirPosicion(x,y,z);
	}
}

void TesoroBinario::colocarTesoro(int x, int y, int z, int jugador){
	this->tablero->getCelda(x,y,z)->getFicha()->setTipo(Tesoro);
	this->tablero->getCelda(x,y,z)->getFicha()->setJugadorOwner(jugador);
}

void TesoroBinario::juego(){
/*
	do{
		this->jugadores->iniciarCursor();
		while(this->jugadores->avanzarCursor()){
			if(sigueJugando(this->jugadores->obtenerCursor())){
				jugarTurno(this->jugadores->obtenerCursor()->getNumeroDeJugador())
			}
		}

	}while(!finDeJuego())
*/
}

void TesoroBinario::jugarTurno(int jugador){



	//logica cartas (levantar, jugar, guardar, ver disponibles)

	//colocarMina();
	//colocarEspia(jugador);
	//moverTesoro();




	this->turno++;
}

void TesoroBinario::colocarEspia(int jugador){
	int x,y,z;
	cout << "Indique la posicion para el espia: " << endl;
	recibirPosicion(&x,&y,&z);

	Ficha* ficha = this->tablero->getCelda(x,y,z)->getFicha();
	if(ficha->getJugadorOwner() == jugador){
		cout << "Ya tienes una ficha en esta casilla" << endl;
		colocarEspia(jugador);
	}else{
		switch (ficha->getTipo()){
		case VACIO:
			ficha->setJugadorOwner(jugador);
			ficha->setTipo(Espia);
			this->jugadores->obtener(jugador)->incrementarEspias();
			break;
		case Tesoro:
			encontrarTesoro(this->tablero->getCelda(x,y,z));
			break;
		case Espia:
			eliminarEspias(this->tablero->getCelda(x,y,z));
			break;
		case Mina:
			//pierdeTurno;
			break;
		}
	}
}

void TesoroBinario::encontrarTesoro(Celda* celda){
	cout << "Tu espia encontro un tesoro enemigo. La casilla quedara inactiva por 5 turnos" << endl;
	celda->setEstado(false);
	celda->setTurnosInactiva(5);
	//descuento en 1 los tesoros del otro jugador
	this->jugadores->obtener(celda->getFicha()->getJugadorOwner())->descontarTesoros();
}

void TesoroBinario::eliminarEspias(Celda* celda){
	cout << "Tu espia se encontro con un espia enemigo. Ambos son eliminados del juego" << endl;
	//descuento en 1 los espias del otro jugador
	this->jugadores->obtener(celda->getFicha()->getJugadorOwner())->descontarTesoros();
	//vacio la celda
	celda->getFicha()->setTipo(VACIO);
	celda->getFicha()->setJugadorOwner(-1);
}




//
//Pruebas con carga aleatoria
//
void TesoroBinario::cargarJuego() {
    this->cargarCantidadesDeFichasAJugadores();
    cout << this->jugadores->obtener(1)->getEspias() <<endl;
    this->cargarFichas();
    //this->tablero->getCelda(3,3,3)->getFicha()->setTipo(Tesoro);
    cout << "fichas cargadas"<<endl;
}

void TesoroBinario::cargarCantidadesDeFichasAJugadores(){
	this->jugadores->iniciarCursor();
	while(this->jugadores->avanzarCursor()){
		this->jugadores->obtenerCursor()->setEspia(1);
		this->jugadores->obtenerCursor()->setTesoro(1);
	}
}


bool TesoroBinario::validarCeldaAInsertarFicha(Coordenada coordenada){
	TipoContenido tipo = this->tablero->getCelda(coordenada.getCoordenadaX(), coordenada.getCoordenadaY(), coordenada.getCoordenadaZ())->getFicha()->getTipo();

    return (tipo == VACIO);
}

void TesoroBinario::cargarFichaDelTipo(int cantidadDeCarga, TipoContenido tipoDeFicha, int jugadorOwner){
    Coordenada coordenada;
    for (int i = 0; i < cantidadDeCarga; i++){
        do{
        	int x,y,z;
        	x=rand()% this->tablero->getTamanioX() + 1;
        	y=rand()% this->tablero->getTamanioY() + 1;
        	z=rand()% this->tablero->getTamanioZ() + 1;
        	cout << x << y << z << endl;
            coordenada.setCoordenadaX(x);
            coordenada.setCoordenadaY(y);
            coordenada.setCoordenadaZ(z);
        } while (!validarCeldaAInsertarFicha(coordenada));
        this->tablero->getCelda(coordenada.getCoordenadaX(),coordenada.getCoordenadaY(),coordenada.getCoordenadaZ())->getFicha()->setJugadorOwner(jugadorOwner);
        this->tablero->getCelda(coordenada.getCoordenadaX(),coordenada.getCoordenadaY(),coordenada.getCoordenadaZ())->getFicha()->setTipo(tipoDeFicha);
    }
}

void TesoroBinario::cargarFichas(){
	int i = 0;
	this->jugadores->iniciarCursor();
	while(this->jugadores->avanzarCursor()){
		this->cargarFichaDelTipo(this->jugadores->obtenerCursor()->getEspias(), Espia, i );
		this->cargarFichaDelTipo(this->jugadores->obtenerCursor()->getTesoros(), Tesoro, i);
		i++;
	}
}

TipoCarta TesoroBinario::obtenerTipoCarta(int indiceCarta){
    TipoCarta tipo;
    switch (indiceCarta)
    {
    case Blindaje:
        tipo = Blindaje;
        break;
    case Radar:
        tipo = Radar;
        break;
    case PartirTesoro:
        tipo = PartirTesoro;
        break;
    }
    return tipo;
}

Carta* TesoroBinario::generarCarta(){
    int numero = rand() % 3;
    TipoCarta tipo = obtenerTipoCarta(numero);
    Carta* carta= new Carta(tipo);
    return carta;
}

void TesoroBinario::ejecutarCartaElegida(Carta* carta, Jugador* jugador,Coordenada coordenada){
    carta->usarCarta(tablero, coordenada);
} 
bool TesoroBinario::mensajeValido(std::string mensaje){
    return (mensaje == "Y" || mensaje == "N");
}
int TesoroBinario::obtenerIndiceDeCarta(Jugador* jugador){
    int i = 0;
    int indiceDeCarta;
    while(i !=-1){
        cout<<"Ingrese el indice de la carta que quiere usar: "<<endl;
        cin >> indiceDeCarta;
        if( (indiceDeCarta -1 >= 0) && (indiceDeCarta -1  < jugador->getCantidadDeCartas()) ){
            i= -1;
        }else{
            cout<<"Ingrese un indice valido"<<endl;
        }
    }
    return indiceDeCarta-1;
}
void TesoroBinario::tomarCartaDeMazo(Jugador* jugador, Coordenada coordenada){
    Carta*  carta = this->generarCarta();
    jugador->agregarCarta(carta);
    cout<<"Acaba de selecionar una carta del tipo: " << carta->getStringTipoCarta()<<endl;
    string respuesta = "";
    
    while(!mensajeValido(respuesta)){
        cout<<"¿Desea usar alguna Carta? Y/N: "<<endl;
        cin>>respuesta;
    }  

    if(respuesta == "Y"){
        jugador->imprimirCartas();
        int indiceCarta = this->obtenerIndiceDeCarta(jugador);
        this->ejecutarCartaElegida(jugador->seleccionarCarta(indiceCarta),jugador,coordenada);
        jugador->removerCarta(indiceCarta);
        cout<<"Carta ejecutada correctamente"<<endl;
    }
}



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
    string cambioIntStr= ss.str();

    string guardado = "sample" + cambioIntStr + ".bmp";
    AnImage.WriteToFile("sample.bmp");
     */

}

//Esta va a ser una funcion que podamos llamar en cada momento que se requiera
//cambiar un o unos pixeles en especifico, asi no tenemos que reescribir el bitmap entero
void TesoroBinario::pintarPixel(string contenido){

}

//Escritura del archivo que copia la terminal
void TesoroBinario::escrituraArchivoDeTexto(string contenido){

    string nombreDeArchivo = "src/include/libreria/textoBitmap.txt";
    ofstream archivo;

    archivo.open(nombreDeArchivo.c_str(), fstream::app);

    if(contenido == "$"){
        archivo << endl;
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
}

//Reseteo de archivo de texto
void TesoroBinario::reiniciarArchivoEscrito(){
    string nombreArchivo = "src/include/libreria/textoBitmap.txt";
    ofstream archivo;

    archivo.open(nombreArchivo.c_str(), fstream::out);
    archivo.close();
}