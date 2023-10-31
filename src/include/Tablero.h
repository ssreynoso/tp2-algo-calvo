#ifndef __TABLERO_H__
#define __TABLERO_H__
#include "Lista.h"
#include "Celda.h"

template <class T> class Tablero {
    private:
        Lista<Lista<Lista<T>*>*>* cubo;
        int x, y, z;
        
    public:

        // PRE: Recibe 3 enteros positivos
        // POST: Construye un Tablero con las dimensiones especificadas
        Tablero(int n, int m, int l);

        ~Tablero();

        // PRE: Recibe 3 enteros positivos como Coordenada y el dato
        // POST: Setea el dato en la celda especificada
        void setTData(int n, int m, int l, T data);

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
        void setCoordenada(int n, int m, int l);
};

template <class T> Tablero<T>::Tablero(int n, int m, int l) {
    this->x = n, this->y = m, this->z = l;
    cubo = new Lista<Lista<Lista<T>*>*>();
    for (int i = 0; i < n; i++) {
        Lista<Lista<T>*>* plano = new Lista<Lista<T>*>();
        for (int j = 0; j < m; j++) {
            Lista<T>* fila = new Lista<T>();
            for (int k = 0; k < l; k++) {
                Celda *celda = new Celda();
                fila->add(celda);
            }
            plano->add(fila);
        }
        cubo->add(plano);
    }
}

template <class T> Tablero<T>::~Tablero() {
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

template <class T> void Tablero<T>::setTData(int n, int m, int l, T data){
    setCoordenada(n, m, l);

    this->cubo->getLData(n)->getLData(m)->getLData(l)->setNData(data);
}

template <class T> T Tablero<T>::getTData(int n, int m, int l){
    setCoordenada(n, m, l);
    return this->cubo->getLData(n)->getLData(m)->getLData(l);
}

template <class T> void Tablero<T>::setCoordenada(int n, int m, int l){
    this->cubo->irANodo(n);
    this->cubo->getLData(m)->irANodo(m);
    this->cubo->getLData(m)->getLData(m)->irANodo(l);
}

template <class T> bool Tablero<T>::inRange(int n, int m, int l) {
    return (n >= 0 && n < this->x && m >= 0 && m < this->y && l >= 0 && l < this->z);
}

#endif