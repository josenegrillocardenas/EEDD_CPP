/* 
 * File:   VectorDin.h
 * Author: José Negrillo Cárdenas
 *
 * Created on 30 de septiembre de 2013, 23:43
 */

#ifndef VECTORDIN_H
#define	VECTORDIN_H
#include "FueraDeRango.h"
#include <iostream>

using namespace std;

template <typename T>
class VectorDin {
    private:
        T *v;
        int tamF, tamL;
    public:
        VectorDin(): tamF(1), tamL(0) {
            v=new T[tamF];
        }
        
        VectorDin(const VectorDin &orig): tamF(orig.tamF), tamL(orig.tamL) {
            v=new T[orig.tamF];
            for(int i=0;i<orig.tamL;++i)
                v[i]=orig.v[i];
        }
        
        ~VectorDin() {
            delete [] v;
        }
       
        VectorDin& operator=(const VectorDin &orig) {
            delete [] v;
            tamF=orig.tamF;
            tamL=orig.tamL;
            v=new T[orig.tamF];
            for(int i=0;i<orig.tamL;++i)
                v[i]=orig.v[i];
            return *this;
        }
        
        int tam() {
            return tamL;
        }
        
        T& operator[](int posicion) throw (FueraDeRango) {
            if(posicion<0 || posicion>=tamL) throw FueraDeRango();
            return v[posicion];
        }
        
        void insertarFinal(const T& algo) {
            if(tamL==tamF) {  // Si no hay hueco, reservamos más memoria
                T *aux=new T[tamF*2];
                for(int i=0;i<tamL;++i)
                    aux[i]=v[i];
                tamF*=2;
                delete [] v;
                v=aux;
            }
            v[tamL]=algo;
            ++tamL;
        }
        
        void insertar(const T& algo, int posicion) throw (FueraDeRango){
            if (posicion<0 ||posicion>=tamL) throw FueraDeRango();
            
            this->insertarFinal(algo);
            
            T aux=v[tamL-1];
            for(int i=tamL-1;i>=posicion;i--)  
                v[i+1]=v[i];
            
            v[posicion]=aux;
           
        }
        
        void borrarFinal() {
            --tamL;
            if(tamL==tamF/3) {          // Si el vector es 3 veces menor que la memoria
                T *aux=new T[tamF/2];   // reservada, lo reducimos a la mitad
                for(int i=0;i<tamL;++i)
                    aux[i]=v[i];
                tamF/=2;  
                delete [] v;
                v=aux;
            }
        }
        
        void borrar(int posicion) throw (FueraDeRango) {
            if (posicion<0 ||posicion>=tamL) throw FueraDeRango();
            for(int i=posicion;i<tamL;++i)
                v[i]=v[i+1];
            this->borrarFinal();
        }
};

#endif	/* VECTORDIN_H */

