//MARTÍN AZNAR GARCÍA, 51797315G

#include<iostream>
#include<cctype>

using namespace std;

#include "./../include/tporo.h"

ostream& operator<<(ostream &os,const TPoro &poro){ 
    //cout<<poro.PosicionX()<<poro.PosicionY()<<poro.Volumen()<<endl;
    if(!poro.EsVacio()){ //Si no esta vacio
        os.setf(ios::fixed); 
        os.precision( 2 ); 
        
        os<<"("<<poro.x<<", "<<poro.y<<") "; //(x,y)
        os<<poro.Volumen()<<" "; // v
        
        if(poro.color!=NULL) //Si tiene color c
            os<<poro.color; 
        else 
            os<<"-"; //Si no tiene color
    } 
    else 
        os << "()"; //Si esta vacio
            
    return os; 
}

TPoro::TPoro(){ //Constructor por defecto
    this->x=0;
    this->y=0;
    this->volumen=0.0;
    this->color=NULL;
}

TPoro::TPoro(int x, int y, double v){ //Constructor de inicialización
    this->x=x;
    this->y=y;
    this->volumen=v;
    this->color=NULL;
}

TPoro::TPoro(int x,int y,double v, char *c){ //Constructor de inicialización con color
    
    if(c!=NULL){  //Pone las letras mayusculas a minusculas
        char* min_c= new char;
        int i;
        for(i=0;c[i]!='\0';i++){
           min_c[i]=tolower(c[i]);
        }
        min_c[i+1]='\0';
        this->x=x;
        this->y=y;
        this->volumen=v;
        this->color=min_c;
    }
    else{

    this->x=x;
    this->y=y;
    this->volumen=v;
    this->color=c;
    }
    
}

TPoro::TPoro(const TPoro &tp){ //constructor de copia
    this->x=tp.PosicionX();
    this->y=tp.PosicionY();
    this->volumen=tp.Volumen();
    this->color=tp.Color();
}

TPoro::~TPoro(){ //DEstructor
    this->x=0;
    this->y=0;
    this->volumen=0.0;
    this->color=NULL;
}

TPoro& TPoro::operator=(const TPoro &tp){ //Iguala los atributos
    //cout<<"b"<<tp<<endl;
    x=tp.PosicionX();
    y=tp.PosicionY();
    volumen=tp.Volumen();
    color=tp.Color();
    return *this;
}

bool TPoro::operator==(const TPoro &tp){ //Compara que los valores de los atributos sean los mismos
    bool color_=true;
    if(this->color==NULL && tp.Color()==NULL){
        color_=true;
    }
    else if (this->color==NULL || tp.Color()==NULL){
        color_=false;
    }
    else{
        color_=(*color==*tp.color);
    }
    if(x==tp.PosicionX() && y==tp.PosicionY() && volumen==tp.Volumen() && color_){
        return true;
    }
    else{
        return false;
    }
}

bool TPoro::operator!=(const TPoro &tp){ //Compara que los valores de los atributos no sean los mismos
    return !(*this==tp);
}

void TPoro::Posicion(int x,int y){ //asigna la coordenada x y
    this->x=x;
    this->y=y;
}

void TPoro::Volumen(double v){ //asigna el volumen
    this->volumen=v;
}

void TPoro::Color(char *c){ //asigna el color 
    if(c==NULL){
        this->color=c;
    }
    else{
        char* min_c= new char;
        int i;
        for(i=0;c[i]!='\0';i++){
           min_c[i]=tolower(c[i]);
        }
        this->color=min_c;
    }
}

int TPoro::PosicionX() const{ //DEvuelve x
    return x;
}

int TPoro::PosicionY() const{ //Devuelve y
    return y;
}

double TPoro::Volumen() const{ //Devuelve volumen
    return this->volumen;
}

char* TPoro::Color() const{ //Devuelve color
    return color;
}

bool TPoro::EsVacio() const{ //Si esta vacio, valores a 0/NULL
    if(x==0 && y==0 && volumen==0.0 && color==NULL){
        return true;
    }
    else{
        return false;
    }
}