#ifndef __ENUMS_H__
#define __ENUMS_H__

//fichas
enum TipoContenido {
    Espia, 
    Tesoro,
    TesoroPartido,
	Mina,
    VACIO,
};

//cartas
enum TipoCarta {
    Blindaje,
    Radar,
    PartirTesoro,
};

//lista
enum Iteracion {
    SIGUIENTE, 
    FINAL, 
    ANTERIOR
};

#endif
