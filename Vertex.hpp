#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>

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
    vector<Vertex *>& get_neighbours();


private:
    int key_value;
    vector<Vertex *> neighbours;
};

#endif // VERTEX_HPP
