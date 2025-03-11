#ifndef TListaPoro_
#define TListaPoro_

#include "./../include/tporo.h"
#include "./../include/tvectorporo.h"

class TListaNodo{
    friend class TListaPosicion;
    friend class TListaPoro;
    private:
        TPoro e;
        TListaNodo *anterior;
        TListaNodo *siguiente;
    public:
        TListaNodo();
        TListaNodo(const TListaNodo &tln);
        ~TListaNodo();
        TListaNodo& operator=(const TListaNodo &tln);
};

class TListaPosicion{
    friend class TListaPoro;
    private:
        TListaNodo *pos;
    public:
        TListaPosicion();
        TListaPosicion(TListaPosicion &tlp);
        ~TListaPosicion();
        TListaPosicion& operator=(const TListaPosicion &tlp);

        bool operator==(const TListaPosicion &tlp);
        TListaPosicion Anterior();
        TListaPosicion Siguiente();
        bool EsVacia();
};

class TListaPoro{
    friend ostream & operator<<(ostream &os, TListaPoro &tlp);
    private:
        TListaNodo *primero;
        TListaNodo *ultimo;
    public:
        TListaPoro();
        TListaPoro(TListaPoro &tlp);
        ~TListaPoro();
        TListaPoro & operator=( TListaPoro &tlp);

        bool operator==(TListaPoro &tlp);
        TListaPoro operator+(TListaPoro &tlp);
        TListaPoro operator-(TListaPoro &tlp);
        bool EsVacia();
        bool Insertar(TPoro &tlp);
        bool Borrar(TPoro &tlp);
        bool Borrar(TListaPosicion &tlp);
        TPoro Obtener(TListaPosicion &tlp);
        bool Buscar(TPoro &tlp);
        int Longitud();
        TListaPosicion Primera();
        TListaPosicion Ultima();
        TListaPoro ExtraerRango (int n1, int n2);
};

#endif