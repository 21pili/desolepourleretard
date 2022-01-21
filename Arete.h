#include <iostream>
#include <cmath>
#include <string>
#include <vector>

class Arete {
    std::string start_vertex; //nom du sommet de départ
    std::string end_vertex; //nom du sommet d'arrivée
    double value_arete; //poids de l'arête

    public:

    Arete(std::string start_vertex, std::string end_vertex, double value_arete);
    Arete();
    double value();
    std::string start_label();
    std::string end_label();
};