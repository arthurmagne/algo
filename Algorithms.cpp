#include "Algorithms.hpp"
#include "Utils.hpp"
#include <iostream>


using namespace std;

/* We'll work only with adjacency list */

Algorithms::Algorithms()
{
}


set<Vertex*> Algorithms::two_aprox_algorithm(Graph *any_graph){
    // We do have an adjacency list : all vertexes already have a list of neighbours!
    vector<Vertex*> vertexes = any_graph->get_vertexes();
    set<Vertex*> cover;
    bool contains_edges = true;
    while (contains_edges){
        contains_edges = false;
        for (vector<Vertex*>::iterator current = vertexes.begin() ; current != vertexes.end(); ++current){
            // we pick an edge randomly (the first one in our adjacency list)
            if ((*current)->get_neighbours().size() == 0){
                // if we don't have neighbours, continue
                continue;
            }else{
                contains_edges = true;
                Vertex* first = (*current);
                Vertex* last = (*(*current)->get_neighbours().begin());

                cover.insert(first);
                cover.insert(last);

                // First we absolutly need to remove those edges in the others list !
                // remove edges sibbling first vertex
                for (set<Vertex*>::iterator it = first->get_neighbours().begin() ; it != first->get_neighbours().end(); ++it){
                    (*it)->get_neighbours().erase(first);

                }

                // do the same for the other vertex
                for (set<Vertex*>::iterator it = last->get_neighbours().begin() ; it != last->get_neighbours().end(); ++it){
                    (*it)->get_neighbours().erase(last);
                }

                // remove all egdes from this node and the first one in his neighbours list
                first->get_neighbours().clear();
                last->get_neighbours().clear();
                break;

            }
        }
        cout << "Après une itération: " << endl;
        Utils::display_graph(any_graph);

    }

    return cover;
}

/* We choose the vertex with the higher degree, add it to the cover
*  and remove it and his neighbours from the vertex vector
* " A greedy algorithm always makes the choice that looks best at the moment.
*  The greedy heuristic cannot always find an optimal solution!
*  If the graph is represented by an adjacency list this can be implemented in O(m + n) time." */
set<Vertex*> Algorithms::greedy_algorithm(Graph *any_graph){
    // We do have an adjacency list : all vertexes already have a list of neighbours!
    vector<Vertex*> vertexes = any_graph->get_vertexes();
    set<Vertex*> cover;
    Vertex * max_degree;
    bool contains_edges = true;
    while (contains_edges){
        contains_edges = false;

        // we choose the vertex with degree max
        for (vector<Vertex*>::iterator current = vertexes.begin() ; current != vertexes.end(); ++current){
            if (current == vertexes.begin())
               max_degree = *current;
            if ((*current)->get_number_of_neighbours() > max_degree->get_number_of_neighbours())
               max_degree = *current;
        }
        if (max_degree->get_number_of_neighbours() != 0){
            contains_edges = true;
        }else{
            continue;
        }

        cover.insert(max_degree);


        // remove the covered edges
        for (set<Vertex*>::iterator it = max_degree->get_neighbours().begin() ; it != max_degree->get_neighbours().end(); ++it){
            (*it)->get_neighbours().erase(max_degree);
        }
        // remove all edges from max_degree node
        max_degree->get_neighbours().clear();

        cout << "Après une itération: " << endl;
        Utils::display_graph(any_graph);

    }

    return cover;
}

set<Node*> Algorithms::optimal_tree(Tree *any_tree){
    //On mélange la liste des sommets
    set<Node*> cover;
    // seed rand
    srand(time(NULL));
    vector<Node*> nodes= any_tree->get_nodes();
    random_shuffle(nodes.begin(),nodes.end());
    vector<Node*>::iterator iter = nodes.begin();
    while (iter != nodes.end()){
        //trouver un moyen de trouver un noeud au hazard (avec des fils)
        // pour ça on à mélangé les noeuds, on les parcours, on regarde si le noeud à des fils sinon on le passe
        // semble fonctionner
        if (((*iter)->number_of_children()==0) && ((*iter)->get_parent()==NULL)){
            iter++;
            continue;
        }

        Node* current = *iter;
        //On cherche une feuille
        while (current->number_of_children()!=0){
            current=(*current->get_children().begin());
        }
        //On marque le père
        if(current->get_parent()!=NULL){
            current=current->get_parent();
            cover.insert(current);

             //On supprime les aretes fils-père
             for (set<Node*>::iterator it = current->get_children().begin() ; it != current->get_children().end(); ++it){

                 (*it)->set_parent(NULL);
              }
              //On supprime les aretes pere-fils
             current->get_children().clear();

             //On supprime l'arete pere-"grandpere"
             if(current->get_parent()!=NULL){
                  Node* current_father = current->get_parent();
                  current->set_parent(NULL);
                  current_father->get_children().erase(current_father);
              }
        }
        iter++;
    }

    return cover;
}
/*
set<Vertex*> Algorithms::parametric_algorithm(Graph *any_graph, set<Vertex *> current_cover, int cpt, int k){
    if (cpt >= k){
        return NULL;
    }
    set<set<Vertex*> > set_of_cover;
    // We loop til cpt > k
    int cpt = 0;

    // two choises : we add this vertex in the cover or his neighbours


    // 1 : add max_degree to the cover1
    // create a new graph
    Graph * graph_left = any_graph->get_graph_copy();

    //find max_degree in this graph
    Vertex* max_degree_left = graph_left->get_vertexes_copy().at(0);
    for (vector<Vertex*>::iterator it = graph_left->get_iterator_begin(); it != graph_left->get_iterator_end() ; ++it){
        if ((*it)->get_number_of_neighbours() > max_degree_left->get_number_of_neighbours())
            max_degree_left = (*it);
    }
    set<Vertex*> cover_left;
    cover_left.insert(max_degree_left);
    // remove all edges incident to max_degree
    // remove the covered edges
    for (set<Vertex*>::iterator it = max_degree_left->get_neighbours().begin() ; it != max_degree_left->get_neighbours().end(); ++it){
        (*it)->get_neighbours().erase(max_degree_left);
    }
    // remove all edges from max_degree node
    max_degree_left->get_neighbours().clear();
    // launch second function
    parametric_algorithm_impl(graph_left, cover_left, ++cpt);



    // 2 : add his neighbours
    Graph * graph_right = any_graph->get_graph_copy();
    //find max_degree in this graph
    Vertex* max_degree_right = graph_right->get_vertexes_copy().at(0);
    for (vector<Vertex*>::iterator it = graph_right->get_iterator_begin(); it != graph_right->get_iterator_end() ; ++it){
        if ((*it)->get_number_of_neighbours() > max_degree_right->get_number_of_neighbours())
            max_degree_right = (*it);
    }
    set<Vertex*> cover_right;
    // remove the covered edges
    for (set<Vertex*>::iterator it = max_degree_left->get_neighbours().begin() ; it != max_degree_left->get_neighbours().end(); ++it){
        (*it)->get_neighbours().erase(max_degree_left);
    }
    // remove all edges from max_degree node
    max_degree_left->get_neighbours().clear();

    set<Vertex*>::iterator tmp;

    for (set<Vertex*>::iterator current = max_degree_right->get_neighbours().begin(); current != max_degree_right->get_neighbours().end() ; ){
        // faire un second for !
        cover_right.insert(*current);
        Vertex* vertex_tmp = (*current);

        for (set<Vertex*>::iterator it = (*current)->get_neighbours().begin(); it != (*current)->get_neighbours().end() ; ++it){

            // remove all edges from this neighbour
            // remove it from the other side

            if ((*it)->get_key() == max_degree_right->get_key()){
                tmp = current;
                ++tmp;
                (*it)->get_neighbours().erase(vertex_tmp);
            }else{
                (*it)->get_neighbours().erase(vertex_tmp);
            }


        }
        (vertex_tmp)->get_neighbours().clear();
        current = tmp;


    }

    // launch second function
    parametric_algorithm(graph_right, cover_right, ++cpt, k);

    return cover_left;
}

void Algorithms::parametric_algorithm_impl(Graph * current_graph, set<Vertex*> current_cover, int k){
    cout << endl << "Nouvel appel" << endl;
    for (set<Vertex*>::iterator it = current_cover.begin() ; it != current_cover.end(); ++it){
        cout << (*it)->get_key() << endl;
    }
    Utils::display_graph(current_graph);

}



/*set<Node*> Algorithms::optimal_tree(Tree *any_tree){
    //On mélange la liste des sommets
    set<Node*> cover;
    vector<TreeEdge*> e;
    // seed rand
    srand(time(NULL));
    vector<Node*> nodes= any_tree->get_nodes();
    random_shuffle(nodes.begin(),nodes.end());
    int i=0;
   // while (!e==any_tree->get_edges()){

        Node* current = nodes.at(i);
        //On cherche une feuille
        while (current->number_of_children()!=0){
            current=(*current->get_children().begin());
        }
        //On marque le père
        if(current->get_parent()!=NULL){
            current=current->get_parent();
            cover.insert(current);

             //On supprime les arretes fils-père
             for (set<Node*>::iterator it = current->get_children().begin() ; it != current->get_children().end(); ++it){

                 TreeEdge* tmp = new TreeEdge(current, (*it));
                 e.push_back(tmp);
                 (*it)->set_parent(NULL);
              }
              //On supprime les arretes pere-fils
             current->get_children().clear();

             //On supprime l'arrete pere-"grandpere"
             if(current->get_parent()!=NULL){
                 TreeEdge* tmp = new TreeEdge(current, current->get_parent());
                 e.push_back(tmp);
                  Node* current_father = current->get_parent();
                 current->set_parent(NULL);
                  current_father->get_children().erase(current_father);
              }
        }
        i++;



    }

    return cover;
}*/

/*
set<Vertex*> Algorithms::two_aprox_first_depth(Graph* g){

    set<Vertex*> cover;
    std::vector<Vertex*> list = g->get_vertexes_copy();

    while(cover.size() != g->get_number_of_vertexes()){
        Vertex* current;
        for(vector<Vertex*>::iterator it = current->get_neighbours().begin() ; !cover.find(*it); ++it)
            current = (*it);
        two_aprox_first_depth_rec(cover, current, NULL);
    }

    return cover;
}


void Algorithms::two_aprox_first_depth_rec(set<Vertex*> s, Vertex* current, Vertex* prec){

    Vertex* newVertex = new Vertex(current->get_key());
    if(prec != NULL)
        newVertex->add_neighbour(prec->get_key());
    s.insert(newVertex);

    Vertex* min;

    int i = 0;
    while(i < current->get_number_of_neighbours()){

    for(set<Vertex*>::iterator it = current->get_neighbours().begin() ; it != current->get_neighbours().end(); ++it){
        if (it == it->get_neighbours().begin() && !(s.find(*it)))
           min = *it;
        if (((*it)->get_key() < min->get_key()) && !(s.find(*it)))
           min = *it;

    }

    if(min == NULL)
        return;

    Vertex* newNeighbour = new Vertex(min->get_key());
    newVertex->add_neighbour(newNeighbour);
    two_aprox_first_depth_rec(s, min, newVertex);
    i++;

    }

}
*/








