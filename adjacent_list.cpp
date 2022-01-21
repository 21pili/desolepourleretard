#include "adjacent_list.h"


adjacent_list::adjacent_list(std::unordered_map<std::string, std::vector<Arete> > aretes_dict,int dimension):
    aretes_dict(aretes_dict),
    dimension(dimension)
{}

std::vector<std::string> adjacent_list::get_keys(){
    std::vector<std::string> keys;

    keys.reserve(aretes_dict.size());
    for (const auto& key : aretes_dict){ 
        keys.push_back(key.first);
    }

    return keys;
}

double adjacent_list::arete_value(std::string start_label, std::string end_label){
    for(Arete arete: aretes_dict[start_label]){ 
        if( arete.end_label()!= end_label){ 
            continue;
        }
        else{                          
            return arete.value(); 
        }
    }
    return  std::numeric_limits<double>::infinity(); 
}



adjacent_matrix adjacent_list::to_matrix(){
    int i=0;
    std::vector< std::vector<double> > matrix(dimension, std::vector<double>(dimension));
    std::vector<std::string> keys;
    keys.reserve(aretes_dict.size());
    for (const auto& key : aretes_dict ){
        keys.push_back(key.first);
    }
    
    for(int i =0; i!=dimension; i++ ){
        int j = 0; 
        for(int j =0; j!=dimension; j++ ){
             matrix[i][j]=arete_value(keys[i],keys[j]); 
        }
    }

    std::unordered_map<std::string, int> keys_dict;
    for(int i = 0; i<keys.size(); i++){
        keys_dict[keys[i]]=int(i);
    }    

    return adjacent_matrix(matrix, keys_dict); 
}
int adjacent_list::get_dimension(){
    return dimension;
}

void adjacent_list::print(){
    std::vector<std::string> keys;
    keys.reserve(aretes_dict.size());
    for (const auto& key : aretes_dict ){
        keys.push_back(key.first);
    }
    int i = 0;
    for(int i =0; i!=dimension; i++ ){
        int j = 0; 
        std::cout << keys[i];
        for(int j =0; j!=dimension; j++ ){
            if(arete_value(keys[i],keys[j])==std::numeric_limits<double>::infinity()){
                continue;
            }
            else{
                std::cout << " -> "<< keys[j] << ": " << arete_value(keys[i],keys[j]) << std::endl;
            }
        }
    }
}

std::unordered_map<std::string, std::vector<Arete> > adjacent_list::dict(){
    return aretes_dict;
}

std::unordered_map<std::string, int> adjacent_list::keys_dict(){
    std::unordered_map<std::string, int> dict;
    std::vector<std::string> keys;
    keys.reserve(aretes_dict.size());
    for (const auto& key : aretes_dict){
        keys.push_back(key.first);
    }
    for(int i = 0; i<keys.size(); i++){
        dict[keys[i]]=int(i);
    }
    return dict;
}

std::unordered_map<int, std::string> adjacent_list::dict_reverse_keys(){
    std::unordered_map<int, std::string> dict;
    std::vector<std::string> keys;
    keys.reserve(aretes_dict.size());
    for (const auto& key : aretes_dict){
        keys.push_back(key.first);
    }
    for(int i = 0; i<keys.size(); i++){
        dict[i]=keys[i];
    }
    return dict;
}

std::vector<std::string> adjacent_list::neighbors (std::string origin){ 
    std::vector<std::string> neighbors;
    for(Arete arete : aretes_dict[origin]){
        neighbors.push_back(arete.end_label());
    }
    return neighbors;
}