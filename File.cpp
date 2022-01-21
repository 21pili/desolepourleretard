#include "File.h"

File::File(int size):
    size(size),
    deb(0),
    fin(0),
    tab(new int [size])
{}

int File::size_file(){
    return fin-deb;
}

void File::push(int e){
    if ((deb - fin)%size != 1){
        tab[fin]=e;
        fin = fin+1;
    }
}

int File::pull(){
    if(deb-fin != 0){
        deb=(deb+1)%size;
    }
    return tab[deb-1];
    throw "NO";
}

bool File::is_empty(){
    return fin-deb==0;
}

bool File::is_full(){
    return (fin-deb)%size==1;
}

void File::print(){
    if (deb < fin){
        for(int k=deb; k<fin; k++){
        std::cout << tab[k] << ',';
        }
    }
    else{
        for (int k=deb; k<fin+size; k++){
        std::cout << tab[k%size] << ',';
            }
        }
    std::cout << std::endl;
}