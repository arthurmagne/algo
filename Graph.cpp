#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "Graph.hpp"
#include "Utils.hpp"

using std::cout;
using std::endl;
using std::ifstream;

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

vector<Vertex *> &Graph::get_vertexes(){
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
        for (vector<Vertex*>::iterator it = current ; it != graph->vertexes.end(); ++it){
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
    vector<int> randomCover;
    // we add all the vertexes in the structure
    for (int i=0; i<number_of_vertexes ; i++){
        Vertex * vertex = new Vertex(i);
        graph->vertexes.push_back(vertex);
        randomCover.push_back(i);
    }

    // shuffle randomly the vertexes of our graph
    // Complexity : Linear in the number of vertexes
    // pause probleme pour la copie de graph !!!!!!!!!!!
    //random_shuffle(graph->vertexes.begin(), graph->vertexes.end());

    random_shuffle(randomCover.begin(), randomCover.end());

    /* ------ */
    /* only if we need the cover */
    //vector<Vertex*> cover(graph->vertexes.begin(), graph->vertexes.begin()+cover_size);
    /* ------ */

    cout << endl << "La couverture du graphe est : ";
    // we create an edge between two vertexes with the probabitity p
    // with the first vertex taken in the cover: the "cover_size" first vertexes randomly shuffle previously
    for (vector<int>::iterator cpt = randomCover.begin() ; cpt != randomCover.begin() + cover_size; ++cpt){
        Vertex* current = graph->vertexes.at(*cpt);
        for (vector<Vertex*>::iterator it = graph->vertexes.begin() ; it != graph->vertexes.end(); ++it){
            if ( (rand() % 100) < (p*100) ){
                if (current->get_key() != (*it)->get_key()){
                    Edge * edge = new Edge(current, *it);
                    graph->edges.push_back(edge);
                    current->add_neighbour(*it);
                    (*it)->add_neighbour(current);

                }
            }
        }
        cout << current->get_key() << " ";
    }
    cout << endl;
    return graph;
}



Graph * Graph::generate_graph_from_file(char* filename){

    if(Utils::detect_cycle(filename))
        cout << "cycle" <<endl;

    int num_vert=0;
    vector<char *> v;
    ifstream fin;
    fin.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    Graph * g = new Graph();
    vector<Vertex *> ver;
    vector<Edge *> e;
    int size = 0;
    int loop = 0;
    int nb_vertices = 0;
    /* Chaque tour de boucle correspond à une ligne du document texte contenant la liste d'adjacence*/
    while (!fin.eof()){
      char str[20];
      fin.getline(str, 20);
      /* Premier tour de boucle, on recupere le nombre de sommets*/
      if(loop++ == 0){
        char* line_token[10] = {};
        line_token[0] = strtok(str, " :");
        nb_vertices = atoi(line_token[0]);
      /* On cree les sommets du graphe*/
        for(int i = 0; i< nb_vertices; i++)
            ver.push_back(new Vertex(i));
      }

      /* Deuxieme tour de boucle on récupère la liste d'adjacence ligne par ligne*/
      if(loop>1 && loop<ver.size() + 2){
          char* line_token[10] = {};
          line_token[0] = strtok(str, " :");
          v.push_back(line_token[0]);
          if (line_token[0]){
             for (int n = 1; n < 10; n++){
                line_token[n] = strtok(0, " :");
                if (!line_token[n])
                  break;
                v.push_back(line_token[n]);
        }
      }

    /* Pour chaque ligne, on crée les arretes correspondantes et on ajoute les voisins au sommet*/
      if(v.size()>size +1)
         {
             for(int j =1+size; j<v.size(); j++){
                 string sv;
                 if(v[j] != NULL)
                    sv = v[j];
                 int nb = atoi(sv.c_str());
                 e.push_back(new Edge(ver[num_vert], ver[nb]));
                 ver[num_vert]->add_neighbour(ver[nb]);
             }
           }

      size = v.size();
      num_vert++;
    }
}
    /* On affecte les sommets et arretes au graphe*/
    g->edges = e;
    g->vertexes = ver;
    return g;
}

// !!! This function doesn't copy the edges !!!
// !!! Doesn't work if the edges aren't sorted !!!
Graph* Graph::get_graph_copy(){
    Graph* graph_copy = new Graph();

    // we add all the vertexes in the structure
    for (vector<Vertex*>::iterator current = this->vertexes.begin() ; current != this->vertexes.end(); ++current){
        Vertex * vertex = new Vertex((*current)->get_key());
        graph_copy->vertexes.push_back(vertex);

    }
    // we add the neighbours
    for (vector<Vertex*>::iterator current = this->vertexes.begin() ; current != this->vertexes.end(); ++current){
        if ((*current)->get_number_of_neighbours() != 0){
            set<Vertex*> neigh;
            for (set<Vertex*>::iterator it = (*current)->get_neighbours().begin() ; it != (*current)->get_neighbours().end(); ++it){
                // we find the good vertex
                neigh.insert(graph_copy->vertexes.at((*it)->get_key()));
            }
            ((Vertex*)graph_copy->vertexes.at((*current)->get_key()))->get_neighbours() = neigh;
        }
    }
    return graph_copy;
}
