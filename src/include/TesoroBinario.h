#ifndef TESOROBINARIO_H__
#define TESOROBINARIO_H__
#include "Tablero.h"
#include "Jugador.h"
#include "Lista.h"
#include "Enums.h"
#include "Coordenadas.h"
#include "Celda.h"


class TesoroBinario{
    private:
        Tablero* tablero;
        Lista<Jugador*>* jugadores;
        bool omitirTurno;
        int cantidadJugadores; //no hace falta guardarlo, se puede sacar de la long de la lista
        int turno;

    public:
        //Pre: cantidad debe ser al menos 2 y las dimensiones mayores a 1
        //Post: inicializa tablero con las dimensiones dadas y la cantidad de jugadores
        TesoroBinario(int cantidad, int x, int y, int z);
        
        //pre:
        //post: libera la memoria del juego
        ~TesoroBinario();

        //
        //post: imprime los tableros de todos los jugadores
        void imprimirTodosLosTableros();

        //pre:
        //post: imprime el tablero del jugador indicado
        void imprimirTablero(int jugador);

        //pre: -
        //post: solicita la cantidad de tesoros por jugador y permite a cada jugador colocar sus tesoros,
        //		si se intenta colocar un tesoro donde ya hay otro se le avisa y se pide otra posicion
        void cargarTesorosPorJugador();

        //
        //post: recibe posiciones hasta que la ingresada este en rango y y este activa
        void recibirPosicion(int* x, int* y, int* z);

        //pre
        //post: recibe por teclado las coordenadas y coloca el tesoro en la celda correspondiente
        void colocarTesoro(int x, int y, int z, int jugador);

        //
        // gestiona todo el desarrollo del juego hasta que algun jugador gane
        void juego();

        //
        // post: devuelve true en el caso de que el jugador recibido pueda seguir jugando, de lo contrario false. 
        bool sigueJugando(Jugador* jugador);

        //
        // post: realiza las evaluaciones correspondientes para ver si sigue el juego.
        //       devuelve true en caso de que el juego deba finalizar.
        bool finDeJuego();

        //pre: recibe el indice correspondiente al jugador del turno
        //post: gestiona cada turno
        void jugarTurno(Jugador* jugador);

        // pre: -
        // post: Recibe un jugador y mueve un tesoro
        void TesoroBinario::moverTesoro(Jugador* jugador);

        //
        //
        void colocarEspia(int jugador);

        //
        //post: avisa al jugador que se encontro el tesoro e inactiva la celda poniendo el contador de inactivo en 5
        //		Ademas le descuenta el tesoro al jugador que lo perdio.
        void encontrarTesoro(Celda* celda);

        //
        //post: elimina los espias del juego y deja la casilla vacia y sin dueño
        void eliminarEspias(Celda* celda);

        //Post: Gestiona la carga del tablero y los tesoros
        void cargarJuego();    

    private:
         //Post: Carga la cantidad de fichas a cada jugador
        void cargarCantidadesDeFichasAJugadores();

          // ----------Cargas de las fichas en el tablero------

        //Post: Carga las fichas de los jugadores
        void cargarFichas();

        //Pre: 'cantidadDeCarga', 'tipoDeFicha' y 'jugadorOwner' deben contener valores validos
        //Post: Carga la ficha en el tablero
        void cargarFichaDelTipo(int cantidadDeCarga, TipoContenido tipoDeFicha, int jugadorOwner);

        //Pre: 'coordenada' debe contener un valor valido y 'tipoDeFicha' debe estar inicializado
        //Post: Devuelve true si la celda esta vacia y se puede insertar la ficha
        bool validarCeldaAInsertarFicha(Coordenada cordenada);

        //Post: devuelve de forma aleatoria un tipo de Carta
        Carta* generarCarta();

        //Post: devuelve el tipo de carta dependiendo del indice que reciba
        TipoCarta obtenerTipoDeCarta(int indiceDeCarta);

        //Post: devuelve el tipo de carta dependiendo del indice que reciba
        int obtenerIndiceDeCarta(Jugador* jugador);

        //Pre: 'carta', 'jugador' y 'coordenada' deben contener un valor valido
        //Post: dependiendo del tipo de carta ejecuta la accion correspondiente
        void ejecutarCartaElegida(Carta* carta, Jugador* jugador, Coordenada coordenada);

        //Pre: 'jugador' y 'coordenada' deben contener un valor valido
        //Post:se genera una carta al azar y le da la opcion al usuario de usarla o no
        void tomarCartaDeMazo(Jugador* jugador, Coordenada coordenada);

        //Pre: 'mensaje' debe estar inicializado
        //Post: se genera una carta al azar y le da la opcion al usuario de usarla o no
        bool mensajeValido(std::string mensaje);
    
};
#endif /* TESOROBINARIO_H_ */
