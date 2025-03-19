#include <iostream>

using namespace std;

#include "./../include/tporo.h"
#include "./../include/tvectorporo.h"

ostream& operator<<(ostream &os, TVectorPoro &tvp){
    os<<"[";
    for(int i=0;i<tvp.dimension;i++){
        if(!(tvp.datos[i].EsVacio())){
            os<<i+1<<" "<<tvp.datos[i];
            if(i!=tvp.dimension-1){
                os<<" ";
            }
        }
        
    }
    os<<"]";
    return os;
}

TVectorPoro::TVectorPoro(){ //Constructor por defecto
    this->datos=NULL;
    this->dimension=0;
    this->error=TPoro();
}

TVectorPoro::TVectorPoro(int n){ //Constructor de iniciación
    if(n<=0){
        this->datos=NULL;
        this->error=TPoro();
        this->dimension=0;
    }
    else{
        this->datos=new TPoro[n];
        this->dimension=n;
    }

}

TVectorPoro::TVectorPoro(TVectorPoro &tvp){ //Constructor de copia
    this->error=TPoro();
    this->dimension=tvp.dimension;
    for (int i = 0; i < this->dimension; i++) { //Copia los elementos
        this->datos[i] = TPoro(tvp.datos[i]);  
    }
}

TVectorPoro::~TVectorPoro(){ //Destructor
    this->dimension=0;
    delete[] this->datos;
}

TVectorPoro& TVectorPoro::operator=(const TVectorPoro &tvp){ //Copia los TPoro
    if(tvp.datos!=NULL){ //Si no es vacio
        delete [] this->datos;
        this->datos=new TPoro[tvp.dimension]; //Redimensiona el vector
    }

    this->dimension=tvp.dimension;
    for (int i = 0; i < this->dimension; i++) { //Copia los elementos
        this->datos[i] = TPoro(tvp.datos[i]);  
    }
    
    return *this;
}

bool TVectorPoro::operator==(const TVectorPoro &tvp){ //Compara que todas los valores sean iguales
    if(this->dimension==tvp.dimension){ 
        for(int i=0;i<this->dimension;i++){
            if(this->datos[i]!=tvp.datos[i]){ //Si encuentra uno que sea diferente
                return false;
            }
        }
    }
    else{
        return false;
    }
    return true;
}

bool TVectorPoro::operator!=(const TVectorPoro &tvp){ //Compara que al menos un valor sea distinto
    if(this->dimension==tvp.dimension){
        for(int i=0;i<this->dimension;i++){
            if(this->datos[i]!=tvp.datos[i]){ //si es distinto 
                return true;
            }
        }
    }
    else{
        return true;
    }
    return false;
}

TPoro& TVectorPoro::operator[](int n){ //Accede a la posición n-1 del vector
    if(n>this->dimension){
        return this->error;
    }
    return this->datos[n-1];
}

TPoro TVectorPoro::operator[](int n) const{ //Accede a la posición n-1 del vector
    if(n>this->dimension){
        return this->error;
    }
    return this->datos[n-1];
}

int TVectorPoro::Longitud() const{ //Devuelve la dimension del vector
    return this->dimension;
}

int TVectorPoro::Cantidad() const{ //Devuelve el numero de Tporos no vacios
    int i;
    for(i=0;i<this->dimension;i++){
        if(this->datos[i]==this->error){
            break;
        }
    }
    return i;
    
}

bool TVectorPoro::Redimensionar(int n){ //Modifica la longitud del vector
    if(n<=0 || n==this->dimension){ 
        return false;
    }
    
    int longi=this->dimension; 
    TPoro auxtp[this->dimension];

    for(int i=0;i<this->dimension;i++){ //copia de los valores de this en auxiliar
        auxtp[i]=this->datos[i];
    }
    
    if(n>0 && n<this->dimension){ //si n es >0 y < this->dimension rellenará 
        this->dimension=n;
        delete(this->datos);
        this->datos=new TPoro[n]; //Redimensiona el vector

        for(int i=0; i<this->dimension; i++){ //Copia los valores de auxiliar en this
            this->datos[i]=auxtp[i];
        }
        return true;
    }
    else{
        this->dimension=n;
        delete(this->datos);
        this->datos=new TPoro[n]; //Redimensiona el vector

        for(int i=0;i<n;i++){ //recorre todas las posiciones de n
            if(i>=longi){
                this->datos[i]=TPoro(); //Si la posición es mayor a la longitud original del vector se rrellana con Tporo Vacio
            }
            else{
                this->datos[i]=auxtp[i]; //Copia de auxiliar
            }
        }
        return true;
    }
}