#include "./include/Tablero.h"

Tablero::Tablero(int x, int y, int z){
	//validar
	this->x = x;
	this->y = y;
	this->z = z;

	this->cubo = new Lista<Lista<Lista<Celda*>*>*>();
	for (int i = 0; i < x; i++) {
		Lista<Lista<Celda*>*>* plano = new Lista<Lista<Celda*>*>();
		for (int j = 0; j < y; j++) {
			Lista<Celda*>* fila = new Lista<Celda*>();
			for (int k = 0; k < z; k++) {
				Celda* celda = new Celda();
				fila->agregar(celda);
				celda->setCoordenada(i+1, j+1, k+1);
			}
			plano->agregar(fila);
		}
		cubo->agregar(plano);
	}
}

Tablero::~Tablero(){
	this->cubo->iniciarCursor();
		while(this->cubo->avanzarCursor()){
			Lista<Lista<Celda*>*>* plano = this->cubo->obtenerCursor();
			plano->iniciarCursor();
			while(plano->avanzarCursor()){
				Lista<Celda*>* fila = plano->obtenerCursor();
				fila->obtenerCursor();
				while(fila->avanzarCursor()){
					delete fila->obtenerCursor();
				}
				delete fila;
			}
			delete plano;
		}
		delete this->cubo;
}

Celda* Tablero::getCelda(int x, int y, int z){
	if(inRange(x, y, z)){
		return this->cubo->obtener(x)->obtener(y)->obtener(z);
	}else{
		throw "Las coordenadas indicadas estan fuera de rango";
	}
}

int Tablero::getTamanioX() {
    return this->x;
}

int Tablero::getTamanioY() {
    return this->y;
}

int Tablero::getTamanioZ() {
    return this->z;
}

bool Tablero::inRange(int x, int y, int z){
	if( (x >= 0 && x <= this->x) && (y >= 0 && y <= this->y) && (z >= 0 && z <= this->z) ){

		return true;
	}else{
		return false;
	}
}



