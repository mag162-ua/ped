#ifndef TPoro_
#define TPoro_

class TPoro{
    friend ostream& operator<<(ostream &os,const TPoro &tp);
    private:
        int x;
        int y;
        double volumen;
        char* color;
    public:
        TPoro();
        TPoro(int x, int y, double v);
        TPoro(int x,int y,double v, char *c);
        TPoro(const TPoro &tp);
        ~TPoro();
        TPoro& operator=(const TPoro &tp);
        
        bool operator==(const TPoro &tp);
        bool operator!=(const TPoro &tp);
        void Posicion(int x,int y);
        void Volumen(double v);
        void Color(char *c);
        int PosicionX() const;
        int PosicionY() const;
        double Volumen() const;
        char* Color() const;
        bool EsVacio() const;
};

#endif