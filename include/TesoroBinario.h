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

        //post: recibe posiciones hasta que la ingresada este en rango y y este activa
        void recibirPosicion(int* x, int* y, int* z);

        // Pre: Recibe un puntero a jugador
        // Post: Intenta realizar el movimiento de un tesoro.
        void moverTesoro(Jugador* jugador);

        // Pre: Recibe las coordenadas y un numero de jugador
        // Post: Coloca un tesoro en la posición determinada 
        void colocarTesoro(int x, int y, int z, int jugador);
        void colocarTesoro(Celda* celda, int jugador);

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

        //Pre: 'Debe estar inicializado tablero y ademas la celda por parametro debe tener un Espia'
        //Post: 'Eliminas los espias, resetea la celda, desactiva la celda
        //tantos turnos y hace perder un turno al jugador propietario del Espia'
        void explotarEspia(Celda *celda, Jugador *jugador);

        //Pre: 'Debe estar inicializado tablero y ademas la celda por parametro debe tener un Tesoro'
        //Post: 'Elimina cantidad de tesoros. Resetea la celda y desactiva la celda por tantos turnos'
        void explotarTesoro(Celda *celda, Jugador *jugador);

        //Pre: 'Debe estar inicializado tablero y adcional la celda por parametro debe tener un Mina'
        //Post: 'Resetea la celda y desactiva la celda por tantos turnos'
        void explotarMinas(Celda *celda);

        //Pre: 'Debe estar inicializado Tablero, con casillas disponibles'
        //Post: 'Coloca una ficha tipo Tesoro Mina'

        void colocarMina(int jugador);

        //Post: Gestiona la carga del tablero y los tesoros
        void cargarJuego();

        // Logica Bitmap?
        void creacionCanvas();

        void pintarPixel(std::string contenido, Jugador * jugador, int x, int y, int z);

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
        TipoCarta obtenerTipoCarta(int indiceDeCarta);

        //Post: devuelve el tipo de carta dependiendo del indice que reciba
        int obtenerIndiceCarta(Jugador* jugador);

        //Pre: 'carta', 'jugador' y 'coordenada' deben contener un valor valido
        //Post: dependiendo del tipo de carta ejecuta la accion correspondiente
        void ejecutarCartaElegida(Carta* carta, Jugador* jugador, Coordenada coordenada);

        //Pre: 'jugador' y 'coordenada' deben contener un valor valido
        //Post:se genera una carta al azar y le da la opcion al usuario de usarla o no
        void tomarCartaDeMazo(Jugador* jugador, Coordenada coordenada);

        //Pre: 'mensaje' debe estar inicializado
        //Post: se genera una carta al azar y le da la opcion al usuario de usarla o no
        bool mensajeValido(std::string mensaje);

        void escrituraArchivoDeTexto(std::string contenido);

        void reiniciarArchivoEscrito();
    
};
#endif /* TESOROBINARIO_H_ */
