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

void Utils::detect_cycle(char* filename){

    std::vector< std::vector<int> > adj_list;

    ifstream fin;
    fin.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    char str[20];
    fin.getline(str, 20);

    while (!fin.eof()){
        cout << "ON COMMENCE" << endl;
      fin.getline(str, 20);

      std::vector<int> l;


      char* line_token[10] = {};
      line_token[0] = strtok(str, " :");
      l.push_back(atoi(line_token[0]));
      cout << "CACA" << endl;

      if (line_token[0]){
         for (int n = 1; n < 10; n++){
            line_token[n] = strtok(0, " :");
            if (!line_token[n])
              break;
            l.push_back(atoi(line_token[n]));
         }
      }

      cout << "tour de boucle" <<endl;
      for(int i=0; i<l.size(); i++)
         cout << l[i] << endl;

    adj_list.push_back(l);
    cout << adj_list.size() <<endl;
    }
    cout<< "toto" << endl;
    cout << adj_list.size() <<endl;
  //  for(int j=0; j<adj_list.size(); j++)
     //for(int i=0; i<adj_list[j].size(); i++){
      //   cout << adj_list[i][j] << endl;
    }









