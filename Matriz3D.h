/* 
 * File:   Matriz3D.h
 * Author: José Negrillo Cárdenas
 *
 * Created on 24 de septiembre de 2013, 21:04
 */

#ifndef MATRIZ3D_H
#define	MATRIZ3D_H

#include <cstdlib>
#include "FueraDeRango.h"

using namespace std;

template <typename T,unsigned N> class Matriz3D {

public:
    Matriz3D() {
    n=N;
    p=new T**[N];
    for(int i=0;i<N;++i) {
        p[i]=new T*[N];
        for(int j=0;j<N;++j) {
            p[i][j]=new T[N];
            }
        }       
    }
    Matriz3D(const Matriz3D<T,N>& orig);

    virtual ~Matriz3D() {
    for(int i=0;i<n;++i) {
        for(int j=0;j<n;++j) {
            delete p[i][j];
        }
        delete p[i];
    }
    delete p;   
    };
    
    T& operator()(int x, int y, int z) throw (FueraDeRango){
        if(x<0 || x>=n || y<0 || y>=n || z<0 ||z>=n) throw FueraDeRango();
        return p[x][y][z];
    }

private:
    T*** p;
    int n;
    
};

#endif	/* MATRIZ3D_H */

