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

TVectorPoro::TVectorPoro(){
    this->datos=NULL;
    this->dimension=0;
    this->error=TPoro();
}

TVectorPoro::TVectorPoro(int n){
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

TVectorPoro::TVectorPoro(TVectorPoro &tvp){
    this->error=TPoro();
    this->dimension=tvp.dimension;
    for (int i = 0; i < this->dimension; i++) {
        this->datos[i] = tvp.datos[i];  
    }
}

TVectorPoro::~TVectorPoro(){
    this->dimension=0;
    delete[] this->datos;
}

TVectorPoro& TVectorPoro::operator=(const TVectorPoro &tvp){
    if(tvp.datos!=NULL){
        delete [] this->datos;
        this->datos=new TPoro[tvp.dimension];
    }

    this->dimension=tvp.dimension;
    for (int i = 0; i < this->dimension; i++) {
        this->datos[i] = TPoro(tvp.datos[i]);  
    }
    
    return *this;
}

bool TVectorPoro::operator==(const TVectorPoro &tvp){
    if(this->dimension==tvp.dimension){
        for(int i=0;i<this->dimension;i++){
            if(this->datos[i]!=tvp.datos[i]){
                return false;
            }
        }
    }
    else{
        return false;
    }
    return true;
}

bool TVectorPoro::operator!=(const TVectorPoro &tvp){
    if(this->dimension==tvp.dimension){
        for(int i=0;i<this->dimension;i++){
            if(this->datos[i]!=tvp.datos[i]){
                return true;
            }
        }
    }
    else{
        return true;
    }
    return false;
}

TPoro& TVectorPoro::operator[](int n){
    if(n>this->dimension){
        return this->error;
    }
    return this->datos[n-1];
}

TPoro TVectorPoro::operator[](int n) const{
    if(n>this->dimension){
        return this->error;/////////////////////////////////////////////////PREGUNTAR
    }
    return this->datos[n-1];
}

int TVectorPoro::Longitud() const{
    return this->dimension;
}

int TVectorPoro::Cantidad() const{
    int i;
    for(i=0;i<this->dimension;i++){
        if(this->datos[i]==this->error){
            break;
        }
    }
    return i;
    
}

bool TVectorPoro::Redimensionar(int n){
    if(n<=0 || n==this->dimension){
        return false;
    }
    /*if(n>0 && n<this->dimension){
        for(int i=0; i<this->dimension; i++){
            if(i>=n){
                this->datos[i]=TPoro();
            }
        }
        this->dimension=n;
        return true;
    }
    else{
        for(int i=0; i<n; i++){
            if(i>=this->dimension){
                this->datos[i]=TPoro();
            }
        }
        return true;
    }*/


    int longi=this->dimension; 
    TPoro auxtp[this->dimension];

    for(int i=0;i<this->dimension;i++){
        auxtp[i]=this->datos[i];
    }
    
    if(n>0 && n<this->dimension){
        this->dimension=n;
        delete(this->datos);
        this->datos=new TPoro[n];

        for(int i=0; i<this->dimension; i++){
            this->datos[i]=auxtp[i];
        }
        return true;
    }
    else{
        this->dimension=n;
        delete(this->datos);
        this->datos=new TPoro[n];

        for(int i=0;i<n;i++){
            if(i>=longi){
                this->datos[i]=TPoro();
            }
            else{
                this->datos[i]=auxtp[i];
            }
        }
        return true;
    }
}