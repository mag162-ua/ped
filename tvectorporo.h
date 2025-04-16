#ifndef TVectorPoro_
#define TVectorPoro_

class TVectorPoro{
    friend ostream& operator<<(ostream &os,const TVectorPoro &tvp);
    
    private:
        int dimension;
        TPoro *datos;
        TPoro error;
    public:
        TVectorPoro();
        TVectorPoro(int n);
        TVectorPoro(TVectorPoro &tvp);
        ~TVectorPoro();
        TVectorPoro& operator=(const TVectorPoro &tvp);

        bool operator==(const TVectorPoro &tvp);
        bool operator!=(const TVectorPoro &tvp);
        TPoro& operator[](int n);
        TPoro operator[](int n) const;
        int Longitud() const;
        int Cantidad() const;
        bool Redimensionar(int n);
};

#endif
