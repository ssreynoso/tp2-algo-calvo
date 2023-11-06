#ifndef __TABLERO_H__
#define __TABLERO_H__
#include "Lista.h"
#include "Celda.h"

class Tablero{
private:
	Lista<Lista<Lista<Celda*>*>*>* cubo;
	int x;
	int y;
	int z;

public:
    // PRE: Recibe 3 enteros positivos
    // POST: Construye un Tablero con las dimensiones especificadas
	// 		 y guarda en cada celda sus coordenadas
    Tablero(int x, int y, int z);

    //Pre: -
    //Post: libera la memoria asignada al tablero
    ~Tablero();

    // PRE: Recibe 3 enteros positivos como Coordenada
    // POST: Devuelve un puntero a la celda especificada
    Celda* getCelda(int x, int y, int z);

    //PRE: Devuelve el tamanio del tablero en X
    int getTamanioX();

    //PRE: Devuelve el tamanio del tablero en Y
    int getTamanioY();

    //PRE: Devuelve el tamanio del tablero en Z
    int getTamanioZ();

    //PRE: Recibe 3 enteros positivos como Coordenada
    //POST: Devuelve true si la coordenada esta dentro del tablero
    bool inRange(int x, int y, int z);


};

/*
template <class T> class Tablero {
    private:
        Lista<Lista<Lista<T>*>*>* cubo;
        int x;
        int y;
        int z;
        
    public:

        // PRE: Recibe 3 enteros positivos
        // POST: Construye un Tablero con las dimensiones especificadas
        Tablero(int x, int y, int z);

        ~Tablero();

        // PRE: Recibe 3 enteros positivos como Coordenada y el dato
        // POST: Setea el dato en la celda especificada
        void setDato(Coordenada coordenadas, T dato);

        // PRE: Recibe 3 enteros positivos como Coordenada
        // POST: Devuelve el dato de la celda especificada
        T getTData(int n, int m, int l);

        //PRE: Devuelve el tamanio del tablero en X
        int getTamanioX();

        //PRE: Devuelve el tamanio del tablero en Y
        int getTamanioY();

        //PRE: Devuelve el tamanio del tablero en Z
        int getTamanioZ();
        
        //PRE: Recibe 3 enteros positivos como Coordenada
        //POST: Devuelve true si la coordenada esta dentro del tablero
        bool inRange(int n, int m, int l);
        
    private:

        //PRE: Recibe 3 enteros positivos como Coordenada
        //POST: Setea la coordenada
        void setCoordenadas(int x, int y, int z);
};

template <class T> Tablero<T>::Tablero(int x, int y, int z) {
	//validar
	this->x = x;
	this->y = y;
	this->z = z;

	this->cubo = new Lista<Lista<Lista<T>*>*>();
    for (int i = 0; i < x; i++) {
        Lista<Lista<T>*>* plano = new Lista<Lista<T>*>();
        for (int j = 0; j < y; j++) {
            Lista<T>* fila = new Lista<T>();
            for (int k = 0; k < z; k++) {
                T* celda = new T();
                fila->agregar(*celda);
            }
            plano->agregar(fila);
        }
        cubo->agregar(plano);
    }
    setCoordenadas();
}

template <class T> Tablero<T>::~Tablero() {
	this->cubo->iniciarCursor();
	while(this->cubo->avanzarCursor()){
		Lista<Lista<T>*>* plano = this->cubo->obtenerCursor();
		plano->iniciarCursor();
		while(plano->avanzarCursor()){
			Lista<T>* fila = plano->obtenerCursor();
			fila->obtenerCursor();
			while(fila->avanzarCursor()){
				delete fila->obtenerCursor();
			}
			delete fila;
		}
		delete plano;
	}
	delete this->cubo;


    cubo->resetIter();
    int a = this->x, b = this->y, c = this->z;
    for(int i = 0; i < a; i++){
        cubo->getLData(i)->resetIter();
        for(int j = 0; j < b; j++){
            cubo->getLData(i)->getLData(j)->resetIter();
            for(int k = 0; k < c; k++){
                delete cubo->getLData(i)->getLData(j)->getLData(k);
            }
            delete cubo->getLData(i)->getLData(j);
        }
        delete cubo->getLData(i);
    }
    delete cubo;

}

template <class T> int Tablero<T>::getTamanioX() {
    return this->x;
}

template <class T> int Tablero<T>::getTamanioY() {
    return this->y;
}

template <class T> int Tablero<T>::getTamanioZ() {
    return this->z;
}

template <class T> void setDato(Coordenada coordenadas, T dato){


    //setCoordenada(n, m, l);

    //cubo->obtener(n)->obtener(m)->asignar(data, l);
    //this->cubo->getLData(n)->getLData(m)->getLData(l)->setNData(data);
}


template <class T> T Tablero<T>::getTData(int n, int m, int l){
    setCoordenada(n, m, l);
    return this->cubo->getLData(n)->getLData(m)->getLData(l);
}


template <class T> void Tablero<T>::setCoordenadas(){
	this->cubo->iniciarCursor();




	this->cubo->irANodo(n);
    this->cubo->getLData(m)->irANodo(m);
    this->cubo->getLData(m)->getLData(m)->irANodo(l);

}


template <class T> bool Tablero<T>::inRange(int n, int m, int l) {
    return (n >= 0 && n < this->x && m >= 0 && m < this->y && l >= 0 && l < this->z);
}
*/
#endif
