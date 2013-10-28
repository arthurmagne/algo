#include <iostream>
#include <string>
#include "Graph.hpp"

using namespace std;

Graph::Graph()
{
}

Graph::~Graph(){
    //delete vertexes;
    //delete edges;
}

int Graph::get_number_of_vertexes(){
    return this->vertexes.size();
}

vector<Vertex*>::iterator  Graph::get_iterator_begin(){
    return this->vertexes.begin();
}

vector<Vertex*>::iterator  Graph::get_iterator_end(){
    return this->vertexes.end();
}


Graph* Graph::generate_graph(int number_of_vertexes, double p){
    // seed rand
    srand(time(NULL));

    Graph * graph = new Graph();

    // we add all the vertexes in the structure
    for (int i=0; i<number_of_vertexes ; i++){
        Vertex * vertex = new Vertex(i);
        graph->vertexes.push_back(vertex);
    }

    // we create an edge between two vertexes with the probabitity p
    for (vector<Vertex*>::iterator current = graph->vertexes.begin() ; current != graph->vertexes.end(); ++current){
        for (vector<Vertex*>::iterator it = graph->vertexes.begin() ; it != graph->vertexes.end(); ++it){
            if ( (rand() % 100) < (p*100) ){
                if ((*current)->get_key() != (*it)->get_key()){
                    Edge * edge = new Edge(*current, *it);
                    graph->edges.push_back(edge);
                    (*current)->add_neighbour(*it);
                }
            }
        }
    }
    return graph;
}
