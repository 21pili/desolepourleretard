#include "Pile.h"

Pile::Pile(int s):
    sizemax(s),
    size(0),
    tab(new int [s])
{}

void Pile::push(int e){
    if (size!=sizemax){
        tab[size]=e;
        size=size+1;
    }
}

int Pile::pop(){
    if(size!=0){
        size=size-1;
        return tab[size];
    }
    throw "NON";
}

int Pile::size_pile(){
    return size;
}

bool Pile::is_empty(){
    return size==0;
}

bool Pile::is_full(){
    return size==sizemax;
}

void Pile::print(){
    for(int i=0; i<size; i++){
        std::cout << tab[i] << ',';
    }
    std::cout << std::endl;
}