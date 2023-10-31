#include <iostream>
#include "Nodo.h"
#include "Enums.h"

#ifndef __LISTA_H__
#define __LISTA_H__

template <class T> class Lista {
private:
	Nodo<T>* primero;
	Nodo<T>* iterador;
	int size;
	int iteracion;
	
public: 

	Lista();

	~Lista();

	// PRE: Recibe un entero positivo
	// POST: Itera el cursor de la lista hasta el entero recibido
	void irANodo(int x);	



	// POST: Reinicia el iterador en la primer posicion
	void resetIter();

	// PRE: Recibe un dato generico
	// POST: Y lo asigna al nodo del iterador
	void assign(T data);

	// POST: Devuelve el nodo del iterador
	Nodo<T>* getNodo();

	// PRE: Recibe un entero positivo
	// POST: Obtiene el dato del nodo del iterador
	T getLData(int x);

	// PRE: Recibe un dato generico
	// POST: Crea un nuevo nodo al final de la lista
	void add(T data);

	// POST: Obtiene la posicion del iterador
	int getIter();

	// POST: Obtiene el tamaño de la lista
	int getSize();

};


template <class T> Lista<T>::Lista() {
	this->primero = NULL;
	this->iterador = this->primero;
	this->iteracion = 0;
	this->size = 0;
}

template <class T> Lista<T>::~Lista() {
	Nodo<T>* destructor = this->primero;
	while(this->getSize()>0){
		this->primero = this->primero->next();
		delete destructor;
		destructor = this->primero;
		this->size --;
	}
} 

template <class T> void Lista<T>::assign(T data){
	this->iterador->setNData(data);
}


template <class T> void Lista<T>::resetIter() {
	this->iterador = this->primero;
	this->iteracion = 0;
}

template <class T> Nodo<T>* Lista<T>::getNodo() {
	return this->iterador;
}

template <class T> T Lista<T>::getLData(int x) {
	irANodo(x);
	return this->iterador->getNData();
}

template <class T> void Lista<T>::add(T data) {
	Nodo<T>* nuevo = new Nodo<T>(data);
	iterar(FINAL);
	if(this->getSize() == 0){
		this->primero = nuevo;
		this->iterador = this->primero;
	}else{
		nuevo->setAnt(this->iterador);
		this->iterador->setSig(nuevo);
	}
	this->size++;
}

template <class T> int Lista<T>::getIter() {
	return this->iteracion;
}

template <class T> int Lista<T>::getSize() {
	return this->size;
}

// EDITAR esta aberracion
template <class T> void Lista<T>::irANodo(int x){
	bool inicioMasCerca = (this->getIter() / 2 < x);
    if(x < this->getIter()){
		if(inicioMasCerca){
        	this->resetIter();
			for(int i = this->getIter(); i < x; i++){
				this->iterar(SIGUIENTE);
			}
		} else {
			for(int i = this->getIter(); i > x; i--){
				this->iterar(ANTERIOR);
			}
		}
    } else {
		for(int i = this->getIter(); i < x; i++){
				this->iterar(SIGUIENTE);
		}
	}
}

#endif