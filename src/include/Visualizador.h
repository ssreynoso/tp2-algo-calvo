#include <string>

class Visualizador {
private:
    int anchoCanvas;
    int altoCanvas;
    int anchoMargen;
    int altoMargen;
    int cantidadTableros;
    int multiplicadorResolucion;

public:
    Visualizador(int anchoTablero, int altoTablero, int cantidadTableros, int multiplicadorDeResolucion); 
    void crearCanvas(int cantidadJugadores);
    void pintarPixel(std::string contenido, int numeroDeJugador , int x, int y, int z);
};