#include "adjacent_matrix.h"

adjacent_matrix::adjacent_matrix(std::vector< std::vector<double> > matrix, std::unordered_map<std::string, int> dict_keys)
: matrix(matrix),
  dict_keys(dict_keys)
{}


double adjacent_matrix::value(std::string start_vertex, std::string end_vertex){
    int i = dict_keys[start_vertex];
    int j = dict_keys[end_vertex];
    return matrix[i][j];
}

int adjacent_matrix::get_dimension(){
    return matrix.size();
}

void adjacent_matrix::print(){
    std::unordered_map<int, std::string> dict_reverse;
    for (const auto& key : dict_keys){
        dict_reverse[key.second]=key.first;
    }
    std::cout << "   ";
    for (const auto& key : dict_reverse){
        std::cout << key.second << ", ";
    }
    std::cout << std::endl;
    int i =0;
    for (int i = 0; i<matrix.size(); i++){
        int j = 0;
        std::cout << dict_reverse[i] <<"  " ;
        for (int j = 0; j<matrix.size(); j++){
            std::cout << matrix[i][j] << ", ";
        }
        std::cout << std::endl;
    }
}

std::vector< std::vector<double> > adjacent_matrix::get_matrix(){
    return matrix;
}

std::unordered_map<std::string, int> adjacent_matrix::keys_dict(){
    return dict_keys;
}

std::unordered_map<int, std::string> adjacent_matrix::dict_reverse_keys(){
    std::unordered_map<int, std::string> dict_reverse;
    for (const auto& key : dict_keys){
        dict_reverse[key.second]=key.first;
    }
    return dict_reverse;
}