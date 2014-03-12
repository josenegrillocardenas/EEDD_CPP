/* 
 * File:   ListaDEnlazada.h
 * Author: José Negrillo Cárdenas
 *
 * Created on 10 de octubre de 2013, 22:44
 */

#ifndef LISTADENLAZADA_H
#define	LISTADENLAZADA_H

#include <cstdlib>
#include "FueraDeRango.h"

using namespace std;

template <typename T>
class Nodo {
    public:
        T dato;
        Nodo *siguiente, *anterior;
        
        Nodo(const T& dato, Nodo<T> *anterior=0, Nodo<T> *siguiente=0): 
                dato(dato), siguiente(siguiente), anterior(anterior) {}
        Nodo(const Nodo& orig): 
                dato(orig.dato), siguiente(orig.siguiente), anterior(orig.anterior) {}
        ~Nodo() {}
};

template<typename T>
class Iterador {
    private:
        Nodo<T> *nodo;
    public:
        Iterador(Nodo<T> *algo): nodo(algo) {};
        ~Iterador() {}
        bool haySiguiente() {
             return (nodo->siguiente!=NULL);               
        }
        bool hayAnterior() {
            return (nodo->anterior!=NULL);
        }
        bool inicio() {
            return (nodo==NULL);
        }
        bool fin() {
            return (nodo==NULL);
        }
        void siguiente() {
            nodo=nodo->siguiente;
        }
        void anterior() {
            nodo=nodo->anterior;
        }
        Iterador<T>& operator++() {
            this->siguiente();
        }
        Iterador<T>& operator--() {
            this->anterior(); 
        }
        T& dato() {
            return nodo->dato;
        }
        Nodo<T>* getNodo() { return nodo; }  
};

template <typename T>
class ListaDEnlazada {
    private:
        Nodo<T> *cabecera, *cola;
        int tama;
    public:
        ListaDEnlazada(): cabecera(0), cola(0), tama(0) {}
        ListaDEnlazada(const ListaDEnlazada& orig): tama(orig.tama) {
            Iterador<T> i=orig.iteradorIni();
            while(!i.fin()) {
                this->pushBack(i.dato());
            }
        }
        ~ListaDEnlazada() {
            if(!this->empty()) this->vaciar();
        }
        ListaDEnlazada& operator=(const ListaDEnlazada& otro) {
            Iterador<T> i=otro.iteradorIni();
            this->vaciar();
            while(!i.fin()) {
                this->pushBack(i.dato());
            }
            tama=otro.tama;
        }
        Iterador<T> iteradorIni() {
            return Iterador<T>(cabecera);
        }
        Iterador<T> iteradorFin() {
            return Iterador<T>(cola);
        }
        bool empty() {
            return (cabecera==NULL && cola==NULL);
        }
        void pushFront(const T& dato) {
            if(this->empty()) {
                Nodo<T>* nodo=new Nodo<T>(dato);
                cabecera=nodo;
                cola=nodo;
            }
            else {
                Nodo<T>* nodo=new Nodo<T>(dato, NULL, cabecera);
                cabecera->anterior=nodo;
                cabecera=nodo;
            }
            ++tama;
        }
        void pushBack(const T& dato) {
            if(this->empty())
                this->pushFront(dato);
            else {
                Nodo<T>* nodo=new Nodo<T>(dato, cola, NULL);
                cola->siguiente=nodo;
                cola=nodo;
                ++tama;
            }
            
        }
        
        /**
         * @param dato Dato a insertar en la lista.
         * @param i Iterador en la posición que metemos el dato.
         * @note El dato se inserta justo delante del dato indicado por el iterador. 
         * Ejemplo: Lista-> 1,2,3,4,5; \n
         *  Iterador->3; \n
         *  insertar(10,iterador); \n
         *  Inserta el 10 entre el 2 y el 3
         */
        void insertar(const T& dato, Iterador<T>& i) {
            if(this->empty() || !i.hayAnterior()) {
                this->pushFront(dato);          
            }           
            else {
                Nodo<T> *nodo=new Nodo<T>(dato, i.getNodo()->anterior, i.getNodo());
                i.getNodo()->anterior->siguiente=nodo;
                i.getNodo()->anterior=nodo;
                ++tama;
            }
        }
        void popFront() throw (FueraDeRango) {
            if (this->empty()) throw FueraDeRango();
            if (cabecera==cola) { // Si sólo hay un elemento
                delete cabecera;
                cabecera=NULL;
                cola=NULL;
            }
            else { // Si hay varios
                cabecera=cabecera->siguiente;
                delete cabecera->anterior;
                cabecera->anterior=NULL;
            }
            --tama;
        }
        void popBack() throw (FueraDeRango) {
            if (this->empty()) throw FueraDeRango();
            if (cabecera==cola)  // Si sólo hay un elemento
                this->popFront();                      
            else {
                cola=cola->anterior;
                delete cola->siguiente;
                cola->siguiente=NULL;
                --tama;
            }
        }
        /**
         * @param i Iterador que indica el elemento a borrar.
         * @note El iterador queda sobre el dato siguiente al borrado.
         */
        void borrar(Iterador<T>& i) throw (FueraDeRango) {
            if(this->empty()) throw FueraDeRango();
            if(!i.hayAnterior()) this->popFront();
            else if(!i.haySiguiente()) this->popBack();
            else {
                Nodo<T> *aux=i.getNodo();
                ++i;
                aux->siguiente->anterior=aux->anterior;
                aux->anterior->siguiente=aux->siguiente;
                delete aux; 
                --tama;
            }
        }
        void vaciar() {
            while(!this->empty()) {
                this->popBack();
            }
            tama=0;
        }
        T& front() throw (FueraDeRango) {
            if(this->empty()) throw FueraDeRango();
            return cabecera->dato;
        }
        T& back() throw (FueraDeRango) {
            if(this->empty()) throw FueraDeRango();
            return cola->dato;
        }
        int tam() {
            return tama;
        }
    
};

#endif	/* LISTADENLAZADA_H */

