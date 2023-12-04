#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include"include/TesoroBinario.h"

using namespace std;
void NumeroJugadores(int* cantJugadores){
    cout << "****-----------****--------------****\n";
    cout << "*         Bienvenido               *\n";
    cout << "****-----------****-------------****\n";

    cout << "Ingrese el número de jugadores (2<número<5): ";
    cin >> *cantJugadores;
    while(*cantJugadores < 2 || *cantJugadores > 5){
        cout << "Rango Inválido. Ingrese nuevamente: ";
        cin >> *cantJugadores;
    }
}

void recibirDimension(int* valor){
	cin >> *valor;
	while(*valor <= 0){
		cout << "La dimension no es valida intente nuevamente: ";
		cin >> *valor;
	}
}

void dimensiones(int* planos, int* filas, int* columnas){
	cout << "Ingrese las dimensiones del tablero: " << endl;
	cout << "Cantidad de planos: ";
	recibirDimension(planos);
	cout << "Filas: ";
	recibirDimension(filas);
	cout << "Columnas: ";
	recibirDimension(columnas);
}

int main() {

    srand(time(NULL));

    int cantJugadores;
    NumeroJugadores(&cantJugadores);

    int planos, filas, columnas;
    dimensiones(&planos, &filas, &columnas);

    TesoroBinario *juego = new TesoroBinario(cantJugadores, planos, filas, columnas);

    juego->creacionCanvas();
    juego->cargarTesorosPorJugador();

    //TODO:Esto para que es? //Es para imprimir los tableros en consola, borrar antes de entregar
    juego->imprimirTodosLosTableros();

    juego->juego();

    delete juego;
    return 0;
}
