#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <set>

using namespace std;

class Vertex
{
public:
    Vertex(int key_value);
    ~Vertex();
    int get_key();
    void set_color(int color);
    int get_color();
    int get_number_of_neighbours();
    void add_neighbour(Vertex * vertex);
    void add_pred(Vertex * vertex);
    void add_succ(Vertex * vertex);
    void display_neighbours();

    set<Vertex *>& get_pred();
    set<Vertex *>& get_succ();
    set<Vertex *>& get_neighbours();

    Vertex* get_parent();
    void set_parent(Vertex * parent);





    int key_value;
    set<Vertex *> neighbours;
    set<Vertex *> pred;// predecesseur pour algo biparti
    set<Vertex *> succ; // successeur pour algo biparti
    int color; // 0=blanc 1=gris 2=noir
    Vertex* parent;


};

#endif // VERTEX_HPP
