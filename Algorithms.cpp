#include "Algorithms.hpp"
#include "Utils.hpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>



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
            if ((*current)->neighbours.size() == 0){
                // if we don't have neighbours, continue
                continue;
            }else{
                contains_edges = true;
                Vertex* first = (*current);
                Vertex* last = (*(*current)->neighbours.begin());

                cover.insert(first);
                cover.insert(last);

                // First we absolutly need to remove those edges in the others list !
                // remove edges sibbling first vertex
                for (set<Vertex*>::iterator it = first->neighbours.begin() ; it != first->neighbours.end(); ++it){
                    (*it)->neighbours.erase(first);

                }

                // do the same for the other vertex
                for (set<Vertex*>::iterator it = last->neighbours.begin() ; it != last->neighbours.end(); ++it){
                    (*it)->neighbours.erase(last);
                }

                // remove all egdes from this node and the first one in his neighbours list
                first->neighbours.clear();
                last->neighbours.clear();
                break;

            }
        }
        //cout << "Après une itération: " << endl;
        //Utils::display_graph(any_graph);

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
        for (set<Vertex*>::iterator it = max_degree->neighbours.begin() ; it != max_degree->neighbours.end(); ++it){
            (*it)->neighbours.erase(max_degree);
        }
        // remove all edges from max_degree node
        max_degree->neighbours.clear();
        //cout << "Après une itération: " << endl;
        //Utils::display_graph(any_graph);

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
                  current_father->get_children().erase(current);
              }
        }
        iter++;
    }

    return cover;
}

// le cover est à dupliquer à chaque nouvel appel comme le graph
set<int> Algorithms::parametric_algorithm_impl(Graph *any_graph, set<int> current_cover, int cpt, int k){

    bool has_edges = false;
    for (vector<Vertex*>::iterator it = any_graph->get_iterator_begin(); it != any_graph->get_iterator_end() ; ++it){
        if ((*it)->get_number_of_neighbours() != 0){
            has_edges = true;
            break;
        }

    }
    // we didn't find a cover
    if (cpt >= k){
        set<int> error;
        error.insert(-1);
        return error;
    }

    // we find a cover
    if (!has_edges){
        return current_cover;

    }
    set<int> cover_left = current_cover;
    set<int> cover_right = current_cover;


    // two choises : we add this vertex in the cover or his neighbours

    /**
    * 1 : add max_degree to the cover1
    **/

    // create a new graph
    Graph * graph_left = any_graph->get_graph_copy();
    Utils::display_graph(graph_left);
    //find max_degree in this graph
    Vertex* max_degree_left = graph_left->get_vertexes().at(0);
    for (vector<Vertex*>::iterator it = graph_left->get_iterator_begin(); it != graph_left->get_iterator_end() ; ++it){
        if ((*it)->get_number_of_neighbours() > max_degree_left->get_number_of_neighbours())
            max_degree_left = (*it);
    }
    cover_left.insert(max_degree_left->get_key());
    // remove all edges incident to max_degree
    // remove the covered edges
    for (set<Vertex*>::iterator it = max_degree_left->neighbours.begin() ; it != max_degree_left->neighbours.end(); ++it){
        (*it)->neighbours.erase(max_degree_left);
    }
    // remove all edges from max_degree node

    max_degree_left->neighbours.clear();


    // launch this function
    set<int> result_left = parametric_algorithm_impl(graph_left, cover_left, ++cpt, k);

    /** end 1 **/

    /**
    * 2 : add his neighbours
    **/

    Graph * graph_right = any_graph->get_graph_copy();
    Utils::display_graph(graph_right);
    //find max_degree in this graph
    Vertex* max_degree_right = graph_right->get_vertexes().at(0);
    for (vector<Vertex*>::iterator it = graph_right->get_iterator_begin(); it != graph_right->get_iterator_end() ; ++it){
        if ((*it)->get_number_of_neighbours() > max_degree_right->get_number_of_neighbours())
            max_degree_right = (*it);
    }
    // remove the covered edges

    for (set<Vertex*>::iterator it = max_degree_left->neighbours.begin() ; it != max_degree_left->neighbours.end(); ++it){
        (*it)->neighbours.erase(max_degree_left);
    }
    // remove all edges from max_degree node
    max_degree_left->neighbours.clear();


    set<Vertex*>::iterator tmp;

    for (set<Vertex*>::iterator current = max_degree_right->neighbours.begin(); current != max_degree_right->neighbours.end() ; ){
        // faire un second for !
        cover_right.insert((*current)->get_key());
        Vertex* vertex_tmp = (*current);


        for (set<Vertex*>::iterator it = (*current)->neighbours.begin(); it != (*current)->neighbours.end() ; ++it){
            // remove all edges from this neighbour
            // remove it from the other side

            if ((*it)->get_key() == max_degree_right->get_key()){
                tmp = current;
                ++tmp;
                (*it)->neighbours.erase(vertex_tmp);
            }else{
                (*it)->neighbours.erase(vertex_tmp);
            }

        }

        (vertex_tmp)->neighbours.clear();


        current = tmp;


    }


    // relaunch this function
    set<int> result_right = parametric_algorithm_impl(graph_right, cover_right, ++cpt, k);
    /** end 2 **/


    set<int>::iterator first_value_iterator = result_right.begin();
    int first_value = (*first_value_iterator);
    // we choose the smaller cover unless this one contain -1
    if ((result_left.size() > result_right.size()) && (first_value != -1))
        return result_right;
    return result_left;
}

// Launch the real function
set<int> Algorithms::parametric_algorithm(Graph * current_graph, int k){
    set<int> empty_set;
    return parametric_algorithm_impl(current_graph, empty_set, 0, k);


}

void Algorithms::ford_fulkerson(Vertex* source, Vertex* terminal, set<Vertex*> part_S, set<Vertex*> part_T, int** edge_flow,int ** best_path_flow){

    //creation file
    queue<Vertex*> queue;

    for (set<Vertex*>::iterator it = part_S.begin(); it != part_S.end() ; ++it){
        (*it)->set_color(0);
        for (set<Vertex*>::iterator iter = (*it)->get_succ().begin(); iter != (*it)->get_succ().end() ; ++iter){
            edge_flow[(*it)->get_key()][(*iter)->get_key()] =
                    best_path_flow[(*it)->get_key()][(*iter)->get_key()];
        }
    }
    for (set<Vertex*>::iterator it = part_T.begin(); it != part_T.end() ; ++it){
        (*it)->set_color(0);
        for (set<Vertex*>::iterator iter = (*it)->get_succ().begin(); iter != (*it)->get_succ().end() ; ++iter){
            edge_flow[(*it)->get_key()][(*iter)->get_key()] =
                    best_path_flow[(*it)->get_key()][(*iter)->get_key()];
        }
    }

    source->set_color(1);
    queue.push(source);

    while (terminal->get_color()==0 && !queue.empty()){

        Vertex* current= queue.front();
        queue.pop();

        for (set<Vertex*>::iterator it = current->get_succ().begin(); it != current->get_succ().end() ; ++it){
            if ((*it)->get_color() == 0 && edge_flow[current->get_key()][(*it)->get_key()] == 0){
                (*it)->set_color(1);
                edge_flow[current->get_key()][(*it)->get_key()] = 1;
                queue.push((*it));
                (*it)->set_parent(current);
            }
        }
        for (set<Vertex*>::iterator it = current->get_pred().begin(); it != current->get_pred().end() ; ++it){
            if ((*it)->get_color() == 0 && edge_flow[(*it)->get_key()][current->get_key()] == 1){
                (*it)->set_color(1);
                edge_flow[(*it)->get_key()][current->get_key()] = 0;
                queue.push((*it));
                (*it)->set_parent(current);

            }
        }
        current->set_color(2);
    }

    // pour savoir si on relance ou pas
    if (!queue.empty()){
        // Garde les flux du chemin améliorant
        Vertex * start = terminal;
        while (start != source){

            if (part_T.find(start->get_parent()) != part_T.end() && part_S.find(start) != part_S.end()){
                best_path_flow[start->get_key()][start->get_parent()->get_key()] =
                        edge_flow[start->get_key()][start->get_parent()->get_key()];
            }
            else{
                best_path_flow[start->get_parent()->get_key()][start->get_key()] =
                        edge_flow[start->get_parent()->get_key()][start->get_key()];
            }
            start = start->get_parent();
        }

        while (!queue.empty()){
            queue.pop();;
        }

        ford_fulkerson(source,terminal,part_S,part_T,edge_flow,best_path_flow);
    }

}


set<Vertex*> Algorithms::bi_part_algorithm(Graph *any_graph){


    //couverture minimale
    set<Vertex*> cover;
    //Sommet des deux parties
    set<Vertex*> part_S;
    set<Vertex*> part_T;
    //stockage des flux / et des flux des chemins améliorants trouvés
    int ** edge_flow;
    int ** best_path_flow;

    //On stocke le premier sommet dans part_S
    vector<Vertex*> copy_vertex=any_graph->get_vertexes();
    part_S.insert(copy_vertex.at(0));

    //Variable pour savoir si on parcours part_s ou part_T
    int s_or_t = 0;
    //Tant que tous les sommets n'ont pas été stocké dans part_T ou part_S
    while (part_S.size()+part_T.size()!= copy_vertex.size() ){

        if (s_or_t==1){
            //Pour chaque sommet de part_T (on peut ajoutere indice_T qui repartirait que du dernier visité)
            for (set<Vertex*>::iterator it = part_T.begin(); it != part_T.end() ; ++it){
                //Pour chaque voisins
                for (set<Vertex*>::iterator iter = (*it)->get_neighbours().begin(); iter!=(*it)->get_neighbours().end() ; ++iter){
                    part_S.insert(*iter);
                }
            }
            s_or_t=0;
        }
        else{
            //Pour chaque sommet de part_S
            for (set<Vertex*>::iterator it = part_S.begin(); it != part_S.end() ; ++it){
                //Pour chaque voisins
                for (set<Vertex*>::iterator iter = (*it)->get_neighbours().begin(); iter!=(*it)->get_neighbours().end() ; ++iter){
                    part_T.insert(*iter);
                }
            }
            s_or_t=1;
        }
    }

    int MAX= part_S.size()+part_T.size()+2;
    // Ajout du sommet source
    Vertex * source= new Vertex(MAX-1);
    part_S.insert(source);
    // Ajout du sommet terminal
    Vertex * terminal= new Vertex(MAX-2);
    part_T.insert(terminal);

    // Mise à jour des successeur et prédecesseur des sommets
    for (set<Vertex*>::iterator it = part_S.begin(); it != part_S.end() ; ++it){
        if ((*it) != source){//evite d'avoir s comme predecesseur et successeur de s
            (*it)->add_pred(source);
            source->add_succ(*it);
        }
        for (set<Vertex*>::iterator iter = (*it)->get_neighbours().begin(); iter != (*it)->get_neighbours().end() ; ++iter){
            (*it)->add_succ(*iter);
            (*iter)->add_pred(*it);
        }

    }
    // Mise à jour des succ et pred pour t
    for (set<Vertex*>::iterator it = part_T.begin(); it != part_T.end() ; ++it){
        if ((*it) != terminal){//evite d'avoir t comme predecesseur et successeur de t
            (*it)->add_succ(terminal);
            terminal->add_pred(*it);
        }
    }
    // SOURCE correspondra à la case MAX-1 et TERMINAL corespondra à MAX-2
    edge_flow = new int * [MAX];
    for (int i=0; i<MAX; ++i ){
        edge_flow [i] = new int [MAX];
    }
    best_path_flow = new int * [MAX];
    for (int i=0; i<MAX; ++i ){
        best_path_flow [i] = new int [MAX];
    }

    //Initialisation pour Ford-Fulkerson
    for (set<Vertex*>::iterator it = part_S.begin(); it != part_S.end() ; ++it){
        (*it)->set_color(0);
        for (set<Vertex*>::iterator iter = (*it)->get_succ().begin(); iter != (*it)->get_succ().end() ; ++iter){
            edge_flow[(*it)->get_key()][(*iter)->get_key()] = 0;
            best_path_flow[(*it)->get_key()][(*iter)->get_key()] = 0;
        }
    }
    for (set<Vertex*>::iterator it = part_T.begin(); it != part_T.end() ; ++it){
        (*it)->set_color(0);
        for (set<Vertex*>::iterator iter = (*it)->get_succ().begin(); iter != (*it)->get_succ().end() ; ++iter){
            edge_flow[(*it)->get_key()][(*iter)->get_key()] = 0;
            best_path_flow[(*it)->get_key()][(*iter)->get_key()] = 0;
        }
    }

    ford_fulkerson(source,terminal,part_S,part_T,edge_flow,best_path_flow);

    //Calcul de la couverture
    for (set<Vertex*>::iterator it = part_T.begin(); it != part_T.end() ; ++it){
        if ((*it)->get_color() == 2){
            cover.insert(*it);
        }
    }
    for (set<Vertex*>::iterator it = part_S.begin(); it != part_S.end() ; ++it){
        if ((*it)->get_color() == 0){
            cover.insert(*it);
        }
    }

    //SUpprime s et t de la couverture
    cover.erase(source);
    cover.erase(terminal);

    return cover;
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



std::vector<Vertex*> Algorithms::two_aprox_first_depth(Graph* g){

    std::vector<Vertex*> cover;
    std::vector<Vertex*> list = g->get_vertexes();
    std::vector<int> keys;

    Vertex* current;
    Vertex* root = list[0];

    while(cover.size() != g->get_number_of_vertexes()){

        bool found;
        for(int j=0; j<g->get_number_of_vertexes(); j++){
            found = false;
            for(int k=0; k<cover.size(); k++){
                if(cover[k]->get_key() == j)
                    found = true;
            }
            if(!found){
                current = list[j];
                break;
            }
        }

        cover = two_aprox_first_depth_rec(g, cover, current, NULL, keys);

    }

    for(int j=0; j<cover.size(); j++)
        if(cover[j]->get_number_of_neighbours() < 2 && cover[j]->get_number_of_neighbours() > 0 && cover[j]->get_key() != root->get_key())
            cover.erase(cover.begin()+j);


    return cover;
}


std::vector<Vertex*> Algorithms::two_aprox_first_depth_rec(Graph* g, std::vector<Vertex*> s, Vertex* current, Vertex* prec, std::vector<int> keys){
    bool minChanged = false;

    Vertex* newVertex = new Vertex(current->get_key());
    if(prec != NULL)
        newVertex->add_neighbour(new Vertex(prec->get_key()));
    s.push_back(newVertex);
    keys.push_back(newVertex->get_key());


    Vertex* nextVertex;
    int min = g->get_number_of_vertexes();
    int i = 0;

    while(i < current->get_number_of_neighbours()){

        minChanged = false;

        for(set<Vertex*>::iterator it = (current->neighbours).begin() ; it != (current->neighbours).end(); ++it){

            if (it == current->neighbours.begin() && ((find(keys.begin(), keys.end(),(*it)->get_key())) == keys.end())){
                min = (*it)->get_key();
                nextVertex = (*it);
                minChanged = true;
            }

            if (((*it)->get_key() < min) && ((find(keys.begin(), keys.end(),(*it)->get_key())) == keys.end())){
                min = (*it)->get_key();
                nextVertex = (*it);
                minChanged = true;

            }

        }

        if(minChanged == false){
            return s;
        }
        Vertex* newNeighbour = new Vertex(min);
        newVertex->add_neighbour(newNeighbour);
        s = two_aprox_first_depth_rec(g, s, nextVertex, newVertex, keys);
        min = g->get_number_of_vertexes();


        std::vector<int> keys2;
        for(int i = 0; i<s.size(); i++){
            keys2.push_back(s[i]->get_key());
               }
        keys = keys2;
        i++;

    }

    return s;


}

void Algorithms::reduction_SAT(Graph *any_graph,int couverture){
    int facteur =10;
    if (couverture>9){
        facteur*=10;
    }
    if (couverture>99){
        facteur*=10;
    }
    if (couverture>999){
        facteur*=10;
    }








    int siz_phi1 = 0;
    for (int c =couverture-1; c>0;--c){
        siz_phi1 +=c;
    }
    int siz_phi2 = 0;
    for (int d =any_graph->get_number_of_vertexes()-1; d>0;--d){
        siz_phi2 +=d;
    }


    int number_clauses = ((siz_phi1)*any_graph->get_number_of_vertexes()) +
            ((siz_phi2)*couverture) +
            any_graph->get_edges_copy().size();
    int number_variables = couverture * any_graph->get_number_of_vertexes();

    int test_clause = 0;

    ofstream fichier("fichier_pour_minisat.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert

    fichier << "p cnf " << number_variables << " " << number_clauses << endl;

    //Tableau des variables
    // 11 : sommmet 1 a la 1ere place

    int* var_tab = new int[(couverture * any_graph->get_number_of_vertexes())+1];

    int pos=0;

    for (vector<Vertex*>::iterator it =any_graph->get_vertexes().begin(); it !=any_graph->get_vertexes().end() ; ++it){
        for (int j=1; j<couverture+1; ++j){
            var_tab[pos]= (((*it)->get_key())+1)*facteur +j;
            pos++;
        }
    }
    //stockage du facteur
    var_tab[(couverture * any_graph->get_number_of_vertexes())] = facteur;

    ofstream tableau("correspondance_tab.txt", ios::out | ios::trunc);
    for (int i =0; i<couverture * any_graph->get_number_of_vertexes(); ++i){
        tableau << var_tab[i] << endl;
    }
    tableau << var_tab[couverture * any_graph->get_number_of_vertexes()] << endl;
    tableau.close();


    //TEST
    for (int test=0; test <couverture * any_graph->get_number_of_vertexes(); ++test){
        cout << "Case : " << test << " --> " << var_tab[test] << endl;
    }
    //TEST

    int x_ik;
    int x_il;
    for (int i=1; i < any_graph->get_number_of_vertexes()+1;++i){
        for (int k=1; k<couverture ; ++k){//faire un tableau avec num variable -> correspondance
            for (int l=k+1; l< couverture+1;++l){
                for (int m=0;m<couverture * any_graph->get_number_of_vertexes();m++){
                    if (var_tab[m]==i*facteur + k){
                        x_ik = m+1;
                    }
                    if (var_tab[m]==i*facteur + l){
                        x_il= m+1;
                    }
                }
                fichier << "-" << x_ik << " -" << x_il << " 0" << endl;
                test_clause++;
            }
        }

    }
    int x_jk;
    for (int k=1; k < couverture+1;++k){
        for (int i=1; i<any_graph->get_number_of_vertexes(); ++i){//faire un tableau avec num variable -> correspondance
            for (int j=i+1; j<any_graph->get_number_of_vertexes()+1; ++j){
                for (int m=0;m<couverture * any_graph->get_number_of_vertexes();m++){
                    if (var_tab[m]==i*facteur + k){
                        x_ik = m+1;
                    }
                    if (var_tab[m]==j*facteur + k){
                        x_jk= m+1;
                    }
                }
                fichier << "-" << x_ik << " -" << x_jk << " 0" << endl;
                test_clause++;
            }
        }


    }


    for (vector<Edge*>::iterator it =any_graph->get_edges_copy().begin(); it !=any_graph->get_edges_copy().end() ; ++it){
        for (int k=1; k < couverture+1;++k){
            for (int m=0;m<couverture * any_graph->get_number_of_vertexes();m++){
                if (var_tab[m]==(((*it)->get_vertex1()->get_key())+1)*facteur + k){
                        x_ik = m+1;
                    }
                    if (var_tab[m]==(((*it)->get_vertex2()->get_key())+1)*facteur + k){
                        x_jk= m+1;
                    }
                }
            fichier << x_ik << " " << x_jk << " ";


            }
         test_clause++;
         fichier << "0" << endl;
        }


    cout << "Facteur :: "<<facteur << endl;
    fichier.close();

}


set<int> Algorithms::find_cover_minisat(char* corresp_tab,char * output_minisat){

    //get file in tab
    int size_tab;
    string line;
    ifstream tab_file(corresp_tab, ios::in);
    while (getline(tab_file, line)){
        size_tab++;
    }
    tab_file.close();
    int * vertex_index= new int[size_tab];
    ifstream tab_file2(corresp_tab, ios::in);
    line.clear();
    int index=0;
    while (getline(tab_file2, line)){
        vertex_index[index] = atoi(line.c_str());
        index++;
    }
    tab_file2.close();
    int facteur = vertex_index[size_tab-1];


    set<int> cover;
    string content;
    string content_number;
    char c = '-';
    ifstream file(output_minisat, ios::in);
    getline(file, content);

    if (content == "UNSAT"){
        cout << "NO MIN COVER FOR THIS SIZE" << endl;
    }
    else if(content == ""){
        cout << "ERROR FILE" << endl;
    }
    else if(content == "SAT"){
    getline(file,content_number);
    bool cont = true;
    int i =0;
    while (cont){


        if (content_number.at(i) == c){


            i+=1;
            while (content_number.at(i) == '0' || content_number.at(i) == '1'
                   || content_number.at(i) == '2' || content_number.at(i) =='3'
                        || content_number.at(i) == '4' || content_number.at(i) == '5'
                        || content_number.at(i) == '6' || content_number.at(i) == '7'
                        || content_number.at(i) == '8' || content_number.at(i) == '9'){

                i+=1;
            }
            i++;
        }
        else{

            int indice = atoi(&content_number.at(i));


            i++;
            while (content_number.at(i) == '0' || content_number.at(i) == '1'
                   || content_number.at(i) == '2' || content_number.at(i) =='3'
                        || content_number.at(i) == '4' || content_number.at(i) == '5'
                        || content_number.at(i) == '6' || content_number.at(i) == '7'
                        || content_number.at(i) == '8' || content_number.at(i) == '9'){
                i++;
            }
            i++;

            cover.insert((vertex_index[indice-1]/facteur)-1);

        }

        if (content_number.at(i) == '0'){

            cont =false;
     }
    }
}



    file.close();

    return cover;

}







