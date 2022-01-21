#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <limits>
#pragma once
#include "Arete.h"
#include "adjacent_matrix.h"


//Les attributs d'une liste d'adjacence sont un dictionnaire 
//(clé = arete, valeur = liste de vertex dont le vertex entrant est la clé) 
//et la dimension du graphe

class adjacent_list {
    
    std::unordered_map<std::string, std::vector<Arete> > aretes_dict ;
   
    int dimension;

    public:

    adjacent_list (std::unordered_map<std::string, std::vector<Arete> > aretes_dict , int dimension);
    std::vector<std::string> get_keys();
    double arete_value(std::string start_label, std::string end_label);
    adjacent_matrix to_matrix(); // passe dans la représentation matricielle
    int get_dimension();
    void print(); // permet d'afficher les arêtes
    std::unordered_map<std::string, std::vector<Arete> > dict();
    std::unordered_map<std::string, int> keys_dict(); // cf.adjacent_matrix
    std::unordered_map<int, std::string> dict_reverse_keys();// cf.adjacent_matrix
    std::vector<std::string> neighbors(std::string origin); //retourne le vecteur des noms des sommets voisins à un sommet origin
};
