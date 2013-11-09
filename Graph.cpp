#include <iostream>
#include <string>
#include <algorithm>
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

vector<Vertex *> Graph::get_vertexes_copy(){
    return this->vertexes;
}

vector<Edge *> Graph::get_edges_copy(){
    return this->edges;
}


/* Generation functions */

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
                    (*it)->add_neighbour(*current);
                }
            }
        }
    }
    return graph;
}

Graph* Graph::generate_bipartite_graph(int number_of_vertexes, double p){
    // seed rand
    srand(time(NULL));

    Graph * graph = new Graph();
    vector<Vertex*> partA;
    vector<Vertex*> partB;

    // we add all the vertexes in the structure
    for (int i=0; i<number_of_vertexes ; i++){
        Vertex * vertex = new Vertex(i);
        graph->vertexes.push_back(vertex);
        // we split our vertexes in two parts randomly
        if ((rand() % 100) < 50)
            partA.push_back(vertex);
        else
            partB.push_back(vertex);
    }

    // now, we create with a probability p some edges between vertexes in partA and partB
    for (vector<Vertex*>::iterator partAVertex = partA.begin() ; partAVertex != partA.end(); ++partAVertex){
        for (vector<Vertex*>::iterator partBVertex = partB.begin() ; partBVertex != partB.end(); ++partBVertex){
            if ( (rand() % 100) < (p*100) ){
                Edge * edge = new Edge(*partAVertex, *partBVertex);
                graph->edges.push_back(edge);
                (*partAVertex)->add_neighbour(*partBVertex);
                (*partBVertex)->add_neighbour(*partAVertex);
            }
        }
    }
    return graph;
}

Graph* Graph::generate_graph_with_min_cover(int number_of_vertexes, int cover_size, double p){
    if (cover_size > number_of_vertexes){
        cout << "The cover's size can't be bigger than the number of vertexes" << endl;
        return NULL;
    }

    // seed rand
    srand(time(NULL));

    Graph * graph = new Graph();

    // we add all the vertexes in the structure
    for (int i=0; i<number_of_vertexes ; i++){
        Vertex * vertex = new Vertex(i);
        graph->vertexes.push_back(vertex);
    }

    // shuffle randomly the vertexes of our graph
    // Complexity : Linear in the number of vertexes
    random_shuffle(graph->vertexes.begin(), graph->vertexes.end());

    /* ------ */
    /* only if we need the cover */
    vector<Vertex*> cover(graph->vertexes.begin(), graph->vertexes.begin()+cover_size);
    /* ------ */

    cout << endl << "La couverture du graphe est : ";
    // we create an edge between two vertexes with the probabitity p
    // with the first vertex taken in the cover: the "cover_size" first vertexes randomly shuffle previously
    // then we don't have to create a new subvector with the cover ? Do we need this?
    for (vector<Vertex*>::iterator current = graph->vertexes.begin() ; current != graph->vertexes.begin() + cover_size; ++current){
        for (vector<Vertex*>::iterator it = graph->vertexes.begin() ; it != graph->vertexes.end(); ++it){
            if ( (rand() % 100) < (p*100) ){
                if ((*current)->get_key() != (*it)->get_key()){
                    Edge * edge = new Edge(*current, *it);
                    graph->edges.push_back(edge);
                    (*current)->add_neighbour(*it);
                    (*it)->add_neighbour(*current);
                }
            }
        }
        cout << (*current)->get_key() << " ";
    }
    cout << endl;
    return graph;
}

