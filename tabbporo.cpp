#include<iostream>



#include "./../include/tporo.h"
#include "./../include/tvectorporo.h"
#include "./../include/tabbporo.h"

using namespace std;

TNodoABB::TNodoABB (){
    this->item=TPoro();
    this->iz=TABBPoro();
    this->de=TABBPoro();

}

TNodoABB::TNodoABB (const TNodoABB &tnabb){
    this->item=TPoro(tnabb.item);
    this->iz=tnabb.iz;
    this->de=tnabb.de;
}

TNodoABB::~TNodoABB (){
    this->item=TPoro();
    this->iz=TABBPoro();
    this->de=TABBPoro();
}

TNodoABB & TNodoABB::operator=(const TNodoABB &tnabb){
    this->item=TPoro(tnabb.item);
    this->iz=TABBPoro(tnabb.iz);
    this->de=TABBPoro(tnabb.de);
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////77

ostream& operator<<(ostream &os,TABBPoro &poro){ 
    return os;
}

void TABBPoro::InordenAux(const TVectorPoro &v,int &pos){
    if (this->EsVacio()){
        nodo->iz.InordenAux(v, pos);         // Visitar subárbol izquierdo
        v[pos] = nodo->item;                 // Visitar nodo actual (la raíz)
        pos++;                               // Incrementar posición
        nodo->de.InordenAux(v, pos);         // Visitar subárbol derecho
    }
}

void TABBPoro::PreordenAux(const TVectorPoro &v,int &pos){
    if (this->EsVacio()){
        v[pos] = nodo->item;                 // Visitar nodo actual (la raíz)
        pos++;                               // Incrementar posición
        nodo->iz.PreordenAux(v, pos);         // Visitar subárbol izquierdo
        nodo->de.PreordenAux(v, pos);         // Visitar subárbol derecho
    }
}

void TABBPoro::PostordenAux(const TVectorPoro &v,int &pos){
    if (this->EsVacio())
    {
        nodo->iz.PostordenAux(v, pos);       // Visitar subárbol izquierdo
        nodo->de.PostordenAux(v, pos);       // Visitar subárbol derecho
        v[pos] = nodo->item;                 // Visitar nodo actual (la raíz)
        pos++;
    }
}

TABBPoro::TABBPoro(){
    this->nodo=NULL;
}

TABBPoro::TABBPoro(const TABBPoro &tabbp){
    //this->nodo = tabbp.nodo;
    this->nodo=new TNodoABB(*tabbp.nodo);
}

TABBPoro::~TABBPoro(){
    delete this->nodo;
    this->nodo=NULL;
}

TABBPoro& TABBPoro::operator=(const TABBPoro &tabbp){
    if(tabbp.nodo==NULL){
        this->nodo=NULL;
    }
    else{
        if(this->nodo==NULL){
            this->nodo=new TNodoABB();
        }
        //this->nodo= tabbp.nodo;
        this->nodo=new TNodoABB(*tabbp.nodo);
    }
    return *this;
}

bool TABBPoro::operator==(const TABBPoro &tabbp){
    this->nodo;
    if(tabbp.Raiz().EsVacio()){
        return true;
    }
    else if(this->Buscar(tabbp.Raiz())){
        return true && *this==tabbp.nodo->iz && *this==tabbp.nodo->de;
    }
    else{
        return false;
    }
    
}

bool TABBPoro::EsVacio() const{
    return this->Raiz().EsVacio();
}

bool TABBPoro::Insertar(TPoro &tp){
    //cout<<this->EsVacio()<<endl;
    if(this->EsVacio()){
        if(this->nodo==NULL){
            this->nodo=new TNodoABB();
        }
        this->nodo->item=tp;
        return true;
    }
    if(this->Buscar(tp)){
        //cout<<"ya existe"<<endl;
        return false;
    }
    else{
        if(tp.Volumen() < this->Raiz().Volumen()){
            return this->nodo->iz.Insertar(tp);
        }
        else{
            return this->nodo->de.Insertar(tp);
        }
    }

}

bool TABBPoro::Borrar(TPoro &tp){

}

bool TABBPoro::Buscar(const TPoro &tp){
    TPoro raiz = this->Raiz();
    if(raiz.EsVacio()){
        return false;
    }
    else if(raiz==tp){
        return true;
    }
    else{
        return (this->nodo->iz.Buscar(tp) || this->nodo->de.Buscar(tp));
    }
}

TPoro TABBPoro::Raiz()const{
    if(this->nodo==NULL){
        return TPoro();
    }
    else{
        return this->nodo->item;
    }
}

int TABBPoro::Altura()const{
    if(this->EsVacio()){
        return 0;
    }
    else{
        return max(1 + this->nodo->iz.Altura(),1 + this->nodo->de.Altura());
    }
}

int TABBPoro::Nodos()const{
    if(this->EsVacio()){
        return 0;
    }
    return 1 + this->nodo->iz.Nodos() + this->nodo->de.Nodos();
}

int TABBPoro::NodosHoja()const{
    if(this->EsVacio()){
        return 1;
    }
    return 0 + this->nodo->iz.Nodos() + this->nodo->de.Nodos();
}

TVectorPoro TABBPoro::Inorden(){
    // Posición en el vector que almacena el recorrido
    int posicion = 1;

    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorPoro v(Nodos());
    this->InordenAux(v, posicion);
    return v;
}

TVectorPoro TABBPoro::Preorden(){
    // Posición en el vector que almacena el recorrido
    int posicion = 1;
    
    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorPoro v(Nodos());
    PreordenAux(v, posicion);
    return v;
}

TVectorPoro TABBPoro::Postorden(){
    // Posición en el vector que almacena el recorrido
    int posicion = 1;
    
    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorPoro v(Nodos());
    PostordenAux(v, posicion);
    return v;
}

TVectorPoro TABBPoro::Niveles()const{

}

TABBPoro TABBPoro::operator+( TABBPoro &tabbp){
    TABBPoro resultado = *this;
    TVectorPoro aux = tabbp.Inorden();
    for(int i=0;i<aux.Longitud();i++){
        resultado.Insertar(aux[i]);
    }
    return resultado;
}

TABBPoro TABBPoro::operator-( TABBPoro &tabbp){
    TABBPoro resultado;
    TVectorPoro aux = this->Inorden();
    for(int i=0;i<aux.Longitud();i++){
        if(!tabbp.Buscar(aux[i])){
            resultado.Insertar(aux[i]);
        }
    }
    return resultado;
}

