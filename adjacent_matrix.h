#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>

//Représentation matricielle telle que matrice[i,j] = poids de i -> j

class adjacent_matrix {
    std::vector< std::vector<double> > matrix;
    std::unordered_map<std::string, int> dict_keys;

    public:

    adjacent_matrix(std::vector< std::vector<double> > matrix, std::unordered_map<std::string, int> keys_dict); 
    double value(std::string start_label, std::string end_label); //retourne la valeur de l'arête de coordonnées (i,j)
    int get_dimension();
    void print(); 
    std::vector< std::vector<double> > get_matrix(); //retourne la matrice
    std::unordered_map<std::string, int> keys_dict(); // dictionnaire liant une étiquette et sa clé
    std::unordered_map<int, std::string> dict_reverse_keys();//dictionnaire réciproque du précédent
};