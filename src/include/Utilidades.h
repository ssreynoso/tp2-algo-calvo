#include <string>
#include "Jugador.h"
#include "Tablero.h"

// pre: recibe un texto
// post: devuelve true si el texto es "Y" o "N", false en caso contrario
bool confirmar(std::string mensaje);

// pre: recibe un numero
// post: devuelve el numero convertido a string
std::string toString(int numero);

// pre: recibe un jugador
// post: devuelve true si el jugador tiene escudo activo, false en caso contrario
bool controlarEscudoJugador(Jugador *jugador);

// pre: recibe un tablero y 3 punteros a enteros
//post: recibe posiciones hasta que la ingresada este en rango y y este activa
void recibirPosicion(Tablero* tablero, int* x, int* y, int* z);

// pre: recibe un tablero, un numero de jugador y un mensaje
// post: devuelve la coordenada de un tesoro propio
Coordenada* getTesoroPropio(Tablero* tablero, int numeroJugador, std::string mensaje);
