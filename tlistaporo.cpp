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

    this->e=TPoro(tln.e);
    this->anterior=tln.anterior ? new TListaNodo(*tln.anterior) : nullptr;
    this->siguiente=tln.anterior ? new TListaNodo(*tln.siguiente) : nullptr;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

TListaPosicion::TListaPosicion(){
    this->pos=new TListaNodo;
}

TListaPosicion::TListaPosicion(TListaPosicion &tlp){
    this->pos=new TListaNodo(*tlp.pos);
}

TListaPosicion::~TListaPosicion(){
    //delete(this->pos);
    this->pos=NULL;
}

TListaPosicion& TListaPosicion::operator=(const TListaPosicion &tlp){
    this->pos= tlp.pos? new TListaNodo(*tlp.pos): NULL;
    return *this;
}

bool TListaPosicion::operator==(const TListaPosicion &tlp){
    return this->pos && tlp.pos && this->pos->e == tlp.pos->e; //comprueba no esten vacios y ambos sean iguales
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

ostream& operator<<(ostream &os, TListaPoro &tlp){
    os<<"(";
    TListaPosicion pos=tlp.Primera();
    if(!tlp.EsVacia()){
        for(int i=0;i<tlp.Longitud();i++){
            //cout<<pos.pos;
            os<<pos.pos->e;
            if(i!=tlp.Longitud()-1){
                os<<" ";
            }
            pos=pos.Siguiente();
        }
        
    }
    os<<")";
    return os;
}

TListaPoro::TListaPoro(){
    this->primero=new TListaNodo();
    this->ultimo=new TListaNodo();
}

TListaPoro::TListaPoro(TListaPoro &tlp){
    this->primero = NULL;
    this->ultimo = NULL;
    TListaNodo *actual = tlp.primero;
    while (actual) {
        this->Insertar(actual->e);
        actual = actual->siguiente;
    }
}

TListaPoro::~TListaPoro(){
    this->primero=NULL;
    this->ultimo=NULL;
}

TListaPoro& TListaPoro::operator=( TListaPoro &tlp){
    if(!(tlp.EsVacia())){
        delete(this->primero);
        delete(this->ultimo);

        TListaPosicion pos_tlp=tlp.Primera();
        while(pos_tlp.pos!=NULL){
            TListaNodo *new_pos=new TListaNodo(*pos_tlp.pos); 
            this->Insertar(new_pos->e);
            pos_tlp=pos_tlp.Siguiente();
        }
    }
    else{
        this->primero=NULL;
        this->ultimo=NULL;
    }
    return *this;
}

bool TListaPoro::operator==(TListaPoro &tlp){

    TListaNodo* tln_this=this->primero;
    TListaNodo* tln_tlp=tlp.primero;
    
    while(tln_this!=NULL && tln_tlp!=NULL){

        if(tln_tlp->e!=tln_this->e){
            return false;
        }

        tln_this=tln_this->siguiente;
        tln_tlp=tln_tlp->siguiente;

    }
    return true;
}

TListaPoro TListaPoro::operator+(TListaPoro &tlp){
    TListaPoro *list_mas;
    if(tlp.EsVacia()){
        list_mas=this;
    }
    else if(this->EsVacia()){
        list_mas=&tlp;
    }
    else{
        list_mas=this;
        TListaPosicion pos=tlp.Primera();
        while(pos.pos!=NULL){
            list_mas->Insertar(pos.pos->e);

            pos=pos.Siguiente();
        }
    }
    return *list_mas;
}

TListaPoro TListaPoro::operator-(TListaPoro &tlp){
    TListaPoro *list_menos;
    if(tlp.EsVacia()){
        list_menos=this;
    }
    else if(this->EsVacia()){
        list_menos=&tlp;
    }
    else{
        list_menos=this;
        TListaPosicion pos=tlp.Primera();
        while(pos.pos!=NULL){
            if(this->Buscar(pos.pos->e)){
                list_menos->Borrar(pos.pos->e);
            }

            pos=pos.Siguiente();
        }
    }
    return *list_menos;
}

bool TListaPoro::EsVacia(){
    if(this->primero==NULL){
        return true;
    }
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
    
    TListaPosicion pos_tlp=this->Primera();

    while (pos_tlp.pos!=NULL){
        
        if(pos_tlp.pos->e==tlp){
            
            if(!pos_tlp.pos->anterior && !pos_tlp.pos->siguiente){
                this->primero=NULL;
                this->ultimo=NULL;
            }
            else if(!pos_tlp.pos->anterior){
                this->primero=this->primero->siguiente;
                this->primero->anterior=NULL;
            }
            else if(!pos_tlp.pos->siguiente){
                this->ultimo=this->ultimo->anterior;
                this->ultimo->siguiente=NULL;
            }
            else{
                pos_tlp.pos->anterior->siguiente=pos_tlp.pos->siguiente ? pos_tlp.pos->siguiente: NULL;
                pos_tlp.pos->siguiente->anterior=pos_tlp.pos->anterior ? pos_tlp.pos->anterior: NULL;
            }
            
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
    return this->Borrar(tlp.pos->e);
    /*else{

        TListaPosicion pos_tlp=this->Primera();

        while (pos_tlp.pos!=NULL){
            if(pos_tlp.pos==tlp.pos){
                
                pos_tlp.pos->anterior->siguiente=pos_tlp.pos->siguiente ? pos_tlp.pos->siguiente: NULL;
                pos_tlp.pos->siguiente->anterior=pos_tlp.pos->anterior ? pos_tlp.pos->anterior: NULL;
                
                return true;

            }

            pos_tlp=pos_tlp.Siguiente();
        }
        return false;
    }*/
}

TPoro TListaPoro::Obtener(TListaPosicion &tlp){
    if(!tlp.EsVacia() && this->Buscar(tlp.pos->e)){
        TPoro pos_p;

        TListaPosicion pos_tlp=this->Primera();

        while (pos_tlp.pos!=NULL){
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
        return TPoro();
    }
    else{
        return TPoro();
    }
}

bool TListaPoro::Buscar(TPoro &tlp){

    TListaPosicion pos_tlp=this->Primera();
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
    tlp.pos=this->ultimo;
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

    ///////////

    /*TListaPoro resultado;
    if (n2 < n1 || EsVacia()) return resultado;

    TListaPosicion pos = Primera();
    int contador = 1;
    while (!pos.EsVacia() && contador <= n2) {
        if (contador >= n1) {
            resultado.Insertar(pos.pos->e);
            Borrar(pos);
        }
        pos = pos.Siguiente();
        contador++;
    }
    return resultado;*/
}
