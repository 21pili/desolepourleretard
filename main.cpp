#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <limits>
#include "adjacent_list.h"
#include "Pile.h"
#include "File.h"

//Question 1
//-----------------------------------------------------------------------------------------------------------------------
//cf. classes

//Question 2
//-----------------------------------------------------------------------------------------------------------------------
//La fonction read va s'appliquer aux liste d'adjacence.
//Ligne par ligne, on construit le dictionnaire des aretes. 


std::unordered_map<std::string, std::vector<Arete> > read(std::string filename) {
  std::unordered_map<std::string, std::vector<Arete> > empty;
  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
    std::cerr << "cannot open file '" << filename << "'" << std::endl;
    return empty;
  }
  std::unordered_map<std::string, std::vector<Arete> > aretes_dict;
  std::vector<Arete> arete_list;
  std::string line;
  while(getline(input_file, line)) {
    std::istringstream iss(line);
    std::string string1,string2;
    double value;
    iss>>string1>>string2>>value;
    Arete arete(string1,string2,value);
    arete_list.push_back(arete); 
  }
    for (Arete arete : arete_list){ //Construction du dictionnaire
        std::vector<Arete >  arete_neighbors;
        for(Arete arete_prime : arete_list){
            if(arete.start_label()==arete_prime.start_label()){
                arete_neighbors.push_back(arete_prime); //On trouve les voisins
            }
        }
        std::string name = arete.start_label();
        aretes_dict.insert({name,arete_neighbors});
    }
    return aretes_dict;
  }


//Question 3
//-----------------------------------------------------------------------------------------------------------------------
// Dans la suite nous aurons fréquemment besoin de la fonction neighbors, qui donne les sommets accessibles depuis 
//un sommet i. 

std::vector<int> neighbors(adjacent_matrix& graph, int i){
   std::vector<int> neighbors;
  int dim = graph.get_dimension();
  for (int j = 0;j<dim;j++){
    if (graph.value(graph.dict_reverse_keys()[i],graph.dict_reverse_keys()[j]) != std::numeric_limits<double>::infinity()){

      neighbors.push_back(j);
    }
  }
  return neighbors;
}


//Parcours en profondeur pour la représentation matricielle.

//aux est une fonction récursive qui permet de parcourir en profondeur un graphe connexe.  
//L'algorithme est un parcours en profondeur classique.
//dict_reverse_keys permet de se ramener a des entiers. 

void aux_matrix(adjacent_matrix& graph ,int origin,std::vector<bool>& flags){
  int dim = graph.get_dimension();
  flags[origin] = true;
  std::string origin_label = graph.dict_reverse_keys()[origin];
  std::cout << origin_label << ", ";
  for (int neighbor : neighbors(graph,origin)){
    if (!flags[neighbor]){
      aux_matrix(graph, neighbor, flags);
    }
  }
}

//Pour un graphe non connexe. 

void dfs_matrix(adjacent_matrix& graph){
  int dim = graph.get_dimension();
  std::vector<bool> flags(dim, false);
  for (int i = 0;i < dim; i++ ){
    if (!flags[i]){
      aux_matrix(graph,i,flags);
    }
  }
  std::cout << std::endl;
}

//Parcours en profondeur pour la représentation par liste d'adjacence. 
//De manière analogue

std::vector<int> neighbors_list(adjacent_list& graph,int& origin){
  std::vector<int> neighbors;
  for(std::string neighbor:graph.neighbors(graph.dict_reverse_keys()[origin])){
    neighbors.push_back(graph.keys_dict()[neighbor]);
  }
  return neighbors;
}

void aux_list(adjacent_list& graph , int& origin, std::vector<int>& flags){
  int dim = graph.get_dimension();
  std::cout << graph.get_keys()[origin] << ", ";
  flags[origin] = 1;
  for (int neighbor : neighbors_list(graph,origin)){
    if (flags[neighbor]!=1){
      aux_list(graph, neighbor, flags);
    }
  }
}


void dfs_list(adjacent_list& graph){
  int dim = graph.get_dimension();
  std::vector<int> flags(dim,0);

  for (const auto& key : graph.keys_dict()){
    if (flags[graph.keys_dict()[key.first]]!=1){
      aux_list(graph,graph.keys_dict()[key.first],flags);
    }
  }
  std::cout << std::endl;
}


//Question 4
//-----------------------------------------------------------------------------------------------------------------------

// Parcours en profondeur itératif avec la représentation matricielle et une pile. 
// C'est le même algorithme qu'en récursif. 
void dfs_pile_matrix(const std::string& origin_label, adjacent_matrix& graph){
    int origin = graph.keys_dict()[origin_label];
    Pile pile(graph.get_dimension());
    std::vector<bool> flags(graph.get_dimension(), false);
    pile.push(origin);
    flags[origin] = true;
    while (!pile.is_empty()) {
      int vertex = pile.pop(); 
      std::cout << graph.dict_reverse_keys()[vertex] <<" -> "; 
      for (int neighbor: neighbors(graph,vertex)){ 
        if (!flags[neighbor]) {
          pile.push(neighbor); 
          flags[neighbor] = true;
        }
      }
    }
    std::cout << std::endl;
  }


// Parcours en profondeur itératif pour une représentation par liste d'adjacence et une pile. 

void dfs_pile_list(const std::string& origin, adjacent_list& graph){
    Pile pile(graph.get_dimension());
    std::vector<int> flags(graph.get_dimension(), 0);
    pile.push(graph.keys_dict()[origin]);
    flags[graph.keys_dict()[origin]] = 1;
    while (!pile.is_empty()) {
      int vertex = pile.pop();
      std::cout << graph.dict_reverse_keys()[vertex] <<" -> ";
      for (int neighbor: neighbors_list(graph,vertex)){
        if (flags[neighbor]!=1) {
          pile.push(neighbor);
          flags[neighbor] = 1;
        }
      }
    }
    std::cout << std::endl;
  }


//Question 5
//-----------------------------------------------------------------------------------------------------------------------
// Parcours en largeur avec la représentation matricielle
//C'est le même algorithme que dfs sauf que l'on remplace la pile par une file.
//Pour conserver l'information de la profondeur d'un sommet on construit deux
//piles en parallèle, l'une contient les sommets, l'autre leur profondeur, ainsi on peut
//s'arrêter dès que la profondeur maximale est atteinte. 

int bfs_matrix(const std::string& origin_label, adjacent_matrix& graph, int depth_max){
    int origin = graph.keys_dict()[origin_label];
    int dim = graph.get_dimension();
    std::vector<bool> flags(dim, false);
    File vertexes(dim+1); 
    File depths(dim+1);  
    vertexes.push(origin);
    depths.push(0);
    flags[origin] = true;
    while (!vertexes.is_empty()){
      int vertex = vertexes.pull();
      int depth_vertex = depths.pull();
      std::cout << graph.dict_reverse_keys()[vertex] << "," << depth_vertex << " -> ";
      if (depth_vertex == depth_max){ 
        return EXIT_SUCCESS;
      }
      for (int neighbor : neighbors(graph,vertex)){
        if (!flags[neighbor]) {
          vertexes.push(neighbor);
          depths.push(depth_vertex+1);
          flags[neighbor] = true;
        }
      }
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
  }

// Parcours en largeur avec la représentation en liste d'adjacence. 
// De manière analogue, 

int bfs_list(const std::string& origin, adjacent_list& graph, int depth_max){
    int dim = graph.get_dimension();
    std::vector<bool> flags(dim, false);
    File vertexes(dim+1);
    File depths(dim+1);  
    vertexes.push(graph.keys_dict()[origin]);
    depths.push(0);
    flags[graph.keys_dict()[origin]] = true;
    while (!vertexes.is_empty()){ 
      int vertex = vertexes.pull();
      int depth_vertex = depths.pull();
      std::cout << graph.get_keys()[vertex] << "," << depth_vertex << " -> ";
      if (depth_vertex == depth_max){ 
        return EXIT_SUCCESS;
      }
      for (int neighbor : neighbors_list(graph,vertex)){
        if (!flags[neighbor]) {
          vertexes.push(neighbor);
          depths.push(depth_vertex+1);
          flags[neighbor] = true;
        }
      }
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
  }

//Question 6
//-----------------------------------------------------------------------------------------------------------------------

// On utilisera la fonction suivante. 

bool false_remaining(std::vector<bool>& flags){
  int size = flags.size();
  for (int i =0;i<size;i++){
    if (!flags[i]){
      return true;
    }
  }
  return false;
}

// On réalise une recherche de distance minimum parmis les sommets tels que flags[sommet] = false

int vertex_min( std::vector<bool>& flags, adjacent_matrix& graph, std::vector<double>& distances){
  int dim = graph.get_dimension();
  double min_distance = std::numeric_limits<double>::infinity(); //on initialise la distance minimale à l'infini
  int min_vertex = -1;
  for (int j = 0;j<dim;j++){ //On recherche ici la distance minimale
    if ((!flags[j]) and (distances[j] <= min_distance)){
        min_distance = distances[j];
        min_vertex = j;
    }
  } 
  return min_vertex;
}

// On implémente alors Dijkstra. 

void Dijkstra(adjacent_matrix& graph,const std::string& origin_label){
  int origin = graph.keys_dict()[origin_label];
  int dim = graph.get_dimension();
  std::vector<bool> flags(dim,false);
  std::vector<double> distances(dim,std::numeric_limits<double>::infinity());
  std::vector<std::vector<int> > previous(dim, std::vector<int>(dim,-1));
  std::vector<int> preOrigin;
  previous[0].push_back(graph.keys_dict()[origin_label]);
  distances[origin] = 0;
  while (false_remaining(flags)){ 
    int a = vertex_min(flags, graph, distances);
    flags[a] = true;
    for (int neighbor:neighbors(graph,a)){
      if (!flags[neighbor]){
        if ( (distances[neighbor] > distances[a] + graph.value(graph.dict_reverse_keys()[a],graph.dict_reverse_keys()[neighbor]) ) ){
          distances[neighbor] = distances[a] + graph.value(graph.dict_reverse_keys()[a],graph.dict_reverse_keys()[neighbor]);
          previous[neighbor].push_back(a);
        }
      }
    }
  }
  for (int i=0;i<distances.size();i++){
    std::cout << "distance mini de " << origin_label << " -> " << graph.dict_reverse_keys()[i] << " : " << distances[i] << std::endl;
  }
}

//Question 7
//-----------------------------------------------------------------------------------------------------------------------

//Nous utiliserons la fonction min

double min(double x, double y){
  if(x<y){
    return x;
  }
  else{
    return y;
  }
}
//Classiqument, 

void floyd_warshall(adjacent_matrix& graph){
  int dim = graph.get_dimension();
  std::vector< std::vector< double > > matrix(dim, std::vector<double>(dim));
  matrix = graph.get_matrix();
  for (int k=0;k<dim ;k++){
    for (int i=0;i<dim ;i++){
      for (int j=0;j<dim;j++){
        matrix[i][j] = min(matrix[i][j],matrix[i][k] + matrix[k][j]); 
      }
    }
  }
  //Il reste à afficher la matrice... 
  std::unordered_map<int, std::string> reverse_dict;
    std::cout << "   ";
    for (const auto& key : graph.keys_dict()){
        reverse_dict[key.second]=key.first;
        std::cout << key.first << ", ";
    }

    /*for (const auto& key : reverse_dict){
        std::cout << key.second << ", ";
    }*/
    std::cout << std::endl;

  int i =0;
    for (int i = 0; i<matrix.size(); i++){
        std::cout << reverse_dict[i] <<"  " ;
        int j = 0;
        for (int j = 0; j<matrix.size(); j++){
            std::cout << matrix[i][j] << ", ";
        }
        std::cout << std::endl;
    }
}

//Pour un peu de mise en forme...

void ligne(){
  for (int i=0;i<50;i++){
    std::cout<< "-";
  }
  std::cout << std::endl;
}

void star(){
  for (int i=0;i<50;i++){
    std::cout<< "*";
  }
  std::cout << std::endl;
}

void print(std::string str){
  std::cout << str;
}

void testgraph(std::string filename){
  //Question1 et Question2
  // On lit le fichier test.graph et on créé un dictionnaire
  std::unordered_map<std::string, std::vector<Arete> > dictionary= read(filename);
  star();
  star();
  std::cout << filename << std::endl;
  star();
  star();
  std::cout << "Questions 1 et 2" << std::endl;
  ligne();
  adjacent_list graph(dictionary, dictionary.size()); 
  std::cout << "Représentation par liste d'adjacence" << std::endl;
  std::cout << std::endl;
  graph.print();
  std::cout << std::endl;
  std::cout << "Représentation matricielle" << std::endl;
  std::cout << std::endl;
  adjacent_matrix mgraph= graph.to_matrix();
  mgraph.print();
  std::cout << std::endl;
  std::unordered_map<int, std::string> keys_dictR = mgraph.dict_reverse_keys();
  std::cout << std::endl;
  ligne();
  std::cout << "Question 3: Parcours en profondeur récursif" << std::endl;
  ligne();
  std::cout << std::endl;


  std::cout << "Représentation matricielle: " << std::endl;
  std::cout << std::endl;
  std::cout << "Un chemin : " << std::endl;
  dfs_matrix(mgraph);
  std::cout << std::endl;


  std::cout << "Représentation par liste d'adjacence: " << std::endl;
  std::cout << std::endl;
  std::cout << "Un chemin : " << std::endl;
  dfs_list(graph);

  std::cout << std::endl;
  ligne();
  std::cout << "Question 4: Parcours en profondeur itératif" << std::endl;
  ligne();
  std::cout << std::endl;

  std::cout << "Représentation matricielle: " << std::endl;
  dfs_pile_matrix("d",mgraph);

  std::cout << std::endl;
  std::cout << "Représentation par liste d'adjacence: " << std::endl;
  dfs_pile_list("d", graph);


  std::cout << std::endl;
  ligne();
  std::cout << "Question 5: Parcours en largeur" << std::endl;
  ligne();
  std::cout << std::endl;

  std::cout << "Représentation matricielle: " << std::endl;
  std::cout << "sommet, profondeur" << std::endl;
  bfs_matrix("d", mgraph, 5);

  std::cout << std::endl;
  std::cout << "Représentation par liste d'adjacence: " << std::endl;
  std::cout << "sommet, profondeur" << std::endl;
  bfs_list("d", graph, 5);

  std::cout << std::endl;
  ligne();
  std::cout << "Question 6: Dijkstra" << std::endl;
  ligne();
  std::cout << std::endl;
  Dijkstra(mgraph,"a");

  std::cout << std::endl;
  ligne();
  std::cout << "Question 7: FloydWarshall " << std::endl;
  ligne();
  std::cout << std::endl;
  std::cout << "matrice[i,j] = poids i -> j" << std::endl;
  std::cout << std::endl;
  floyd_warshall(mgraph);
  }

int main(){
  testgraph("test0.graph");
  testgraph("test1.graph");
  testgraph("test2.graph");
  testgraph("test3.graph");
  testgraph("test4.graph");
}