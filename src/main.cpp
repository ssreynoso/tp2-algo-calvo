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

void dimensiones(int* x, int* y, int* z){
	cout << "Ingrese las dimensiones del tablero (x, y, z): " << endl;
	cout << "Cantidad de planos: ";
	recibirDimension(x);
	cout << "Filas: ";
	recibirDimension(y);
	cout << "Columnas: ";
	recibirDimension(z);
}

int main() {

    srand(time(NULL));

    int cantJugadores;
    NumeroJugadores(&cantJugadores);

    int x, y, z;
    dimensiones(&x, &y, &z);

    TesoroBinario *juego = new TesoroBinario(cantJugadores, x, y, z);

    juego->creacionCanvas();
    juego->cargarTesorosPorJugador();

    //TODO:Esto para que es? //Es para imprimir los tableros en consola, borrar antes de entregar
    juego->imprimirTodosLosTableros();

    juego->juego();


    delete juego;
    return 0;
}
