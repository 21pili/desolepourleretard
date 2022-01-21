#include <iostream>
//On reprend l'implémentation classique d'une file à l'aide d'un tableau
class File {

    int size; 
    int deb; 
    int fin; 
    int* tab;

    public:

    File(int s);
    ~File(){
        delete[] tab;
    }
    File(const File &r):
        size(r.size),
        deb(r.deb),
        fin(r.fin),
        tab(new int[size]){}
    void push (int e);
    int pull();
    int size_file();
    bool is_empty();
    bool is_full();
    void print();
    File operator=(const File& r){
        {size= r.size;
        deb = r.deb;
        fin = r.fin;
        delete[] tab;
        tab= new int[size];}
        return *this;
    }
};