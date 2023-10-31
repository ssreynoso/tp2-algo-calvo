#include <iostream>
#include <string>
#include"./include/TesoroBinario.h"

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

int main(){
    
    int cantJugadores;
    NumeroJugadores(&cantJugadores);
    TesoroBinario* Juego = new TesoroBinario(cantJugadores);
    Juego->cargarJuego();
    return 0;
}