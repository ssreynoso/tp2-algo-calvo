#include "Coordenadas.h"

Coordenada::Coordenada(){
    this->coordX = 0;
    this->coordY = 0;
    this->coordZ = 0;
}

void Coordenada::setCoordenadaX(int x){
    this->coordX = x;
}

void Coordenada::setCoordenadaY(int y){
    this->coordY = y;
}

void Coordenada::setCoordenadaZ(int z){
    this->coordZ = z;
}

int Coordenada::getCoordenadaX(){
    return this->coordX;
}

int Coordenada::getCoordenadaY(){
    return this->coordY;
}

int Coordenada::getCoordenadaZ(){
    return this->coordZ;
}