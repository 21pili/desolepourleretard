#include <iostream>

class Pile {

    int sizemax; 
    int size; 
    int* tab; 

    public:

    Pile(int s);
    ~Pile(){
        delete[] tab;
    }
    Pile(const Pile &r):
        sizemax(r.sizemax),
        size(r.size),
        tab(new int[sizemax]){}
    void push (int e); 
    int pop(); 
    int size_pile();
    bool is_empty();
    bool is_full();
    void print();
    Pile operator=(const Pile& r){
        {sizemax= r.sizemax;
        size= r.size;
        delete[] tab;
        tab= new int [sizemax];}
        return *this;
    }
};