#ifndef __COORDENADAS_H__
#define __COORDENADAS_H__

class Coordenada {
    private:
        int coordX,coordY,coordZ;

    public:
        //post: inicializa las coordenadas en el origen
        Coordenada();

        //pre: 'x' debe esta inicializado
        //post: asigna el valor recibido a 'coordX'
        void setCoordenadaX(int x);

        //pre: 'y' debe esta inicializado
        //post: asigna el valor recibido a 'coordY'
        void setCoordenadaY(int y);

        //pre: 'z' debe esta inicializado
        //post: asigna el valor recibido a 'coordZ'
        void setCoordenadaZ(int z);

        //post: devuelve coordX
        int getCoordenadaX();
        
        //post: devuelve coordX
        int getCoordenadaY();

        //post: devuelve coordX
        int getCoordenadaZ();
};

#endif