#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <cstdlib>
#include <list>
#include "Utils.hpp"

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

bool Utils::detect_cycle(char* filename){

    std::vector< std::vector<int> > adj_list;

    ifstream fin;
    fin.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    char str[20];
    fin.getline(str, 20);
    char* line_token[10] = {};
    line_token[0] = strtok(str, " :");
    int nb_loop = atoi(line_token[0]);

    int matA[nb_loop][nb_loop];
    int matB[nb_loop][nb_loop];
    int matC[nb_loop][nb_loop];

    int loop = 0;

    while (loop++<nb_loop){
      fin.getline(str, 20);
      std::vector<int> l;

      char* line_token[10] = {};
      line_token[0] = strtok(str, " :");
      l.push_back(atoi(line_token[0]));

      if (line_token[0]){
         for (int n = 1; n < 10; n++){
            line_token[n] = strtok(0, " :");
            if (!line_token[n])
              break;
            l.push_back(atoi(line_token[n]));

         }
         adj_list.push_back(l);
      }
    }

      for(int i=0; i<nb_loop; i++)
        for(int j=0; j<nb_loop; j++)
            matA[i][j] = 0;

      for(int i=0; i<adj_list.size(); i++){
          int s = adj_list[i][0];
          for(int j=1; j<adj_list[i].size(); j++)
              matA[s][(adj_list[i][j])] = 1;
      }

      for(int i=0; i<nb_loop; i++)
          for(int j=0; j<nb_loop; j++){
              matB[i][j] = matA[i][j];
              matC[i][j] = 0;
          }

      for(int n=0; n<=nb_loop; n++){
          for(int i=0; i<nb_loop; i++)
              for(int j=0; j<nb_loop; j++){
                  matC[i][j] = 0;
                  for(int k=0; k<nb_loop; k++)
                      matC[i][j] = matA[i][k] * matB[k][j] + matC[i][j];
              }

          for(int i=0; i<nb_loop; i++)
              for(int j=0; j<nb_loop; j++)
                  matB[i][j] = matC[i][j];

          for(int i=0; i<nb_loop; i++)
              if((matC[i][i] != 0) && n > 2)
                  return true;
              }

      return false;
    }

