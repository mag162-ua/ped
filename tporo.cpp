#include <iostream>

using namespace std;

#include "./../include/tporo.h"

ostream& operator<<(ostream &os,const TPoro &poro){
    if(!poro.EsVacio()){ 
        os.setf(ios::fixed); 
        os.precision( 2 ); 
        
        os<<"("<<poro.x<<", "<<poro.y<<") ";
        os<<poro.Volumen()<<" ";
        
        if(poro.color!=NULL) 
            os<<poro.color; 
        else 
            os<<"-"; 
    } 
    else 
        os << "()"; 
            
    return os; 
}

TPoro::TPoro(){
    this->x=0;
    this->y=0;
    this->volumen=0.0;
    this->color=NULL;
}

TPoro::TPoro(int x, int y, double v){
    this->x=x;
    this->y=y;
    this->volumen=v;
    this->color=NULL;
}

TPoro::TPoro(int x,int y,double v, char *c){
    
    if(c!=NULL){
        char diff=('a'-'A');
        char* min_c= new char;
        int i;
        for(i=0;c[i]!='\0';i++){
            if(c[i]>='A' && c[i]<='Z'){
                min_c[i]= c[i]+diff;
            }
            else{
                min_c[i]= c[i];
            }
        }
        min_c[i+1]='\0';
        this->color=min_c;
    }

    this->x=x;
    this->y=y;
    this->volumen=v;
    this->color=c;
    
}

TPoro::TPoro(const TPoro &tp){
    this->x=tp.PosicionX();
    this->y=tp.PosicionY();
    this->volumen=tp.Volumen();
    this->color=tp.Color();
}

TPoro::~TPoro(){
    this->x=0;
    this->y=0;
    this->volumen=0.0;
    this->color=NULL;
}

TPoro& TPoro::operator=(const TPoro &tp){
    x=tp.PosicionX();
    y=tp.PosicionY();
    volumen=tp.Volumen();
    color=tp.Color();
    return *this;
}

bool TPoro::operator==(const TPoro &tp){
    if(x==tp.PosicionX() && y==tp.PosicionY() && volumen==tp.Volumen() && color==tp.Color()){
        return true;
    }
    else{
        return false;
    }
}

bool TPoro::operator!=(const TPoro &tp){
    if(x==tp.PosicionX() && y==tp.PosicionY() && volumen==tp.Volumen() && color==tp.Color()){
        return false;
    }
    else{
        return true;
    }
}

void TPoro::Posicion(int x,int y){
    this->x=x;
    this->y=y;
}

void TPoro::Volumen(double v){
    this->volumen=v;
}

void TPoro::Color(char *c){
    this->color=c;
}

int TPoro::PosicionX() const{
    return x;
}

int TPoro::PosicionY() const{
    return y;
}

double TPoro::Volumen() const{
    return this->volumen;
}

char* TPoro::Color() const{
    return color;
}

bool TPoro::EsVacio() const{
    if(x==0 && y==0 && volumen==0.0 && color==NULL){
        return true;
    }
    else{
        return false;
    }
}