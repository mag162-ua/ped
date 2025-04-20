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

void TABBPoro::InordenAux(TVectorPoro &v,int &pos) const{
    if (!this->EsVacio()){

        nodo->iz.InordenAux(v, pos);         // Visitar subárbol izquierdo
        v[pos] = this->nodo->item;           // Visitar nodo actual (la raíz)
        pos++;                               // Incrementar posición
        nodo->de.InordenAux(v, pos);         // Visitar subárbol derecho
    }
}

void TABBPoro::PreordenAux(TVectorPoro &v,int &pos) const{
    if (!this->EsVacio()){
        v[pos] = nodo->item;                 // Visitar nodo actual (la raíz)
        pos++;                               // Incrementar posición
        nodo->iz.PreordenAux(v, pos);         // Visitar subárbol izquierdo
        nodo->de.PreordenAux(v, pos);         // Visitar subárbol derecho
    }
}

void TABBPoro::PostordenAux(TVectorPoro &v,int &pos) const{
    if (!this->EsVacio())
    {
        nodo->iz.PostordenAux(v, pos);       // Visitar subárbol izquierdo
        nodo->de.PostordenAux(v, pos);       // Visitar subárbol derecho
        v[pos] = nodo->item;                 // Visitar nodo actual (la raíz)
        pos++;
    }
}

void TABBPoro::NivelesAux(TVectorPoro &v,int n, int &pos) const{
    if (EsVacio()) return;

    if (n == 1) {
        v[pos++] = nodo->item;
    } else {
        nodo->iz.NivelesAux(v, n - 1, pos);
        nodo->de.NivelesAux(v, n - 1, pos);
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
        //cout<<this->nodo->item<<endl;
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
    if(this->EsVacio()){
        return false;
    }
    else if(!this->Buscar(tp)){
        return false;
    }
    else{
        if(this->nodo->item==tp){
            if(this->nodo->iz.EsVacio() && this->nodo->de.EsVacio()){
                this->nodo = new TNodoABB();
                return true; 
            }
            else{
                if(!this->nodo->iz.EsVacio()){
                    TABBPoro* mayor = &this->nodo->iz;
    
                    while (!mayor->nodo->de.EsVacio()) {
                        mayor = &mayor->nodo->de;
                    }
    
                    // Copiar el item
                    this->nodo->item = mayor->nodo->item;
                    // Borrar ese nodo ahora duplicado
                    this->nodo->iz.Borrar(mayor->nodo->item);
                    return true;
    
                }
                else{
                    this->nodo=this->nodo->de.nodo;
                    return true;
                }
            }
        }
        else{
            return this->nodo->iz.Borrar(tp) || this->nodo->de.Borrar(tp);
        }
    }
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
        return 0;
    }
    if(this->nodo->iz.EsVacio() && this->nodo->de.EsVacio()){
        return 1;
    }
    return 0 + this->nodo->iz.NodosHoja() + this->nodo->de.NodosHoja();
}

TVectorPoro TABBPoro::Inorden() const{
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
    int total_nodos = Nodos();
    TVectorPoro resultado(total_nodos);
    int pos = 1;

    int h = Altura();
    for (int i = 1; i <= h; i++) {
        NivelesAux(resultado, i, pos);  // Añadir todos los nodos del nivel i
    }

    return resultado;
}

TABBPoro TABBPoro::operator+( TABBPoro &tabbp){
    TABBPoro resultado;
    if(this->EsVacio() && tabbp.EsVacio()){
        return TABBPoro();
    }
    else if(this->EsVacio()){
        return resultado = tabbp;
    }
    else if(tabbp.EsVacio()){
        return resultado = *this;
    }
    else{
        resultado = *this;

        TVectorPoro aux = tabbp.Inorden();
        for(int i=1;i<=aux.Longitud();i++){
            resultado.Insertar(aux[i]);
        }
        return resultado;
    }
}

TABBPoro TABBPoro::operator-( TABBPoro &tabbp){
    TABBPoro resultado;
    if(this->EsVacio() && tabbp.EsVacio()){
        return TABBPoro();
    }
    else if(this->EsVacio()){
        return TABBPoro();
    }
    else if(tabbp.EsVacio()){
        return resultado = *this;
    }
    else{
        TVectorPoro aux = this->Inorden();

        for(int i=1;i<=aux.Longitud();i++){
            TPoro poro_pos = TPoro(aux[i]);
            if(!tabbp.Buscar(poro_pos)){
                resultado.Insertar(poro_pos);
            }
        }
        return resultado;
    }
}

