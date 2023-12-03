#include <string>

class Visualizador {
private:
    int cntFilas;
    int cntColumnas;
    int anchoCanvas;
    int altoCanvas;
    int anchoMargen;
    int altoMargen;
    int cantidadTableros;
    int multiplicadorResolucion;

public:
    Visualizador(int cntFilas, int cntColumnas, int cantidadTableros, int multiplicadorDeResolucion); 
    void crearCanvas(int cantidadJugadores);
    void pintarPixel(std::string contenido, int numeroDeJugador , int fila, int columna, int plano);
};