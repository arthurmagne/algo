#include <iostream>
#include <string>
#include "Utils.hpp"
#include "Node.hpp"
#include "Graph.hpp"
#include <fstream>
#include <cstring>

using std::cout;
using std::endl;
using std::ifstream;

Utils::Utils()
{
}

void Utils::display_tree(Tree * tree){
    cout << tree->get_number_of_nodes() << endl;
    for (vector<Node*>::iterator it = tree->get_iterator_begin() ; it != tree->get_iterator_end(); ++it){
        if ((*it)->number_of_children() == 0)
            continue;
        cout << (*it)->get_key() << ": ";
        (*it)->display_children();
    }
}

void Utils::display_graph(Graph * graph){
    cout << graph->get_number_of_vertexes() << endl;
    for (vector<Vertex*>::iterator it = graph->get_iterator_begin() ; it != graph->get_iterator_end(); ++it){
        if ((*it)->get_number_of_neighbours() == 0)
            continue;
        cout << (*it)->get_key() << ": ";
        (*it)->display_neighbours();
    }
}

Graph Utils::generate_graph_from_file(std::string filename){
    std::vector<std::string> v;
    ifstream fin;
    fin.open(filename);
    if (!fin.good())
      return 1;

    int loop = 0;
    int nb_vertices = 0;

    while (!fin.eof()){

      char str[20];
      fin.getline(str, 20);

      if(loop++ == 0){
        nb_vertices = str[0] - '0';
        Graph g = new Graph();
        for(int i = 0; i< nb_vertices; i++)
            g->vertexes.push_back(new Vertex(i));
      }

      const char* line_token[10] = {};
      line_token[0] = strtok(str, " :");

      v.push_back(line_token[0]);
      for(int i; i<v.size(); i++)
          cout << v[i] << " ";
         cout << endl;

      if (line_token[0]){
        for (int n = 1; n < 10; n++){
          line_token[n] = strtok(0, " :");
       if (!line_token[n])
              break;
       v.push_back(line_token[n]);

       if(v.size()>1)
         {
           for(int j = 0; j<v.size(); j++)
             g->edges.push_back(new Edge(v[0], v[j]));
           }
        }
      }
    }
}
