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
    int get_number_of_neighbours();
    void add_neighbour(Vertex * vertex);
    void display_neighbours();
    set<Vertex *>& get_neighbours();


private:
    int key_value;
    set<Vertex *> neighbours;
};

#endif // VERTEX_HPP
