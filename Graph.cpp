#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "Graph.hpp"

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

vector<Vertex *> &Graph::get_vertexes_copy(){
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

Graph* Graph::get_graph_copy(){
    Graph* graph_copy = new Graph();

    vector<Vertex*> vertexes_copy(this->vertexes);
    vector<Edge*> edges_copy(this->edges);

    graph_copy->vertexes = vertexes_copy;
    graph_copy->edges = edges_copy;
    return graph_copy;
}


Graph * Graph::generate_graph_from_file(char* filename){
    int num_vert=0;
    vector<char *> v;
    ifstream fin;
    fin.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    //if(fin.is_open())
       // cout << "File Open" << endl;
    Graph * g = new Graph();
    vector<Vertex *> ver;
    vector<Edge *> e;
    int size = 0;
    int loop = 0;
    int nb_vertices = 0;
    /** Chaque tour de boucle correspond à une ligne du document texte contenant la liste d'adjacence*/
    while (!fin.eof()){
      char str[20];
      fin.getline(str, 20);
      /** Premier tour de boucle, on recupere le nombre de sommets*/
      if(loop++ == 0){
       // fin.getline(str, 20);
        nb_vertices = str[0] - '0';
       // cout << "nb vertices ";
       // cout << nb_vertices << endl;
      /** On cree les sommets du graphe*/
        for(int i = 0; i< nb_vertices; i++)
            ver.push_back(new Vertex(i+1));
       // for(int i = 0; i< ver.size(); i++)
          //  cout<<"sommet "<< i+1 <<" "<<ver[i]<<endl;
      }
      /** Deuxieme tour de boucle on récupère la liste d'adjacence ligne par ligne*/
      if(loop>1 && loop<4){ // loop>=1 ?

          char* line_token[10] = {};
          line_token[0] = strtok(str, " :");
          v.push_back(line_token[0]);
        //  cout<<"v[0]="<<v[0]<<endl;
          if (line_token[0]){
           //  cout<< "TOTO 7"<<endl;
             for (int n = 1; n < 10; n++){
                line_token[n] = strtok(0, " :");
                if (!line_token[n])
                  break;
                v.push_back(line_token[n]);
        }

           // cout << "v[1]="<< v[1] <<endl;
      }

    /** Pour chaque ligne, on crée les arretes correspondantes et on ajoute les voisins au sommet*/
      if(v.size()>1)
         {

             for(int j =1+size; j<v.size(); j++){
                 string sv;
                 if(v[j] != NULL)
                    sv = v[j];
                 int nb = atoi(sv.c_str());
                 e.push_back(new Edge(ver[num_vert], ver[nb-1]));
                 ver[num_vert]->add_neighbour(ver[nb-1]);
             }
           }
      size = v.size();
     // cout << (ver[num_vert])->get_number_of_neighbours();
      num_vert++;
    }
}
    /** On affecte les sommets et arretes au graphe*/
    g->edges = e;
    g->vertexes = ver;
    return g;
}
