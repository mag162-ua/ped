//MARTÍN AZNAR GARCÍA, 51797315G

#include <iostream>

using namespace std;

#include "./../include/tporo.h"
#include "./../include/tvectorporo.h"
#include "./../include/tlistaporo.h"

TListaNodo::TListaNodo(){ //Construtor por defecto
    this->e=TPoro();
    this->anterior=NULL;
    this->siguiente=NULL;
}

TListaNodo::TListaNodo(const TListaNodo &tln){ //Constructor de copia
    
    this->e=tln.e;
    this->anterior=tln.anterior;
    this->siguiente=tln.siguiente;

}

TListaNodo::~TListaNodo(){ //Destructor
    this->anterior=NULL;
    this->siguiente=NULL;
    e=TPoro();
}

TListaNodo& TListaNodo::operator=(const TListaNodo &tln){ //Copia los atributos

    this->e=TPoro(tln.e);
    this->anterior=tln.anterior ? new TListaNodo(*tln.anterior) : NULL; //Si anterior no es vacio se crea una copia
    this->siguiente=tln.anterior ? new TListaNodo(*tln.siguiente) : NULL; //Si siguiente no es vacio se crea una copia
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

TListaPosicion::TListaPosicion(){ //Cosntructor por defecto
    this->pos=new TListaNodo;
}

TListaPosicion::TListaPosicion(TListaPosicion &tlp){ //Constructor de copia
    this->pos=new TListaNodo(*tlp.pos);
}

TListaPosicion::~TListaPosicion(){ //Destructor
    this->pos=NULL;
}

TListaPosicion& TListaPosicion::operator=(const TListaPosicion &tlp){
    this->pos= tlp.pos? new TListaNodo(*tlp.pos): NULL; //Crea un nuevo TListaNodo si el pasado por paramnetro es distinto de NULL
    return *this;
}

bool TListaPosicion::operator==(const TListaPosicion &tlp){
    return this->pos && tlp.pos && this->pos->e == tlp.pos->e; //comprueba no esten vacios y ambos sean iguales
}

TListaPosicion TListaPosicion::Anterior(){ //Devuelve la posición anterior
    TListaPosicion ant_tlp=TListaPosicion();
    ant_tlp.pos=this->pos->anterior;
    return ant_tlp;
}

TListaPosicion TListaPosicion::Siguiente(){ //Devuelve la posición siguiente
    TListaPosicion sig_tlp=TListaPosicion();
    sig_tlp.pos=this->pos->siguiente;
    return sig_tlp;
}

bool TListaPosicion::EsVacia(){ //True si el puntero pos es NULL, false en caso contrario
    if(this->pos==NULL){
        return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////

//Ordenada por volumen

ostream& operator<<(ostream &os,const TListaPoro &tlp){ //operador de salida
    os<<"(";
    TListaPosicion pos=tlp.Primera();
    if(!tlp.EsVacia()){ //Comprueba que no este vacia
        for(int i=0;i<tlp.Longitud();i++){

            os<<pos.pos->e; //llama a operator<<(ostream, TPoro)
            if(i!=tlp.Longitud()-1){ //Introduce espacios exceptuando la ultima vez
                os<<" ";
            }
            pos=pos.Siguiente(); //Salta la siguiente nodo
        }
        
    }
    os<<")";
    return os;
}

TListaPoro::TListaPoro(){ //Constructor por defecto
    this->primero=new TListaNodo();
    this->ultimo=new TListaNodo();
}

TListaPoro::TListaPoro(TListaPoro &tlp){ //Constructor de copia
    this->primero = NULL;
    this->ultimo = NULL;
    TListaNodo *actual = tlp.primero; //primer nodo de la lista
    while (actual) { //recorre la lista pasada por parametro
        this->Insertar(actual->e); // Inserta el nodo
        actual = actual->siguiente; // salta al siguiente nodo
    }
}

TListaPoro::~TListaPoro(){ //destructor
    this->primero=NULL;
    this->ultimo=NULL;
}

TListaPoro& TListaPoro::operator=( TListaPoro &tlp){ //Copia los nodos de la lista 
    if(!(tlp.EsVacia())){ //Comprueba que no este vacio
        delete(this->primero);
        delete(this->ultimo);

        TListaPosicion pos_tlp=tlp.Primera();//asigna primera posición
        while(pos_tlp.pos!=NULL){ //Recorre la lista pasada por parametro
            TListaNodo *new_pos=new TListaNodo(*pos_tlp.pos); //crea un nuevo nodo copia de el nodo auxiliar
            this->Insertar(new_pos->e); //inserta en this object
            pos_tlp=pos_tlp.Siguiente(); //Salta a la siguiente posición
        }
    }
    else{ //Si esta vacia
        this->primero=NULL;
        this->ultimo=NULL;
    }
    return *this;
}

bool TListaPoro::operator==(TListaPoro &tlp){ //Compara si son iguales

    TListaNodo* tln_this=this->primero;
    TListaNodo* tln_tlp=tlp.primero;
    
    while(tln_this!=NULL && tln_tlp!=NULL){ //Recorre ambas listas

        if(tln_tlp->e!=tln_this->e){ //Si algun nodo no son iguales devolverá false
            return false;
        }

        tln_this=tln_this->siguiente; //Salta a la siguiente posición
        tln_tlp=tln_tlp->siguiente; //Salta a la siguiente posición

    }
    return true;
}

TListaPoro TListaPoro::operator+(TListaPoro &tlp){
    TListaPoro *list_mas; //lista nueva
    if(tlp.EsVacia()){ //comprueba pasada por parametro no vacia
        list_mas=this; //Si esta vacia se copiará this object
    }
    else if(this->EsVacia()){ //Si esta vacia this object
        list_mas=&tlp; //Se copiará el objeto pasado por parametro
    }
    else{
        list_mas=this; //copiamos los valores de this object
        TListaPosicion pos=tlp.Primera(); //asigna la primera posición de la lista por parametro
        while(pos.pos!=NULL){ // rescorremos la lista pasada por parametro
            list_mas->Insertar(pos.pos->e); //inserta los valores que no se encuentren en la lista, no repetidos

            pos=pos.Siguiente();//pasa al nodo siguiente de la lista
        }
    }
    return *list_mas;
}

TListaPoro TListaPoro::operator-(TListaPoro &tlp){
    TListaPoro *list_menos; //lista nueva
    
    list_menos=this; //copiamos los valores de this object
    TListaPosicion pos=tlp.Primera(); //asigna la primera posición de la lista por parametro
    while(pos.pos!=NULL){ // rescorremos la lista pasada por parametro
        //cout<<"a"<<endl;
        if(this->Buscar(pos.pos->e)){ //Busca el nodo de la lista pasada por parametro
            list_menos->Borrar(pos.pos->e); //borra el nodo de la lista
        }

        pos=pos.Siguiente(); //pasa al nodo siguiente de la lista
    }
    
    return *list_menos;
}

bool TListaPoro::EsVacia() const{
    if(this->primero==NULL){ //compruba que la primera posición sea NULL
        return true;
    }
    if(this->primero->e.EsVacio() && this->ultimo->e.EsVacio()){ //comprueba que los TPoros primeo y ultimo sean sean vacios

        return true;
    }
    return false;
}

bool TListaPoro::Insertar(TPoro &tlp){ 
    if(this->EsVacia()){ //Si la lista esta vacia, introduce en la primera posición
        
        TListaNodo* nuevo = new TListaNodo(); //Crea nuevo nodo
        nuevo->e = tlp; //Copia los valores del nodo pasado por parametro
        nuevo->siguiente = NULL;
        nuevo->anterior = NULL;
        
        this->primero = nuevo; //asigna a primera posición
        this->ultimo = nuevo;
    
        return true;
    }
    else if(this->Buscar(tlp)){ //Si el nodo ya existe en la lista no lo insertará
        return false;
    }
    else{ //No exite en la lista

        TListaPosicion pos_tlp = this->Primera(); //Primera posición de la lista

        while (pos_tlp.pos != NULL) { //Recorre toda la lista
            if (tlp.Volumen() < pos_tlp.pos->e.Volumen()) { //si el Volumen es menos al nodo actual

                TListaNodo* nuevo = new TListaNodo(); //crea nodo
                nuevo->e = tlp; //Copia los valores del nodo pasado por parametro

                nuevo->siguiente = pos_tlp.pos; //enlaza los nodos nuevo y actual
                

                if (pos_tlp.pos->anterior != NULL) { //Si la psoción anterior a la actual no es NULL
                    pos_tlp.pos->anterior->siguiente = nuevo; //Se enlaza siguiente del anterior de la posición actual y nuevo
                    nuevo->anterior = pos_tlp.pos->anterior; //enlaza los anterior del actual y nodos nuevo
                }
                else{
                    pos_tlp.pos->anterior=nuevo;
                    nuevo->anterior = NULL;
                    this->primero=nuevo;
                }
                
                return true;
            }

            pos_tlp = pos_tlp.Siguiente();
        }
        //Lo inserta al final de la lista
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
    
    if(!this->Buscar(tlp)){ //Comprueba que exista
        return false;
    }
    
    TListaPosicion pos_tlp=this->Primera();

    while (pos_tlp.pos!=NULL){ //Recorre toda la lista
        
        if(pos_tlp.pos->e==tlp){ //Si encuentra el nodo
            
            if(!pos_tlp.pos->anterior && !pos_tlp.pos->siguiente){ //Si tanto el anterior y el siguiente son null lo deja vacio
                this->primero=NULL;
                this->ultimo=NULL;
            }
            else if(!pos_tlp.pos->anterior){ //si el anterior es null elimina el primer nodo
                this->primero=this->primero->siguiente;
                this->primero->anterior=NULL;
            }
            else if(!pos_tlp.pos->siguiente){ //si el último es null elimina el primer nodo
                this->ultimo=this->ultimo->anterior;
                this->ultimo->siguiente=NULL;
            }
            else{ //En caso que se encuentre el medio
                pos_tlp.pos->anterior->siguiente=pos_tlp.pos->siguiente ? pos_tlp.pos->siguiente: NULL; 
                pos_tlp.pos->siguiente->anterior=pos_tlp.pos->anterior ? pos_tlp.pos->anterior: NULL;
            }
            
            return true;

        }

        pos_tlp=pos_tlp.Siguiente(); //salta al siguiente nodo
    }

    return false;
}

bool TListaPoro::Borrar(TListaPosicion &tlp){ //Bora TlistaPosicion

    if(!this->Buscar(tlp.pos->e)){ //Comprueba que exista 
        return false;
    }

    if(tlp.EsVacia()){ //Si esta vacia
        return false;
    }
    return this->Borrar(tlp.pos->e); //Llama al metodo Borrar(TPoro)
    
}

TPoro TListaPoro::Obtener(TListaPosicion &tlp){ 
    if(!tlp.EsVacia() && this->Buscar(tlp.pos->e)){ //No este vacio y existe en la lista
        TPoro *pos_p;

        TListaPosicion pos_tlp=this->Primera();

        while (pos_tlp.pos!=NULL){ //Recorre la lista
            if(pos_tlp==tlp){ //si lo encuentra
                if(pos_tlp.pos->e.EsVacio()){ //Si es un TPoro vacio
                    pos_p=new TPoro(); //TPoro Vacio
                    break;
                }
                else{
                    pos_p=&pos_tlp.pos->e; //Se copia el nodo
                    break;
                }
            }
            pos_tlp=pos_tlp.Siguiente(); //Salto de nodo
        }
        return *pos_p;
    }
    else{
        return TPoro();
    }
}

bool TListaPoro::Buscar(TPoro &tlp){ //Busca si existe el nodo

    TListaPosicion pos_tlp=this->Primera();
    while (pos_tlp.pos!=NULL){ //Recorre toda la lista
        if(pos_tlp.pos->e==tlp){ //si lo encuentra devuelve true
            return true;
        }
        pos_tlp=pos_tlp.Siguiente(); //salta al siguiente nodo 
    }
    return false;
}

int TListaPoro::Longitud() const { //devuelve la posición de la lista
    
    if(this->EsVacia()){ //Si está vacía devuelve 0
        return 0;
    }

    TListaPosicion tlp=this->Primera();

    int i=0;

    while (tlp.pos!=NULL){ //Recorre la lista e incrementas el contador de nodos i
        i++;
        tlp=tlp.Siguiente();
    }

    return i;
}

TListaPosicion TListaPoro::Primera() const { //Devuelve un objeto TListaPosición que apunta al primer nodo de la lista
    TListaPosicion tlp=TListaPosicion();
    tlp.pos=this->primero;
    return tlp;
}

TListaPosicion TListaPoro::Ultima() const { //Devuelve un objeto TListaPosición que apunta al ultimo nodo de la lista
    TListaPosicion tlp=TListaPosicion();
    tlp.pos=this->ultimo;
    return tlp;
}

TListaPoro TListaPoro::ExtraerRango (int n1, int n2){
    TListaPoro rang_tlp;
    if(n2<n1){ //Si inicio del rango es mayor que el final del rango, devuelve una lista vacia
        return rang_tlp;
    }
    for(int i=1;i<=this->Longitud();i++){ //recorre la lista 
        
        TListaPosicion pos_tlp=TListaPosicion();
        pos_tlp=this->Primera();

        if(i<=n2 && i>=n1){ //Se encuentra en dentro del intervalo insertará los nodos en la nueva lista
            rang_tlp.Insertar(pos_tlp.pos->e);
        }

        pos_tlp=pos_tlp.Siguiente(); //Salta a la siguiente nodo
        
    }
    return rang_tlp;

}
