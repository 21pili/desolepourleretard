#include "Arete.h"


Arete::Arete(std::string start_vertex, std::string end_vertex, double value_arete):
    start_vertex(start_vertex),
    end_vertex(end_vertex),
    value_arete(value_arete)
{}

double Arete::value(){
    return value_arete;
}

std::string Arete::start_label(){
    return start_vertex;
}

std::string Arete::end_label(){
    return end_vertex;
}
