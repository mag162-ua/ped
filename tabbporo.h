#ifndef _TABB_

#define _TABB_

#include<iostream>
using namespace std;

//#define _TABB_
#include "./../include/tporo.h"
#include "./../include/tvectorporo.h"

class TNodoABB;

class TABBPoro{
    //friend TNodoABB;
    friend ostream & operator<<(ostream &,const TABBPoro &);
    private:
        TNodoABB *nodo;
        void InordenAux(TVectorPoro &,int &) const;
        void PreordenAux(TVectorPoro &,int &);
        void PostordenAux(TVectorPoro &,int &);

    public:
        TABBPoro();
        TABBPoro(const TABBPoro &);
        ~TABBPoro();
        TABBPoro& operator=(const TABBPoro &);

        bool operator==(const TABBPoro &);
        bool EsVacio() const;
        bool Insertar(TPoro &);
        bool Borrar(TPoro &);
        bool Buscar(const TPoro &);
        TPoro Raiz()const ;
        int Altura()const ;
        int Nodos()const ;
        int NodosHoja()const ;
        TVectorPoro Inorden() const;
        TVectorPoro Preorden();
        TVectorPoro Postorden();
        TVectorPoro Niveles()const ;
        TABBPoro operator+( TABBPoro &);
        TABBPoro operator-( TABBPoro &);
};

class TNodoABB{
    friend TABBPoro;
    private:
        TPoro item;
        TABBPoro iz,de;
    
    public:
        TNodoABB ();
        TNodoABB (const TNodoABB &);
        ~TNodoABB ();
        TNodoABB & operator=(const TNodoABB &);
};

#endif