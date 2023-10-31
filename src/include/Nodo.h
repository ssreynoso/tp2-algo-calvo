#ifndef __NODO_H__
#define __NODO_H__

template <class T> class Nodo{
private:
    T data;
    Nodo<T>* sig;
    Nodo<T>* ant;

public:

    // PRE: Recibe un dato generico
    // POST: Construye un nodo con el dato recibido
    Nodo(T data);
    
    // PRE: Devuelve el dato guardado en el nodo
    T getNData();
    
    // PRE: Recibe un dato generico
    // POST: Setea el dato del nodo
    void setNData(T data);
    
    // POST: Devuelve el nodo siguiente
    Nodo<T>* next();

    // POST: Devuelve el nodo anterior
    Nodo<T>* prev();

    // POST: Linkea el nodo siguiente al puntero
    void setSig(Nodo<T>* sig);

    // POST: Linkea el nodo anterior al puntero
    void setAnt(Nodo<T>* ant);
};

template <class T> Nodo<T>::Nodo(T data){
    this->data = data;
    this->sig = NULL;
    this->ant = NULL;
}

template <class T> T Nodo<T>::getNData(){
    return this->data;
}

template <class T> void Nodo<T>::setNData(T data){
    this->data = data;
}

template <class T> Nodo<T>* Nodo<T>::next(){
    return this->sig;
}

template <class T> Nodo<T>* Nodo<T>::prev(){
    return this->ant;
}

template <class T> void Nodo<T>::setSig(Nodo<T>* sig) {
    this->sig = sig;
}

template <class T> void Nodo<T>::setAnt(Nodo<T>* ant) {
    this->ant = ant;
}

#endif