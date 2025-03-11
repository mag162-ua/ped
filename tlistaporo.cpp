#include <iostream>

using namespace std;

#include "./../include/tporo.h"
#include "./../include/tvectorporo.h"
#include "./../include/tlistaporo.h"

TListaNodo::TListaNodo(){
    this->e=TPoro();
    this->anterior=NULL;
    this->siguiente=NULL;
}

TListaNodo::TListaNodo(const TListaNodo &tln){
    this->e=tln.e;
    this->anterior=tln.anterior;
    this->siguiente=tln.siguiente;
}

TListaNodo::~TListaNodo(){ //PREGUNTAR
    this->anterior=NULL;
    this->siguiente=NULL;
    e=TPoro();
}

TListaNodo& TListaNodo::operator=(const TListaNodo &tln){
    this->e=tln.e;
    this->anterior=tln.anterior;
    this->siguiente=tln.siguiente;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

TListaPosicion::TListaPosicion(){
    this->pos=new TListaNodo;
}

TListaPosicion::TListaPosicion(TListaPosicion &tlp){
    this->pos=tlp.pos;
}

TListaPosicion::~TListaPosicion(){
    //delete(this->pos);
    this->pos=NULL;
}

TListaPosicion& TListaPosicion::operator=(const TListaPosicion &tlp){
    this->pos=tlp.pos;
    return *this;
}

bool TListaPosicion::operator==(const TListaPosicion &tlp){
    if(this->pos==tlp.pos){
        return true;
    }
    return false;
}

TListaPosicion TListaPosicion::Anterior(){
    TListaPosicion ant_tlp=TListaPosicion();
    ant_tlp.pos=this->pos->anterior;
    return ant_tlp;
}

TListaPosicion TListaPosicion::Siguiente(){
    TListaPosicion sig_tlp=TListaPosicion();
    sig_tlp.pos=this->pos->siguiente;
    return sig_tlp;
}

bool TListaPosicion::EsVacia(){
    if(this->pos==NULL){
        return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////

//Ordenada por volumen

TListaPoro::TListaPoro(){
    this->primero=new TListaNodo();
    this->ultimo=new TListaNodo();
}

TListaPoro::TListaPoro(TListaPoro &tlp){
    this->primero= new TListaNodo(*tlp.primero);
    this->ultimo=new TListaNodo(*tlp.ultimo);
}

TListaPoro::~TListaPoro(){
    delete(this->primero);
    delete(this->ultimo);
}

TListaPoro& TListaPoro::operator=( TListaPoro &tlp){
    if(!(tlp.EsVacia())){
        delete(this->primero);
        delete(this->ultimo);

        this->primero=new TListaNodo(*tlp.primero);
        this->ultimo=new TListaNodo(*tlp.ultimo);
    }
    else{
        this->primero=NULL;
        this->ultimo=NULL;
    }
    return *this;
}

bool TListaPoro::operator==(TListaPoro &tlp){
    //TPoro tp_this=this->primero->e;
    //TPoro tp_tlp=tlp.primero->e;

    TListaNodo* tln_this=this->primero;
    TListaNodo* tln_tlp=tlp.primero;
    
    while(tln_this!=NULL && tln_tlp!=NULL){
        /*if(tp_this!=tp_tlp){
            return false;
        }*/
        if(tln_tlp->e!=tln_this->e){
            return false;
        }

        tln_this=tln_this->siguiente;
        tln_tlp=tln_tlp->siguiente;

        //tp_this=tln_this.e;
        //tp_tlp=tln_tlp.e;
    }
    return true;
}

TListaPoro TListaPoro::operator+(TListaPoro &tlp){
    //TPoro tp_this=this->primero->e;
    //TPoro tp_tlp=tlp.primero->e;

    
    TListaNodo tln_tlp=*tlp.primero;

    /*while(this->ultimo->e!=tln_this.e){
        exist=false;
        while(tlp.ultimo->e!=tln_tlp.e){
            if(tp_this==tp_tlp){
                exist=true;
            }
            
            tln_tlp=*tln_tlp.siguiente;
            tp_tlp=tln_tlp.e;
        }
        tln_this=*tln_this.siguiente;
        tp_this=tln_this.e;
    }*/
    //return true;
    bool exist;
    TListaPoro listmas=TListaPoro(*this);

    while(tlp.ultimo->e!=tln_tlp.e){ //recorre pasado por parametro
        exist=false;
        TListaNodo tln_this=*this->primero;
        while(this->ultimo->e!=tln_this.e){ //recorre this
            if(tln_tlp.e==tln_this.e){ //si this y parametro coinciden
                exist=true;
            }
            tln_this=*tln_this.siguiente; //siguiente posición this
            //tp_this=tln_this.e;

        }
        if(!exist){ //Si no coincide
            TListaNodo mas=TListaNodo(tln_this);
            this->ultimo->siguiente=&mas;
            TListaNodo ant=*listmas.ultimo;
            listmas.ultimo=&mas;
            listmas.ultimo->anterior=&ant;
        }
        tln_tlp=*tln_tlp.siguiente; //siguiente de parametro
        //tp_tlp=tln_tlp.e;
    }
    return listmas;
}

TListaPoro TListaPoro::operator-(TListaPoro &tlp){

    TListaNodo tln_this=*this->primero;
    

    bool exist;
    TListaPoro listmenos=TListaPoro();

    while(this->ultimo->e!=tln_this.e){ //Recorre this
        exist=false;
        TListaNodo tln_tlp=*tlp.primero;
        while(tlp.ultimo->e!=tln_tlp.e){ //recorre parametro
            if(tln_tlp.e==tln_this.e){ //si coinciden
                exist=true;
            }

            tln_tlp=*tln_tlp.siguiente;//siguiente de parametro
        }
        if(!exist){
            if(listmenos.primero==NULL){
                listmenos.primero=new TListaNodo(tln_this);
                listmenos.ultimo=new TListaNodo(tln_this);
            }
            else{
                TListaNodo menos=TListaNodo(tln_this);
                this->ultimo->siguiente=&menos;
                TListaNodo ant=*listmenos.ultimo;
                listmenos.ultimo=&menos;
                listmenos.ultimo->anterior=&ant;
            }
            
        }
    }
    return listmenos;

}

bool TListaPoro::EsVacia(){
    if(this->primero->e.EsVacio() && this->ultimo->e.EsVacio()){
        return true;
    }
    return false;
}

bool TListaPoro::Insertar(TPoro &tlp){

    if(this->EsVacia()){
        // Si la lista está vacía, simplemente creamos un nuevo nodo.
        TListaNodo* nuevo = new TListaNodo();
        nuevo->e = tlp;
        nuevo->siguiente = NULL;
        nuevo->anterior = NULL;

        this->primero = nuevo;
        this->ultimo = nuevo;
        return true;
    }
    else if(this->Buscar(tlp)){
        // Si el elemento ya existe, no lo insertamos.
        return false;
    }
    else{
        // Crear una posición inicial para empezar el recorrido
        TListaPosicion pos_tlp = this->Primera();

        // Recorrer la lista y encontrar la posición adecuada
        while (pos_tlp.pos != NULL) {
            // Comparamos el volumen para encontrar el lugar de inserción
            if (tlp.Volumen() < pos_tlp.pos->e.Volumen()) {
                // Si encontramos la posición adecuada
                TListaNodo* nuevo = new TListaNodo();
                nuevo->e = tlp;
                
                // Insertar el nuevo nodo en la posición encontrada
                nuevo->siguiente = pos_tlp.pos;
                nuevo->anterior = pos_tlp.pos->anterior;

                if (pos_tlp.pos->anterior != NULL) {
                    pos_tlp.pos->anterior->siguiente = nuevo;
                }
                pos_tlp.pos->anterior = nuevo;

                // Si estamos insertando en la primera posición
                if (pos_tlp.pos == this->primero) {
                    this->primero = nuevo;
                }

                return true;
            }

            // Avanzar al siguiente nodo
            pos_tlp = pos_tlp.Siguiente();
        }

        // Si no encontramos la posición, insertamos al final
        TListaNodo* nuevo = new TListaNodo();
        nuevo->e = tlp;
        nuevo->siguiente = NULL;
        nuevo->anterior = this->ultimo;
        this->ultimo->siguiente = nuevo;
        this->ultimo = nuevo;

        return true;
    }
}

bool TListaPoro::Borrar(TPoro &tlp){

    if(!this->Buscar(tlp)){
        return false;
    }

    TListaPosicion pos_tlp=TListaPosicion();
    pos_tlp=this->Primera();

    while (!(pos_tlp==this->Ultima())){
        if(pos_tlp.pos->e==tlp){
            
            pos_tlp.pos->anterior->siguiente=pos_tlp.pos->siguiente;
            pos_tlp.pos->siguiente->anterior=pos_tlp.pos->anterior;
            
            return true;

        }

        pos_tlp=pos_tlp.Siguiente();
    }
    return false;
}

bool TListaPoro::Borrar(TListaPosicion &tlp){

    if(!this->Buscar(tlp.pos->e)){
        return false;
    }

    if(tlp.EsVacia()){
        return false;
    }
    else{

        TListaPosicion pos_tlp=TListaPosicion();
        pos_tlp=this->Primera();

        while (!(pos_tlp==this->Ultima())){
            if(pos_tlp.pos==tlp.pos){
                
                pos_tlp.pos->anterior->siguiente=pos_tlp.pos->siguiente;
                pos_tlp.pos->siguiente->anterior=pos_tlp.pos->anterior;
                
                return true;

            }

            pos_tlp=pos_tlp.Siguiente();
        }
        return false;
    }
}

TPoro TListaPoro::Obtener(TListaPosicion &tlp){
    if(!tlp.EsVacia() && this->Buscar(tlp.pos->e)){
        //if(){
        TPoro pos_p;

        TListaPosicion pos_tlp=TListaPosicion();
        pos_tlp=this->Primera();

        while (!(pos_tlp==this->Ultima())){
            if(pos_tlp==tlp){
                if(pos_tlp.pos->e.EsVacio()){
                    pos_p=TPoro();
                    break;
                }
                else{
                    pos_p=pos_tlp.pos->e;
                    break;
                }
            }
            pos_tlp=pos_tlp.Siguiente();
        }
        //}
        return TPoro();
    }
    else{
        return TPoro();
    }
}

bool TListaPoro::Buscar(TPoro &tlp){
    TListaPosicion pos_tlp=TListaPosicion();
    pos_tlp=this->Primera();
    while (pos_tlp.pos!=NULL){
        if(pos_tlp.pos->e==tlp){
            return true;
        }
        pos_tlp=pos_tlp.Siguiente();
    }
    return false;
}

int TListaPoro::Longitud(){
    if(this->EsVacia()){
        return 0;
    }
    TListaPosicion tlp=this->Primera();
    
    int i=0;
    
    while (tlp.pos!=NULL){
        i++;
        
        tlp=tlp.Siguiente();
        
    }
    return i;
}

TListaPosicion TListaPoro::Primera(){
    TListaPosicion tlp=TListaPosicion();
    tlp.pos=this->primero;
    return tlp;
}

TListaPosicion TListaPoro::Ultima(){
    TListaPosicion tlp=TListaPosicion();
    tlp.pos=this->primero;
    return tlp;
}

TListaPoro TListaPoro::ExtraerRango (int n1, int n2){
    TListaPoro rang_tlp;
    if(n2<n1){
        return rang_tlp;
    }
    for(int i=1;i<=this->Longitud();i++){

        TListaPosicion pos_tlp=TListaPosicion();
        pos_tlp=this->Primera();

        if(i<=n2 && i>=n1){
            if(rang_tlp.EsVacia()){
                rang_tlp.primero=pos_tlp.pos;
            }
            else{
                if(rang_tlp.Longitud()==1){
                    rang_tlp.primero->siguiente=pos_tlp.pos;
                }
                else{
                    rang_tlp.ultimo->siguiente=pos_tlp.pos;
                }
                rang_tlp.ultimo=pos_tlp.pos;
            }
        }

        pos_tlp=pos_tlp.Siguiente();
        
    }
    return rang_tlp;
}
